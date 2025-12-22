// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "theme.h"

// Layer definitions
enum { _QWERTY, _LOWER, _RAISE, _ADJUST };

enum custom_keycodes {
    MAC_TOGGLE = SAFE_RANGE
};

//----------------------------------------------------------
// Key map

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        QK_GESC,  KC_1,   KC_2,    KC_3,    KC_4,      KC_5,    KC_GRV,                              KC_DEL,  KC_6,     KC_7,      KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,      KC_T,    KC_LBRC,                             KC_RBRC, KC_Y,     KC_U,      KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,      KC_G,    KC_HOME,                             KC_PGUP, KC_H,     KC_J,      KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,      KC_B,    KC_END,                              KC_PGDN, KC_N,     KC_M,      KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                   KC_LALT, KC_LGUI,  KC_SPC,  MO(_LOWER),                          MO(_RAISE),  KC_SPC,  KC_BSPC,KC_ENT,
                                                                    KC_MPLY,               KC_MUTE,
                                                       KC_UP,                                                 KC_UP,
                                            KC_LEFT,   KC_ENT, KC_RIGHT,                            KC_LEFT, KC_ENT, KC_RIGHT,
                                                       KC_DOWN,                                               KC_DOWN
    ),
    [_LOWER] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,     KC_F5,   _______,                             _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, _______, KC_UP,   _______, _______,   _______, _______,                             _______, _______, _______, _______, _______, _______, KC_F12,
        _______, KC_LEFT, KC_DOWN, KC_RIGHT,_______,   _______, NK_TOGG,                             DT_UP,   _______, _______, _______, _______, _______, _______,
        KC_CAPS, _______, _______, _______, _______,   DJ_POWR, AU_TOGG,                             DT_DOWN, _______, _______, _______, _______, _______, _______,
                                   KC_RALT, _______,   _______, _______,                             MO(_ADJUST), _______, _______, _______,
                                                                    RM_PREV,               RM_NEXT,
                                                     _______,                                               _______,
                                            _______,   _______, _______,                             _______, _______, _______,
                                                     _______,                                               _______
    ),
    [_RAISE] = LAYOUT(
        KC_ESC, KC_F1,   KC_F2,    KC_F3,   KC_F4,     KC_F5,   _______,                             _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______,_______, KC_UP,    _______, _______,   _______, _______,                             _______, _______, _______, _______, _______, _______, KC_F12,
        _______,KC_LEFT, KC_DOWN,  KC_RIGHT,_______,   KC_UNDS, KC_NO,                               KC_NO,   KC_EQL,  _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,   KC_MINS, KC_NO,                               KC_NO,   KC_PLUS, _______, _______, _______, _______, _______,
                                   _______, _______,   _______, MO(_ADJUST),                             _______, _______, _______, _______,
                                                                    BL_DOWN,               BL_UP,
                                                     _______,                                               _______,
                                            _______,   _______, _______,                             _______, _______, _______,
                                                     _______,                                               _______
    ),
    [_ADJUST] = LAYOUT(
        QK_REBOOT, KC_CAPS, KC_NUM,  KC_SCRL, KC_RCTL,   _______, _______,                           _______, _______, _______, _______, DB_TOGG, EE_CLR,  QK_BOOT,
        _______, _______, _______, _______, _______,   _______, _______,                             _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,   _______, _______,                             _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,   _______, _______,                             _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______,   _______, _______,                             _______, _______, _______, _______,
                                                                      _______,               _______,
                                                     _______,                                               _______,
                                            _______,   _______, _______,                             _______, _______, _______,
                                                     _______,                                               _______
    )
};

