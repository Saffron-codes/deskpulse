#include <lvgl.h>
#include <TFT_eSPI.h>
#include <ui.h>
#include <WiFi.h>
#include <HTTPClient.h>

typedef enum {
  NONE,
  NETWORK_CONNECTING,
  NETWORK_CONNECTED,
  NETWORK_CONNECT_FAILED
} Network_Status_t;

Network_Status_t networkStatus = NONE;


/*Change to your screen resolution*/
static const uint16_t screenWidth = 320;
static const uint16_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * screenHeight / 10];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

const char *ssid = "TASESA";
const char *password = "sesa75321476";

HTTPClient http;
static lv_timer_t *timer;
unsigned long networkTimeout = 10 * 1000;

String SERVER_URL = "https://d939dbba-1b51-4ac1-b260-12daf6487294-00-3avhhw4i10h4o.sisko.replit.dev/";

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char *buf) {
  Serial.printf(buf);
  Serial.flush();
}
#endif

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)&color_p->full, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
  uint16_t touchX = 0, touchY = 0;

  bool touched = tft.getTouch(&touchX, &touchY, 600);

  touchX += 45;
  touchY -= 30;

  if (!touched) {
    data->state = LV_INDEV_STATE_REL;
  } else {
    data->state = LV_INDEV_STATE_PR;

    /*Set the coordinates*/
    data->point.x = touchX;
    data->point.y = touchY;

    Serial.print("Data x ");
    Serial.println(touchX);

    Serial.print("Data y ");
    Serial.println(touchY);
  }
}

void setup() {
  Serial.begin(115200); /* prepare for possible serial debug */

  String LVGL_Arduino = "Hello Arduino! ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

  Serial.println(LVGL_Arduino);
  Serial.println("I am LVGL_Arduino");

  lv_init();

#if LV_USE_LOG != 0
  lv_log_register_print_cb(my_print); /* register print function for debugging */
#endif

  tft.begin();        /* TFT init */
  tft.setRotation(3); /* Landscape orientation, flipped */

  uint16_t calData[5] = { 404, 3388, 308, 3307, 1 };
  tft.setTouch(calData);

  lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * screenHeight / 10);

  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  /*Change the following line to your display resolution*/
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /*Initialize the (dummy) input device driver*/
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);


  ui_init();

  // Starting Tasks & Timer for UI
  networkConnector();
  timer = lv_timer_create(timerForNetwork, 1000, NULL);

  Serial.println("Setup done");
}


// timer for network connectivity
static void timerForNetwork(lv_timer_t *timer) {
  LV_UNUSED(timer);

  switch (networkStatus) {
    case NETWORK_CONNECTING:
      lv_obj_clear_flag(ui_SpinnerSplash, LV_OBJ_FLAG_HIDDEN);
      //lv_obj_clear_flag(ui_LabelStatus, LV_OBJ_FLAG_HIDDEN);
      //lv_label_set_text(ui_LabelStatus, "Connecting....");
      Serial.println("Connecting...");
      break;
    case NETWORK_CONNECTED:
      lv_obj_add_flag(ui_SpinnerSplash, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_flag(ui_LabelStatus, LV_OBJ_FLAG_HIDDEN);
      lv_label_set_text(ui_LabelStatus, "Connected");
      lv_scr_load_anim(ui_OTPScreen, LV_SCR_LOAD_ANIM_FADE_OUT, 500, 0,false);
      Serial.println("Connected");
      lv_timer_del(timer);
      break;
    case NETWORK_CONNECT_FAILED:
      lv_obj_add_flag(ui_SpinnerSplash, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_flag(ui_LabelStatus, LV_OBJ_FLAG_HIDDEN);
      lv_label_set_text(ui_LabelStatus, "Connection to WIFI failed...");
      Serial.println("Failed");
      break;
    default:
      break;
  }
}

static void networkConnector() {
  xTaskCreate(connectToWiFiTask,
              "connectToWiFiTask",
              2048,
              NULL,
              1,
              NULL);
}





void connectToWiFiTask(void *parameter) {

  unsigned long startingTime = millis();
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  vTaskDelay(100);

  WiFi.begin(ssid, password);

  networkStatus = NETWORK_CONNECTING;

  while (WiFi.status() != WL_CONNECTED && (millis() - startingTime) < networkTimeout) {
    vTaskDelay(250);
  }

  if (WiFi.status() == WL_CONNECTED) {
    networkStatus = NETWORK_CONNECTED;
  } else {
    networkStatus = NETWORK_CONNECT_FAILED;
  }

  vTaskDelete(NULL);
}


// void handleServerStatus() {
//   lv_obj_clear_flag(ui_SpinnerSplash, LV_OBJ_FLAG_HIDDEN);

//   http.begin(SERVER_URL);
//   int statusCode = http.GET();

//   if(statusCode == HTTP_CODE_OK){
//     lv_obj_add_flag(ui_SpinnerSplash, LV_OBJ_FLAG_HIDDEN);
//   }
//   else {
//     lv_obj_clear_flag(ui_LabelStatus, LV_OBJ_FLAG_HIDDEN);
//     lv_label_set_text(ui_LabelStatus, "Some Error Occurred");
//   }
// }

void loop() {
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}
