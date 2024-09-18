#include "keymap.h"

static uint16_t idle_timer;           // Idle LED timeout timer
static uint8_t  idle_second_counter;  // Idle LED seconds counter, counts seconds not milliseconds
static uint8_t  key_event_counter;    // This counter is used to check if any keys are being held

bool     spam_enter;
uint16_t spam_timer    = false;
uint16_t spam_interval = 3000;  // (1000ms == 1s)

// #if defined(KEY_CANCELLATION_ENABLE)
// const key_cancellation_t PROGMEM key_cancellation_list[] = {
//     [0] = {KC_D, KC_A},
//     [1] = {KC_A, KC_D},
// };
// #endif

tap_dance_action_t tap_dance_actions[] = {
    // Tap once for backslash, twice for F13
    [TD_BSLS_F13] = ACTION_TAP_DANCE_DOUBLE(KC_BSLS, KC_F13),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_BSLS_F13):
            return TAPPING_TERM + 50;
        case LT(2, KC_CAPS):
            return 200;
        default:
            return TAPPING_TERM;
    }
}

#define LTCAPS LT(2, KC_CAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,                   KC_PSCR, KC_SCRL, KC_PAUS, \
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,         KC_INS,  KC_HOME, KC_PGUP, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, TD(TD_BSLS_F13), KC_DEL,  KC_END,  KC_PGDN, \
        LTCAPS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                                    KC_UP, \
        KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                             KC_RALT, KC_RGUI,   MO(1),  KC_RCTL,                 KC_LEFT, KC_DOWN, KC_RGHT \
    ),
    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, KC_NUM, KC_MUTE, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   KC_MPLY, KC_MSTP, KC_VOLU, \
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, _______, _______, _______, _______, _______, _______, _______,   KC_MPRV, KC_MNXT, KC_VOLD, \
        _______, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______, _______, \
        _______, RGB_TOG, U_T_AUTO, U_T_AGCR, DBG_TOG, MD_BOOT, NK_TOGG, _______, _______, _______, KC_GFN_AFK, _______,                         _______, \
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______ \
    ),
    [2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______, \
        KC_NUM, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,    _______, _______, _______, _______,   _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   _______, _______, _______, _______,   _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, KC_P0,   KC_P0,   KC_P0,   KC_PDOT, _______, _______,                              _______, \
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______ \
    ),
};

#define __OFF__ {0, 0, 0}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [1] = {
        __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__,            __OFF__, AZURE, RED, \
        __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__,   GREEN,   RED,   SPRING, \
        __OFF__, CYAN,    GOLD,    CYAN,    MAGENT,  AZURE,   __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__,   BLUE,    BLUE,  SPRING, \
        __OFF__, CORAL,   GOLD,    CORAL,   MAGENT,  AZURE,   __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, \
        __OFF__, CHART,   __OFF__,  __OFF__,  __OFF__, RED,     TURQ,    __OFF__, __OFF__, AZURE,   GREEN,  __OFF__,                              __OFF__, \
        __OFF__, __OFF__, __OFF__,                   __OFF__,                            __OFF__, __OFF__, __OFF__, __OFF__,            __OFF__, __OFF__, __OFF__ \
    },
    [2] = {
        __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__,            __OFF__, __OFF__, __OFF__, \
        GREEN,   __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, MAGENT,  MAGENT,  MAGENT,  __OFF__, GREEN,   GREEN,   __OFF__,   __OFF__, __OFF__, __OFF__, \
        __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, MAGENT,  MAGENT,  MAGENT,  __OFF__, __OFF__, __OFF__, __OFF__,   __OFF__, __OFF__, __OFF__, \
        __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, MAGENT,  MAGENT,  MAGENT,  __OFF__, __OFF__, __OFF__, \
        __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, MAGENT,  MAGENT,  MAGENT,  GREEN,   __OFF__, __OFF__,                              __OFF__, \
        __OFF__, __OFF__, __OFF__,                   __OFF__,                            __OFF__, __OFF__, __OFF__, __OFF__,            __OFF__, __OFF__, __OFF__ \
    },
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    // Enable or disable debugging
    debug_enable   = false;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;

    idle_second_counter            = 0;                       // Counter for number of seconds keyboard has been idle.
    key_event_counter              = 0;                       // Counter to determine if keys are being held, neutral at 0.
    rgb_time_out_seconds           = RGB_DEFAULT_TIME_OUT;    // RGB timeout initialized to its default configure in keymap.h
    rgb_time_out_enable            = false;                   // Disable RGB timeout by default. Enable using toggle key.
    rgb_time_out_user_value        = false;                   // Has to have the same initial value as rgb_time_out_enable.
    rgb_enabled_flag               = true;                    // Initially, keyboard RGB is enabled. Change to false config.h initializes RGB disabled.
    rgb_time_out_fast_mode_enabled = false;                   // RGB timeout fast mode disabled initially.
    rgb_time_out_saved_flag        = rgb_matrix_get_flags();  // Save RGB matrix state for when keyboard comes back from ide.
};

