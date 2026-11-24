#pragma once
#include <pebble.h>

typedef struct
{
    bool phone_muted;
    bool watch_muted;
    bool no_scroll_wrap;
    bool enable_backlight_on_vibration;
    uint16_t auto_close_timeout;
} Preferences;

extern Preferences preferences;

void reload_preferences();

uint8_t action_menu_font_size(void);
bool cycle_action_menu_font_size(void);
