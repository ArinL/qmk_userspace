/* Copyright 2021 Jonavin Eng @Jonavin
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

#pragma once

// LAYERS -- Note: to avoid compile problems, make sure total layers matches DYNAMIC_KEYMAP_LAYER_COUNT defined in config.h (where _COLEMAK layer is defined)
enum custom_user_layers {
    _BASE,
    _FN1,
    _FN2,
    _FN3,
    _FN4
};

#define LOCKPC LGUI(KC_L)

// KEYCODES
enum custom_user_keycodes {
        ENCFUNC  = SAFE_RANGE,
        KC_WINLCK,     // Toggles Win key on and off
        RGB_TOI,       // Timeout idle time up
        RGB_TOD,       // Timeout idle time down
        RGB_NITE,      // Turns off all rgb but allow rgb indicators to work

        KC_MCRO1,
        KC_MCRO2,
        KC_MCRO3,
        KC_MCRO4,

        NEW_SAFE_RANGE // New safe range for keymap level custom keycodes
};

// ENCODER ACTIONS
#ifdef ENCODER_ENABLE
void encoder_action_volume(bool clockwise);
void encoder_action_mediatrack(bool clockwise);
void encoder_action_navword(bool clockwise);
void encoder_action_navpage(bool clockwise);

uint8_t get_selected_layer(void);
void encoder_action_layerchange(bool clockwise);

#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
void encoder_action_rgb_speed(bool clockwise);
void encoder_action_rgb_hue(bool clockwise);
void encoder_action_rgb_saturation(bool clockwise);
void encoder_action_rgb_brightness(bool clockwise);
void encoder_action_rgb_mode(bool clockwise);
#endif // RGB_MATRIX_ENABLE / RGBLIGHT_ENABLE
#endif // ENCODER_ENABLE

#ifdef RGB_MATRIX_ENABLE
void activate_rgb_nightmode(bool turn_on);
bool get_rgb_nightmode(void);
#endif

// IDLE TIMEOUTS
#ifdef IDLE_TIMEOUT_ENABLE
#define TIMEOUT_THRESHOLD_DEFAULT 4 // default timeout minutes
#define TIMEOUT_THRESHOLD_MAX 140 // upper limits (2 hours and 10 minutes -- no rgb indicators above this value)
//prototype  functions
uint16_t get_timeout_threshold(void);
void timeout_reset_timer(void);
void timeout_update_threshold(bool increase);
void timeout_tick_timer(void);
#endif //IDLE_TIMEOUT_ENABLE

// OTHER FUNCTION PROTOTYPE
void activate_numlock(bool turn_on);