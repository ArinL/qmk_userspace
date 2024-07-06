/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
   Copyright 2021 Jonavin Eng @Jonavin
   Copyright 2024 arinl <arinl@tuta.io>
   
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Note: Several advanced functions referenced in this file (like Tap Dance functions) are defined in /users/arinl/arinl.c

#include QMK_KEYBOARD_H

#include "rgb_matrix_map.h"

#include "arinl.h"

#include <math.h>

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Base Layout
     *
     * ,-------------------------------------------------------------------------------------------------------------.
     * | Esc  ||  F1  |  F2  |  F3  |  F4  ||  F5  |  F6  |  F7  |  F8  ||  F9  | F10  | F11  | F12  || Del  || Mute |
     * |=============================================================================================================|
     * |  ` ~ |  1 ! |  2 @ |  3 # |  4 $ |  5 % |  6 ^ |  7 & |  8 * |  9 ( |  0 ) |  - _ |  = + |  Backspc || Home |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+----------++------|
     * |   Tab   |  Q   |  W   |  E   |  R   |  T   |  Y   |  U   |  I   |  O   |  P   | [ }  | ] }  |  \ |  || PgUp |
     * |---------+------+------+------+------+------+------+------+------+------+------+------+------+-------++------|
     * |  Capslock  |  A   |  S   |  D   |  F  |  G   |  H   |  J   |  K   |  L   | ; :  | ' "  |    Enter   || PgDn |
     * |------------+------+------+------+-----+------+------+------+------+------+------+------|----+========+------|
     * |    LShift    |  Z   |  X   |  C   |  V   |  B   |  N   |  M   | , <  | . >  | / ?  | RShift ||  Up  || End  |
     * |--------------+------+------+------+------+------+------+------+------+------+------+--+=====++------++======|
     * |  Ctrl  |   Win  |  LAlt  |               Space                  | RAlt |  Fn  | Ctrl || Left | Down || Rght |
     * `-------------------------------------------------------------------------------------------------------------'
     */

    [_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,           KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS,          KC_A, KC_S, KC_D, KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_FN1),KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN1] = LAYOUT(
        EE_CLR,  _______, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_PAUS, KC_SCRL, KC_PSCR,  KC_INS,           KC_SLEP,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,           _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, LOCKPC,  _______, _______,          _______,           _______,
        _______,         RGB_NITE, RGB_TOG, _______, _______, _______,  KC_NUM, _______, _______, _______, _______,          _______,  RGB_MOD, _______,
        _______, KC_WINLCK, _______,                          _______,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),

    [_FN2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______,   KC_P7,   KC_P8, KC_P9,   _______, KC_PMNS, KC_PPLS, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______,   KC_P4,   KC_P5, KC_P6,   _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______,   KC_P1,   KC_P2, KC_P3,   _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______,   KC_P0, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

    [_FN3] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_0,    _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                               KC_W,                            _______, _______, _______, _______, _______, _______
    ),
    
    [_FN4] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, KC_MCRO4,_______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, KC_MCRO2,KC_MCRO3,KC_MCRO1,_______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
};

#if defined(ENCODER_ENABLE) && !defined(ENCODER_DEFAULTACTIONS_ENABLE) // Encoder Functionality when not using userspace defaults
// https://docs.qmk.fm/features/encoders#callbacks encoder_update_user()
bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t mods_state = get_mods();
    if (mods_state & MOD_BIT(KC_LSFT)) {            // if holding Lshift, change layers
        encoder_action_layerchange(clockwise);
    } else if (mods_state & MOD_BIT(KC_RSFT)) {     // if holding Rshift, change rgb saturation
        encoder_action_rgb_saturation(clockwise);
    } else if (mods_state & MOD_BIT(KC_RCTL)) {     // if holding RCtrl, change rgb hue/colour
        encoder_action_rgb_hue(clockwise);
    } else if (mods_state & MOD_BIT(KC_RALT)) {     // if holding LAlt, change rgb brightness
        encoder_action_rgb_brightness(clockwise);
    } else {                                        // default action changes volume, unless on _FN1 layer
        switch (get_highest_layer(layer_state)) {
        case _FN1:
            #ifdef IDLE_TIMEOUT_ENABLE
            timeout_update_threshold(clockwise);    // updates rgb timeout
            #endif
            break;
        default:
            encoder_action_volume(clockwise);       // ochanges volume
            break;
        }
    }
    return false;
}
#endif // ENCODER_ENABLE && !ENCODER_DEFAULTACTIONS_ENABLE

#ifdef RGB_MATRIX_ENABLE

