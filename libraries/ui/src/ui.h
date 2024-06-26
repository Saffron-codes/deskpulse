// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: Deskpulse

#ifndef _DESKPULSE_UI_H
#define _DESKPULSE_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

#include "ui_helpers.h"
#include "ui_events.h"

// SCREEN: ui_SplashScreen
void ui_SplashScreen_screen_init(void);
extern lv_obj_t * ui_SplashScreen;
extern lv_obj_t * ui_title;
extern lv_obj_t * ui_SpinnerSplash;
extern lv_obj_t * ui_LabelStatus;
// SCREEN: ui_OTPScreen
void ui_OTPScreen_screen_init(void);
extern lv_obj_t * ui_OTPScreen;
extern lv_obj_t * ui_Label5;
extern lv_obj_t * ui_Label6;
// SCREEN: ui_HomeScreen
void ui_HomeScreen_screen_init(void);
extern lv_obj_t * ui_HomeScreen;
extern lv_obj_t * ui____initial_actions0;





void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
