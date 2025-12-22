// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <hal.h>
#include <string.h>
#include <ctype.h>
#include <printf.h>
#include "qp.h"
#include "backlight.h"
#include "transactions.h"
#include "split_util.h"

#include "djinn.h"
#include "theme.h"

#include "frieren.qgf.h"
#include "lock-caps-ON.qgf.h"
#include "lock-scrl-ON.qgf.h"
#include "lock-num-ON.qgf.h"
#include "lock-caps-OFF.qgf.h"
#include "lock-scrl-OFF.qgf.h"
#include "lock-num-OFF.qgf.h"
#include "unispace18.qff.h"

static painter_image_handle_t frieren;
static painter_image_handle_t lock_caps_on;
static painter_image_handle_t lock_caps_off;
static painter_image_handle_t lock_num_on;
static painter_image_handle_t lock_num_off;
static painter_image_handle_t lock_scrl_on;
static painter_image_handle_t lock_scrl_off;
static painter_font_handle_t  unispace;

//----------------------------------------------------------
// UI Initialisation
void keyboard_post_init_display(void) {
    frieren       = qp_load_image_mem(gfx_frieren);
    lock_caps_on  = qp_load_image_mem(gfx_lock_caps_ON);
    lock_caps_off = qp_load_image_mem(gfx_lock_caps_OFF);
    lock_num_on   = qp_load_image_mem(gfx_lock_num_ON);
    lock_num_off  = qp_load_image_mem(gfx_lock_num_OFF);
    lock_scrl_on  = qp_load_image_mem(gfx_lock_scrl_ON);
    lock_scrl_off = qp_load_image_mem(gfx_lock_scrl_OFF);
    unispace      = qp_load_font_mem(font_unispace18);
}

