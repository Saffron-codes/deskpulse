SET(SOURCES screens/ui_SplashScreen.c
    screens/ui_OTPScreen.c
    screens/ui_HomeScreen.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c)

add_library(ui ${SOURCES})