// RGB matrix setup
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Nightmode RGB setup
    if (get_rgb_nightmode()) rgb_matrix_set_color_all(RGB_OFF);

    led_t led_state = host_keyboard_led_state();
    // ScrollLock RGB setup
    if (led_state.scroll_lock) { 
        rgb_matrix_set_color(LED_F11, RGB_RED);
    }

    // NumLock RGB setup
    #ifdef INVERT_NUMLOCK_INDICATOR
    if (!led_state.num_lock) { // on if NUM lock is OFF
        rgb_matrix_set_color(LED_N, RGB_ORANGE2);
        rgb_matrix_set_color(LED_FN, RGB_ORANGE2);
    }
    #else
    if (led_state.num_lock) { // Normal, on if NUM lock is ON
        rgb_matrix_set_color(LED_N, RGB_ORANGE2);
        rgb_matrix_set_color(LED_FN, RGB_ORANGE2);
    }
    #endif // INVERT_NUMLOCK_INDICATOR

    // CapsLock RGB setup
    if (led_state.caps_lock) {
        rgb_matrix_set_color(LED_L6, RGB_WHITE);
        rgb_matrix_set_color(LED_L7, RGB_WHITE);
        rgb_matrix_set_color(LED_L8, RGB_WHITE);
        rgb_matrix_set_color(LED_CAPS, RGB_WHITE);
    }

    // Winkey RGB setup
    if (keymap_config.no_gui) {
        rgb_matrix_set_color(LED_LWIN, RGB_RED); // RGB_RED when Winkey disabled
    }

    // Fn selector mode RGB setup
    switch (get_highest_layer(layer_state)) { // Handle layer RGB states
    case _FN1: 
        rgb_matrix_set_color(LED_F6, RGB_RED);
        rgb_matrix_set_color(LED_F7, RGB_RED);
        rgb_matrix_set_color(LED_F8, RGB_RED);

        rgb_matrix_set_color(LED_F10, RGB_YELLOW2);
        rgb_matrix_set_color(LED_F11, RGB_YELLOW2);
        rgb_matrix_set_color(LED_F12, RGB_YELLOW2);
        rgb_matrix_set_color(LED_INS, RGB_YELLOW2);

        rgb_matrix_set_color(LED_FN, RGB_OFFBLUE);

        rgb_matrix_set_color(LED_LWIN, RGB_RED);
        rgb_matrix_set_color(LED_BSLS, RGB_RED);

        rgb_matrix_set_color(LED_N, RGB_ORANGE2);

        rgb_matrix_set_color(LED_RALT, RGB_RED);
        rgb_matrix_set_color(LED_RCTL, RGB_GREEN);
        rgb_matrix_set_color(LED_RSFT, RGB_BLUE);

        rgb_matrix_set_color(LED_Z, RGB_PURPLE2);
        rgb_matrix_set_color(LED_X, RGB_PURPLE2);
        rgb_matrix_set_color(LED_UP, RGB_GREEN);
        rgb_matrix_set_color(LED_DOWN, RGB_GREEN);
        rgb_matrix_set_color(LED_LEFT, RGB_BLUE);
        rgb_matrix_set_color(LED_RIGHT, RGB_BLUE);

        // RGB Timeout Indicator -- shows 0 to 139 using F row and num row; larger numbers using 16bit code
        uint16_t timeout_threshold = get_timeout_threshold();
        if (timeout_threshold <= 10) rgb_matrix_set_color(LED_LIST_FUNCROW[timeout_threshold], RGB_CYAN);
        else if (timeout_threshold < 140) {
            rgb_matrix_set_color(LED_LIST_FUNCROW[(timeout_threshold / 10)], RGB_CYAN);
            rgb_matrix_set_color(LED_LIST_NUMROW[(timeout_threshold % 10)], RGB_CYAN);
        } else { // >= 140 minutes, just show these 3 lights
            rgb_matrix_set_color(LED_LIST_NUMROW[10], RGB_CYAN);
            rgb_matrix_set_color(LED_LIST_NUMROW[11], RGB_CYAN);
            rgb_matrix_set_color(LED_LIST_NUMROW[12], RGB_CYAN);
        }

        // SIDE LEDS
        rgb_matrix_set_color(LED_L7, RGB_PURPLE2);
        rgb_matrix_set_color(LED_L8, RGB_PURPLE2);
        rgb_matrix_set_color(LED_R7, RGB_PURPLE2);
        rgb_matrix_set_color(LED_R8, RGB_PURPLE2);
        break;

    case _FN2: // Numpad overlay RGB
        for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_NUMPAD); i++) {
            rgb_matrix_set_color(LED_LIST_NUMPAD[i], RGB_OFFBLUE);
        }
        // SIDE LEDS
        rgb_matrix_set_color(LED_L5, RGB_PURPLE2);
        rgb_matrix_set_color(LED_L6, RGB_PURPLE2);
        rgb_matrix_set_color(LED_R5, RGB_PURPLE2);
        rgb_matrix_set_color(LED_R6, RGB_PURPLE2);

        break;

    case _FN3: // SF mode RGB
        // SIDE LEDS
        rgb_matrix_set_color(LED_L3, RGB_ORANGE2);
        rgb_matrix_set_color(LED_L4, RGB_ORANGE2);
        rgb_matrix_set_color(LED_R3, RGB_ORANGE2);
        rgb_matrix_set_color(LED_R4, RGB_ORANGE2);
        break;

    case _FN4: // GG mode RGB
        // SIDE LEDS
        rgb_matrix_set_color(LED_L1, RGB_DKRED);
        rgb_matrix_set_color(LED_L2, RGB_DKRED);
        rgb_matrix_set_color(LED_R1, RGB_DKRED);
        rgb_matrix_set_color(LED_R2, RGB_DKRED);
        break;

    default:
        break;
    }
    return false;
}
#endif

void keyboard_post_init_keymap(void) {
    // keyboard_post_init_user() moved to userspace
    #ifdef RGB_MATRIX_ENABLE
    activate_rgb_nightmode(false); // Set to true if you want to startup in nightmode, otherwise use Fn + Z to toggle
    #endif
}