//----------------------------------------------------------
// UI Drawing
void draw_ui_user(bool force_redraw) {
    bool            hue_redraw = force_redraw;
    static uint16_t last_hue   = 0xFFFF;
#if defined(RGB_MATRIX_ENABLE)
    uint16_t curr_hue = rgb_matrix_get_hue();
#else  // defined(RGB_MATRIX_ENABLE)
    uint16_t curr_hue = 0;
#endif // defined(RGB_MATRIX_ENABLE)
    if (last_hue != curr_hue) {
        last_hue   = curr_hue;
        hue_redraw = true;
    }

    bool            layer_state_redraw = false;
    static uint32_t last_layer_state   = 0;
    if (last_layer_state != layer_state) {
        last_layer_state   = layer_state;
        layer_state_redraw = true;
    }

    bool                     power_state_redraw = false;
    static usbpd_allowance_t last_current_state = (usbpd_allowance_t)(~0);
    if (last_current_state != kb_state.current_setting) {
        last_current_state = kb_state.current_setting;
        power_state_redraw = true;
    }

    bool            scan_redraw      = false;
    static uint32_t last_scan_update = 0;
    if (timer_elapsed32(last_scan_update) > 125) {
        last_scan_update = timer_read32();
        scan_redraw      = true;
    }

    bool            wpm_redraw      = false;
    static uint32_t last_wpm_update = 0;
    if (timer_elapsed32(last_wpm_update) > 125) {
        last_wpm_update = timer_read32();
        wpm_redraw      = true;
    }

    bool            tap_redraw      = false;
    static uint32_t last_tap_update = 0;
    if (timer_elapsed32(last_tap_update) > 125) {
        last_tap_update = timer_read32();
        tap_redraw      = true;
    }

#if defined(RGB_MATRIX_ENABLE)
    bool            rgb_effect_redraw = false;
    static uint16_t last_effect       = 0xFFFF;
    uint8_t         curr_effect       = rgb_matrix_config.mode;
    if (last_effect != curr_effect) {
        last_effect       = curr_effect;
        rgb_effect_redraw = true;
    }

    bool speed_redraw         = false;
    uint8_t curr_speed        = rgb_matrix_config.speed;
    static uint8_t last_speed = 0;
    if (last_speed != curr_speed) {
        last_speed       = curr_speed;
        speed_redraw     = true;
    }

    bool sat_redraw = false;
    static uint8_t last_sat = 0;
    uint8_t curr_sat = rgb_matrix_config.hsv.s;
    if (last_sat != curr_sat) {
        last_sat       = curr_sat;
        sat_redraw     = true;
    }

    bool val_redraw = false;
    static uint8_t last_val = 0;
    uint8_t curr_val = rgb_matrix_config.hsv.v;
    if (last_val != curr_val) {
        last_val       = curr_val;
        val_redraw     = true;
    }

#endif // defined(RGB_MATRIX_ENABLE)

    // Show the main picture
    if (hue_redraw) {
        qp_drawimage(lcd, 120 - frieren->width / 2, 0, frieren);
    }

    int ypos = 2;

    // Show layer info on the left side
    if (is_keyboard_left()) {
        char buf[64] = {0};
        int  xpos    = 2;

#if defined(RGB_MATRIX_ENABLE)
        if (hue_redraw || rgb_effect_redraw) {
            static int max_rgb_xpos = 0;
            xpos                    = 2;
            snprintf(buf, sizeof(buf), "rgb: %s", rgb_matrix_get_mode_name(curr_effect));

            for (int i = 5; i < sizeof(buf); ++i) {
                if (buf[i] == 0)
                    break;
                else if (buf[i] == '_')
                    buf[i] = ' ';
                else if (buf[i - 1] == ' ')
                    buf[i] = toupper(buf[i]);
                else if (buf[i - 1] != ' ')
                    buf[i] = tolower(buf[i]);
            }

            xpos += qp_drawtext_recolor(lcd, xpos, ypos, unispace, buf, curr_hue, 255, 255, curr_hue, 255, 0);
            if (max_rgb_xpos < xpos) {
                max_rgb_xpos = xpos;
            }
            qp_rect(lcd, xpos, ypos, max_rgb_xpos, ypos + unispace->line_height, 0, 0, 0, true);
        }

        ypos += unispace->line_height + 2;

        if (hue_redraw || speed_redraw) {
            static int max_speed_xpos = 0;
            xpos                    = 2;
            snprintf(buf, sizeof(buf), "rgb spd: %d", curr_speed);
            xpos += qp_drawtext_recolor(lcd, xpos, ypos, unispace, buf, curr_hue, 255, 255, curr_hue, 255, 0);
            if (max_speed_xpos < xpos) {
                max_speed_xpos = xpos;
            }
            qp_rect(lcd, xpos, ypos, max_speed_xpos, ypos + unispace->line_height, 0, 0, 0, true);
        }

        ypos += unispace->line_height + 2;

        if (hue_redraw) {
            static int max_hue_xpos = 0;
            xpos                    = 2;
            snprintf(buf, sizeof(buf), "rgb hue: %d", curr_hue);
            xpos += qp_drawtext_recolor(lcd, xpos, ypos, unispace, buf, curr_hue, 255, 255, curr_hue, 255, 0);
            if (max_hue_xpos < xpos) {
                max_hue_xpos = xpos;
            }
            qp_rect(lcd, xpos, ypos, max_hue_xpos, ypos + unispace->line_height, 0, 0, 0, true);
        }

        ypos += unispace->line_height + 2;

        if (hue_redraw || sat_redraw) {
            static int max_sat_xpos = 0;
            xpos                    = 2;
            snprintf(buf, sizeof(buf), "rgb sat: %d", curr_sat);
            xpos += qp_drawtext_recolor(lcd, xpos, ypos, unispace, buf, curr_hue, 255, 255, curr_hue, 255, 0);
            if (max_sat_xpos < xpos) {
                max_sat_xpos = xpos;
            }
            qp_rect(lcd, xpos, ypos, max_sat_xpos, ypos + unispace->line_height, 0, 0, 0, true);
        }

        ypos += unispace->line_height + 2;

        if (hue_redraw || val_redraw) {
            static int max_val_xpos = 0;
            xpos                    = 2;
            snprintf(buf, sizeof(buf), "rgb val: %d", curr_val);
            xpos += qp_drawtext_recolor(lcd, xpos, ypos, unispace, buf, curr_hue, 255, 255, curr_hue, 255, 0);
            if (max_val_xpos < xpos) {
                max_val_xpos = xpos;
            }
            qp_rect(lcd, xpos, ypos, max_val_xpos, ypos + unispace->line_height, 0, 0, 0, true);
        }

        ypos += unispace->line_height + 2;
#endif // defined(RGB_MATRIX_ENABLE)

        if (hue_redraw || layer_state_redraw) {
            extern const char *current_layer_name(void);
            const char        *layer_name = current_layer_name();

            static int max_layer_xpos = 0;
            xpos                      = 2;
            snprintf(buf, sizeof(buf), "layer: %s", layer_name);
            xpos += qp_drawtext_recolor(lcd, xpos, ypos, unispace, buf, curr_hue, 255, 255, curr_hue, 255, 0);
            if (max_layer_xpos < xpos) {
                max_layer_xpos = xpos;
            }
            qp_rect(lcd, xpos, ypos, max_layer_xpos, ypos + unispace->line_height, 0, 0, 0, true);
        }

        ypos += unispace->line_height + 64;

        if (hue_redraw || power_state_redraw) {
            static int max_power_xpos = 0;
            xpos                      = 2;
            snprintf(buf, sizeof(buf), "power: %s", usbpd_str(kb_state.current_setting));
            xpos += qp_drawtext_recolor(lcd, xpos, ypos, unispace, buf, curr_hue, 255, 255, curr_hue, 255, 0);
            if (max_power_xpos < xpos) {
                max_power_xpos = xpos;
            }
            qp_rect(lcd, xpos, ypos, max_power_xpos, ypos + unispace->line_height, 0, 0, 0, true);
        }

        ypos += unispace->line_height + 2;

        if (hue_redraw || scan_redraw) {
            static int max_scans_xpos = 0;
            xpos                      = 2;
            snprintf(buf, sizeof(buf), "scans: %d", (int)theme_state.scan_rate);
            xpos += qp_drawtext_recolor(lcd, xpos, ypos, unispace, buf, curr_hue, 255, 255, curr_hue, 255, 0);
            if (max_scans_xpos < xpos) {
                max_scans_xpos = xpos;
            }
            qp_rect(lcd, xpos, ypos, max_scans_xpos, ypos + unispace->line_height, 0, 0, 0, true);
        }

        ypos += unispace->line_height + 2;

        if (hue_redraw || wpm_redraw) {
            static int max_wpm_xpos = 0;
            xpos                    = 2;
            snprintf(buf, sizeof(buf), "wpm: %d", (int)get_current_wpm());
            xpos += qp_drawtext_recolor(lcd, xpos, ypos, unispace, buf, curr_hue, 255, 255, curr_hue, 255, 0);
            if (max_wpm_xpos < xpos) {
                max_wpm_xpos = xpos;
            }
            qp_rect(lcd, xpos, ypos, max_wpm_xpos, ypos + unispace->line_height, 0, 0, 0, true);
        }

        ypos += unispace->line_height + 2;

        if (hue_redraw || tap_redraw) {
            static int max_tap_xpos = 0;
            xpos                    = 2;
            snprintf(buf, sizeof(buf), "tap term: %d ms", g_tapping_term);
            xpos += qp_drawtext_recolor(lcd, xpos, ypos, unispace, buf, curr_hue, 255, 255, curr_hue, 255, 0);
            if (max_tap_xpos < xpos) {
                max_tap_xpos = xpos;
            }
            qp_rect(lcd, xpos, ypos, max_tap_xpos, ypos + unispace->line_height, 0, 0, 0, true);
        }
    }

    // Show LED lock indicators on the right side
    if (!is_keyboard_left()) {
        static led_t last_led_state = {0};
        if (hue_redraw || last_led_state.raw != host_keyboard_led_state().raw) {
            last_led_state.raw = host_keyboard_led_state().raw;
            qp_drawimage_recolor(lcd, 239 - (32 * 3), 0, last_led_state.caps_lock ? lock_caps_on : lock_caps_off, curr_hue, 255, last_led_state.caps_lock ? 255 : 32, curr_hue, 255, 0);
            qp_drawimage_recolor(lcd, 239 - (32 * 2), 0, last_led_state.num_lock ? lock_num_on : lock_num_off, curr_hue, 255, last_led_state.num_lock ? 255 : 32, curr_hue, 255, 0);
            qp_drawimage_recolor(lcd, 239 - (32 * 1), 0, last_led_state.scroll_lock ? lock_scrl_on : lock_scrl_off, curr_hue, 255, last_led_state.scroll_lock ? 255 : 32, curr_hue, 255, 0);
        }
    }
}

