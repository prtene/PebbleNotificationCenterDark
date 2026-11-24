#include "preferences.h"

#include "commons/bytes.h"
#include "commons/connection/bucket_sync.h"
#include "ui/window_notification/window_notification.h"

Preferences preferences;

void reload_preferences()
{
    uint8_t bucket_data[PERSIST_DATA_MAX_LENGTH];
    const bool bucket_exists = bucket_sync_load_bucket(1, bucket_data);
    if (!bucket_exists)
    {
        return;
    }

    preferences.watch_muted = (bucket_data[0] & 0x01) != 0;
    preferences.phone_muted = (bucket_data[0] & 0x02) != 0;
    preferences.no_scroll_wrap = (bucket_data[0] & 0x04) != 0;
    preferences.enable_backlight_on_vibration = (bucket_data[0] & 0x08) != 0;
    preferences.auto_close_timeout = read_uint16_from_byte_array(bucket_data, 1);
}

static const uint32_t ACTION_MENU_FONT_SIZE_KEY = 1003;
static const uint8_t action_menu_font_sizes[] = {28, 42, 24};

static uint8_t action_menu_font_index(void)
{
    const int32_t index = persist_read_int(ACTION_MENU_FONT_SIZE_KEY);
    if (index < 0 || index >= (int32_t)ARRAY_LENGTH(action_menu_font_sizes))
    {
        return 0;
    }
    return (uint8_t)index;
}

uint8_t action_menu_font_size(void)
{
    return action_menu_font_sizes[action_menu_font_index()];
}

bool cycle_action_menu_font_size(void)
{
    const uint8_t next_index = (action_menu_font_index() + 1) % ARRAY_LENGTH(action_menu_font_sizes);
    return persist_write_int(ACTION_MENU_FONT_SIZE_KEY, next_index) > 0;
}