void keyboard_post_init_user(void) { rgb_matrix_enable(); }

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    if (rgb_time_out_enable && rgb_enabled_flag) {
        // If the key event counter is not zero then some key was pressed down but not released, thus reset the timeout counter.
        if (key_event_counter) {
            idle_second_counter = 0;
        } else if (timer_elapsed(idle_timer) > MILLISECONDS_IN_SECOND) {
            idle_second_counter++;
            idle_timer = timer_read();
        }
        if (idle_second_counter >= rgb_time_out_seconds) {
            rgb_time_out_saved_flag = rgb_matrix_get_flags();
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_disable_noeeprom();
            rgb_enabled_flag    = false;
            idle_second_counter = 0;
        }
    }
    if (spam_enter && timer_elapsed(spam_timer) >= spam_interval) {
        spam_timer = timer_read();
        SEND_STRING(SS_TAP(X_P));
    }
};

#define MODS_SHIFT (get_mods() & MOD_MASK_SHIFT)
#define MODS_CTRL (get_mods() & MOD_MASK_CTRL)
#define MODS_ALT (get_mods() & MOD_MASK_ALT)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER: {
                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    case LED_FLAG_UNDERGLOW: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_disable_noeeprom();
                    } break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        rgb_matrix_enable_noeeprom();
                    } break;
                }
            }
            return false;
        case KC_GFN_AFK:  // Toggle's if we hit "ENTER" or "BACKSPACE" to input macros
            if (record->event.pressed) {
                spam_enter ^= 1;
                spam_timer = timer_read();
            }
            return false;
        default:
            return true;  // Process all other keycodes normally
    }
}

void set_layer_color(int layer) {
    if (layer == 0) {
        return;
    }
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        HSV hsv = {
            .h = pgm_read_byte(&ledmap[layer][i][0]),
            .s = pgm_read_byte(&ledmap[layer][i][1]),
            .v = pgm_read_byte(&ledmap[layer][i][2]),
        };
        if (hsv.h || hsv.s || hsv.v) {
            RGB   rgb = hsv_to_rgb(hsv);
            float f   = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
            rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);
        //} else if (layer != 1) {
        } else {
            // Only deactivate non-defined key LEDs at layers other than FN. Because at FN we have RGB adjustments and need to see them live.
            // If the values are all false then it's a transparent key and deactivate LED at this layer
            rgb_matrix_set_color(i, 0, 0, 0);
        }
    }
}

void set_underglow_rgb_matrix(void) {
    HSV     hsv  = rgb_matrix_config.hsv;
    uint8_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 5);
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        switch (rgb_matrix_get_flags()) {
            case LED_FLAG_ALL:
            case LED_FLAG_UNDERGLOW:
                if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
                    hsv.h = g_led_config.point[i].x - time;
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                }
                break;
        }
    }
}

bool rgb_matrix_indicators_user(void) {
    if (disable_layer_color || rgb_matrix_get_flags() == LED_FLAG_NONE || rgb_matrix_get_flags() == LED_FLAG_UNDERGLOW) {
        return false;
    }
    set_layer_color(get_highest_layer(layer_state));
    set_underglow_rgb_matrix();
    return false;
}
