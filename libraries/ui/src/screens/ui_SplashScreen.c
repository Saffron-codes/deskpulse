// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: Deskpulse

#include "../ui.h"

void ui_SplashScreen_screen_init(void)
{
    ui_SplashScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_SplashScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_flex_flow(ui_SplashScreen, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_SplashScreen, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    ui_title = lv_label_create(ui_SplashScreen);
    lv_obj_set_width(ui_title, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_title, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_title, -5);
    lv_obj_set_y(ui_title, -23);
    lv_obj_set_align(ui_title, LV_ALIGN_CENTER);
    lv_label_set_text(ui_title, "Deskpulse");
    lv_obj_set_style_text_font(ui_title, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SpinnerSplash = lv_spinner_create(ui_SplashScreen, 1000, 90);
    lv_obj_set_width(ui_SpinnerSplash, 24);
    lv_obj_set_height(ui_SpinnerSplash, 24);
    lv_obj_set_x(ui_SpinnerSplash, -4);
    lv_obj_set_y(ui_SpinnerSplash, 11);
    lv_obj_set_align(ui_SpinnerSplash, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_SpinnerSplash, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(ui_SpinnerSplash, LV_OBJ_FLAG_CLICKABLE);      /// Flags
    lv_obj_set_style_arc_width(ui_SpinnerSplash, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_width(ui_SpinnerSplash, 4, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_LabelStatus = lv_label_create(ui_SplashScreen);
    lv_obj_set_width(ui_LabelStatus, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelStatus, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelStatus, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelStatus, "Status");
    lv_obj_add_flag(ui_LabelStatus, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_set_style_text_font(ui_LabelStatus, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

}
