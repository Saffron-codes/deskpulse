// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: Deskpulse

#include "../ui.h"

void ui_OTPScreen_screen_init(void)
{
    ui_OTPScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_OTPScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label5 = lv_label_create(ui_OTPScreen);
    lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label5, 1);
    lv_obj_set_y(ui_Label5, -24);
    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label5, "Device OTP");

    ui_Label6 = lv_label_create(ui_OTPScreen);
    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label6, 0);
    lv_obj_set_y(ui_Label6, 12);
    lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label6, "1234");
    lv_obj_set_style_text_letter_space(ui_Label6, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_Label6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label6, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

}