#define __OFF__ {RGB_BLACK}
#define RED {RGB_RED}
#define CORAL {RGB_CORAL}
#define ORANGE {RGB_ORANGE}
#define GOLDEN {RGB_GOLDENROD}
#define GOLD {RGB_GOLD}
#define YELLOW {RGB_YELLOW}
#define CHART {RGB_CHARTREUSE}
#define GREEN {RGB_GREEN}
#define SPRING {RGB_SPRINGGREEN}
#define TURQ {RGB_TURQUOISE}
#define TEAL {RGB_TEAL}
#define CYAN {RGB_CYAN}
#define AZURE {RGB_AZURE}
#define BLUE {RGB_BLUE}
#define PURPLE {RGB_PURPLE}
#define MAGENT {RGB_MAGENTA}
#define PINK {RGB_PINK}
#define WHITE {RGB_WHITE}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [_LOWER] = {
        // underglow left side
        SPRING, SPRING, SPRING, SPRING, SPRING, SPRING, SPRING, SPRING, SPRING, SPRING, SPRING,

                                    ORANGE, __OFF__,   __OFF__, __OFF__,

        GREEN, __OFF__, __OFF__, __OFF__, __OFF__,   __OFF__, SPRING,
        __OFF__, BLUE, BLUE, BLUE,__OFF__,   __OFF__, MAGENT,
        __OFF__, __OFF__,  __OFF__, __OFF__, BLUE, __OFF__, __OFF__,
        RED,  GOLD,   GOLD,   GOLD,   GOLD,     GOLD,   __OFF__,

        // underglow right side
        SPRING, SPRING, SPRING, SPRING, SPRING, SPRING, SPRING, SPRING, SPRING, SPRING, SPRING,

        __OFF__, __OFF__, __OFF__, __OFF__,
        TEAL, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__,
        __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, TEAL,
        __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, GOLD,
        GOLD, GOLD,   GOLD,   GOLD,   GOLD,   GOLD,  __OFF__


    },
    [_RAISE] = {
        // underglow left side
        BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE,

                                    __OFF__, __OFF__,   __OFF__, __OFF__,

        __OFF__, CYAN, __OFF__, __OFF__, __OFF__,   __OFF__, SPRING,
        __OFF__, BLUE, BLUE, BLUE,__OFF__,   TURQ, __OFF__,
        __OFF__, __OFF__,  __OFF__, __OFF__, BLUE, __OFF__, __OFF__,
        RED,  GOLD,   GOLD,   GOLD,   GOLD,     GOLD,   __OFF__,

        // underglow right side
        BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE,

        __OFF__, __OFF__, __OFF__, __OFF__,
        __OFF__, MAGENT, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__,
        __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, PURPLE, __OFF__,
        __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, GOLD,
        GOLD, GOLD,   GOLD,   GOLD,   GOLD,   GOLD,  __OFF__

    },
    [_ADJUST] = {
         // underglow left side
        PINK, PINK, PINK, PINK, PINK, PINK, PINK, PINK, PINK, PINK, PINK,

        __OFF__, __OFF__,   __OFF__, __OFF__,

        __OFF__, CYAN, __OFF__, __OFF__, __OFF__,   __OFF__, __OFF__,
        __OFF__, __OFF__, __OFF__, __OFF__,__OFF__,   __OFF__, __OFF__,
        __OFF__, __OFF__,  __OFF__, __OFF__, __OFF__, __OFF__, __OFF__,
        CORAL,  GREEN,   BLUE,   YELLOW,   GOLD,     GOLD,   __OFF__,

        // underglow right side
        PINK, PINK, PINK, PINK, PINK, PINK, PINK, PINK, PINK, PINK, PINK,

        __OFF__, __OFF__, __OFF__, __OFF__,
        __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__,
        __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__,
        __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__,
        PURPLE, PINK,   TURQ,   __OFF__,   __OFF__,   __OFF__,  __OFF__
    }
};

extern rgb_config_t rgb_matrix_config;
bool disable_layer_color;

// clang-format on

//----------------------------------------------------------
// Encoder map

// clang-format off
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY] = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_LOWER]  = { ENCODER_CCW_CW(RM_HUED, RM_HUEU), ENCODER_CCW_CW(RM_SATD, RM_SATU)  },
    [_RAISE]  = { ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(RM_SPDD, RM_SPDU)  },
    [_ADJUST] = { ENCODER_CCW_CW(RM_PREV, RM_NEXT), ENCODER_CCW_CW(KC_LEFT, KC_RIGHT) },
};
// clang-format on

//----------------------------------------------------------
// Layer naming

const char *current_layer_name(void) {
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            return "qwerty";
        case _LOWER:
            return "lower";
        case _RAISE:
            return "raise";
        case _ADJUST:
            return "adjust";
    }
    return "unknown";
}

//----------------------------------------------------------
// Overrides

void keyboard_post_init_user(void) {
    // Initialise the theme
    theme_init();

    void keyboard_post_init_display(void);
    keyboard_post_init_display();
}

void housekeeping_task_user(void) {
    // Update kb_state so we can send to slave
    theme_state_update();

    // Data sync from master to slave
    theme_state_sync();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uprintf("kc: %s\n", get_keycode_string(keycode));
    switch (keycode) {
        case LCTL_T(MAC_TOGGLE):
            if (record->tap.count && record->event.pressed) {
                tap_code16(LCTL(KC_SPACE)); // Send LCTL + SPACE on tap
                return false;
            }
            break;
    }
    return true;
}

void set_layer_color(int layer) {
    if (layer == _QWERTY) {
        return;
    }
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        RGB rgb = {
            .r = pgm_read_byte(&ledmap[layer][i][0]),
            .g = pgm_read_byte(&ledmap[layer][i][1]),
            .b = pgm_read_byte(&ledmap[layer][i][2]),
        };
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
}

bool rgb_matrix_indicators_user(void) {
    if (disable_layer_color || rgb_matrix_get_flags() == LED_FLAG_NONE || rgb_matrix_get_flags() == LED_FLAG_UNDERGLOW) {
        return false;
    }
    set_layer_color(get_highest_layer(layer_state));
    return false;
}