//----------------------------------------------------------
// Sync

theme_runtime_config theme_state;

void rpc_theme_sync_callback(uint8_t m2s_size, const void *m2s_buffer, uint8_t s2m_size, void *s2m_buffer) {
    if (m2s_size == sizeof(theme_state)) {
        memcpy(&theme_state, m2s_buffer, m2s_size);
    }
}

void theme_init(void) {
    // Register keyboard state sync split transaction
    transaction_register_rpc(THEME_DATA_SYNC, rpc_theme_sync_callback);

    // Reset the initial shared data value between master and slave
    memset(&theme_state, 0, sizeof(theme_state));
}

void theme_state_update(void) {
    if (is_keyboard_master()) {
        // Keep the scan rate in sync
        theme_state.scan_rate = get_matrix_scan_rate();
    }
}

void theme_state_sync(void) {
    if (!is_transport_connected()) return;

    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to slave
        static theme_runtime_config last_theme_state;
        static uint32_t             last_sync;
        bool                        needs_sync = false;

        // Check if the state values are different
        if (memcmp(&theme_state, &last_theme_state, sizeof(theme_runtime_config))) {
            needs_sync = true;
            memcpy(&last_theme_state, &theme_state, sizeof(theme_runtime_config));
        }

        // Send to slave every 125ms regardless of state change
        if (timer_elapsed32(last_sync) > 125) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(THEME_DATA_SYNC, sizeof(theme_runtime_config), &theme_state)) {
                last_sync = timer_read32();
            } else {
                dprint("Failed to perform rpc call\n");
            }
        }
    }
}
