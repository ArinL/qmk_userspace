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

#include QMK_KEYBOARD_H

#include "arinl.h"

// RGB NIGHT MODE
#ifdef RGB_MATRIX_ENABLE
static bool rgb_nightmode = false;

// Turn on/off NUM LOCK if current state is different
void activate_rgb_nightmode(bool turn_on) {
    if (rgb_nightmode != turn_on) {
        rgb_nightmode = !rgb_nightmode;
    }
}

bool get_rgb_nightmode(void) {
    return rgb_nightmode;
}
#endif // RGB_MATRIX_ENABLE

// TIMEOUTS
#ifdef IDLE_TIMEOUT_ENABLE
static uint16_t timeout_timer = 0;
static uint16_t timeout_counter = 0; //in minute intervals
static uint16_t timeout_threshold = TIMEOUT_THRESHOLD_DEFAULT;

uint16_t get_timeout_threshold(void) {
    return timeout_threshold;
}

void timeout_reset_timer(void) {
    timeout_timer = timer_read();
    timeout_counter = 0;
};

void timeout_update_threshold(bool increase) {
    if (increase && timeout_threshold < TIMEOUT_THRESHOLD_MAX) timeout_threshold++;
    if (!increase && timeout_threshold > 0) timeout_threshold--;
};

void timeout_tick_timer(void) {
    if (timeout_threshold > 0) {
        if (timer_elapsed(timeout_timer) >= 60000) { // 1 minute tick
            timeout_counter++;
            timeout_timer = timer_read();
        }
        #ifdef RGB_MATRIX_ENABLE
        if (timeout_threshold > 0 && timeout_counter >= timeout_threshold) {
            rgb_matrix_disable_noeeprom();
        }
        #endif
    } // timeout_threshold = 0 will disable timeout
}

#endif // IDLE_TIMEOUT_ENABLE

#if defined(IDLE_TIMEOUT_ENABLE) // timer features
__attribute__((weak)) void matrix_scan_keymap(void) {}

void matrix_scan_user(void) {
    #ifdef IDLE_TIMEOUT_ENABLE
    timeout_tick_timer();
    #endif
    matrix_scan_keymap();
}
#endif // IDLE_TIMEOUT_ENABLE

// Initialize variable holding the binary representation of active modifiers.
uint8_t mod_state;

// ============================================= PROCESS KEY CODES =============================================

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t * record) {
    return true;
}

static bool is_left_pressed, is_right_pressed, is_down_pressed;

bool process_record_user(uint16_t keycode, keyrecord_t * record) {
    mod_state = get_mods();
    if (!process_record_keymap(keycode, record)) {
        return false;
    }

    // Key macros ...
    switch (keycode) {
        // WinKey lock
    case KC_WINLCK:
        if (record -> event.pressed) {
            keymap_config.no_gui = !keymap_config.no_gui; //toggle status
        } else unregister_code16(keycode);
        break;

    case KC_A:
        is_left_pressed= record->event.pressed;
        break;
    case KC_D:
        is_right_pressed = record->event.pressed;
        break;
    case KC_S:
        is_down_pressed = record->event.pressed;
        break;

    case KC_MCRO1: // hpb
         if (record -> event.pressed) {
            if (is_right_pressed || is_left_pressed) {
                if (is_left_pressed) {
                    SEND_STRING(SS_UP(X_A) SS_DELAY(18) SS_DOWN(X_S) SS_DELAY(18) SS_DOWN(X_A) SS_DELAY(18) SS_UP(X_S) SS_DELAY(18) SS_UP(X_A) SS_DELAY(40) SS_DOWN(X_S) SS_DELAY(18) SS_DOWN(X_A) SS_DELAY(18) SS_UP(X_S) SS_DELAY(18));
                }
                if (is_right_pressed) {
                    SEND_STRING(SS_UP(X_D) SS_DELAY(18) SS_DOWN(X_S) SS_DELAY(18) SS_DOWN(X_D) SS_DELAY(18) SS_UP(X_S) SS_DELAY(18) SS_UP(X_D) SS_DELAY(40) SS_DOWN(X_S) SS_DELAY(18) SS_DOWN(X_D) SS_DELAY(18) SS_UP(X_S) SS_DELAY(18));
                }
                if (!(mod_state & MOD_MASK_SHIFT)) {
                    SEND_STRING(SS_DOWN(X_J) SS_DELAY(18) SS_UP(X_J));
                }
                SEND_STRING(SS_DOWN(X_I) SS_DELAY(18) SS_UP(X_I));
                if ((mod_state & MOD_MASK_SHIFT)) {
                    SEND_STRING(SS_DOWN(X_K) SS_DELAY(18) SS_UP(X_K)); 
                }
            } else {
                register_code(KC_COMM);
            }
         } else unregister_code(KC_COMM);
         break;

    case KC_MCRO2: // giganter
         if (record -> event.pressed) {
            if (is_right_pressed || is_left_pressed) {
                if (is_left_pressed) {
                    SEND_STRING(SS_DOWN(X_S) SS_DELAY(18) SS_UP(X_A) SS_DELAY(18) SS_DOWN(X_D) SS_DELAY(18) SS_UP(X_S) SS_DELAY(18) SS_UP(X_D) SS_DELAY(18) SS_DOWN(X_A) SS_DELAY(18));
                }
                if (is_right_pressed) { 
                    SEND_STRING(SS_DOWN(X_S) SS_DELAY(18) SS_UP(X_D) SS_DELAY(18) SS_DOWN(X_A) SS_DELAY(18) SS_UP(X_S) SS_DELAY(18) SS_UP(X_A) SS_DELAY(18) SS_DOWN(X_D) SS_DELAY(18));
                }
                if (!(mod_state & MOD_MASK_SHIFT)) {
                    SEND_STRING(SS_DOWN(X_J) SS_DELAY(18) SS_UP(X_J));
                }
                SEND_STRING(SS_DOWN(X_L) SS_DELAY(18) SS_UP(X_L));
                if ((mod_state & MOD_MASK_SHIFT)) {
                    SEND_STRING(SS_DOWN(X_K) SS_DELAY(18) SS_UP(X_K));
                }
                if (is_down_pressed) {
                    SEND_STRING(SS_DOWN(X_S));
                }
            } else {
                register_code(KC_N);
            }
         } else unregister_code(KC_N);
         break;
    
    case KC_MCRO3: // buster
        if (record -> event.pressed) {
            if (is_right_pressed || is_left_pressed) {
                if (is_left_pressed) {
                    SEND_STRING(SS_DOWN(X_S) SS_DELAY(18) SS_UP(X_A) SS_DELAY(18) SS_DOWN(X_D) SS_DELAY(18) SS_UP(X_S) SS_DELAY(18) SS_UP(X_D) SS_DELAY(18) SS_DOWN(X_A) SS_DELAY(18));
                }
                if (is_right_pressed) { 
                    SEND_STRING(SS_DOWN(X_S) SS_DELAY(18) SS_UP(X_D) SS_DELAY(18) SS_DOWN(X_A) SS_DELAY(18) SS_UP(X_S) SS_DELAY(18) SS_UP(X_A) SS_DELAY(18) SS_DOWN(X_D) SS_DELAY(18));
                }
                if (!(mod_state & MOD_MASK_SHIFT)) { //shift is not pressed
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING(SS_DOWN(X_J) SS_DELAY(18)); 
                    set_mods(mod_state);
                }
                SEND_STRING(SS_DOWN(X_K) SS_DELAY(18) SS_UP(X_J) SS_UP(X_K));
                if (is_down_pressed) {
                    SEND_STRING(SS_DOWN(X_S));
                }
            } else {
                register_code(KC_M);
            }
         } else unregister_code(KC_M);
         break;

    case KC_MCRO4: // flick
        if (record -> event.pressed) {
            // if ((mod_state & MOD_MASK_SHIFT) && (is_right_pressed || is_left_pressed)) {
            if (is_right_pressed || is_left_pressed) {
                if (is_left_pressed) {
                    SEND_STRING(SS_DOWN(X_S) SS_DELAY(18) SS_UP(X_A) SS_DELAY(18) SS_DOWN(X_D) SS_DELAY(18) SS_UP(X_S) SS_DELAY(18) SS_UP(X_D) SS_DELAY(18) SS_DOWN(X_A) SS_DELAY(18));
                }
                if (is_right_pressed) { 
                    SEND_STRING(SS_DOWN(X_S) SS_DELAY(18) SS_UP(X_D) SS_DELAY(18) SS_DOWN(X_A) SS_DELAY(18) SS_UP(X_S) SS_DELAY(18) SS_UP(X_A) SS_DELAY(18) SS_DOWN(X_D) SS_DELAY(18));
                }
                if (is_right_pressed || is_left_pressed) {
                    SEND_STRING(SS_DOWN(X_J) SS_DELAY(18) SS_DOWN(X_I) SS_DELAY(18) SS_UP(X_J) SS_UP(X_I));
                }
            } else {
                register_code(KC_U);
            }
         } else unregister_code(KC_U);
         break;

    #ifdef IDLE_TIMEOUT_ENABLE
    case RGB_TOI:
        if (record -> event.pressed) {
            timeout_update_threshold(true);
        } else unregister_code16(keycode);
        break;
    case RGB_TOD:
        if (record -> event.pressed) {
            timeout_update_threshold(false); //decrease timeout
        } else unregister_code16(keycode);
        break;
        #endif // IDLE_TIMEOUT_ENABLE
        #ifdef RGB_MATRIX_ENABLE
    case RGB_NITE:
        if (record -> event.pressed) {
            rgb_nightmode = !rgb_nightmode;
        } else unregister_code16(keycode);
        break;
        #endif // RGB_MATRIX_ENABLE

    default:
        if (record -> event.pressed) {
            #ifdef RGB_MATRIX_ENABLE
            rgb_matrix_enable();
            #endif
            #ifdef IDLE_TIMEOUT_ENABLE
            timeout_reset_timer(); //reset activity timer
            #endif
        }
        break;
    }
    return true;
};

// Sets numlock on in numpad _FN2 layer
layer_state_t layer_state_set_user(layer_state_t state) {
  static bool adjust_on = false;
  if (adjust_on != IS_LAYER_ON_STATE(state, _FN2)) {
    adjust_on = !adjust_on;
    if (adjust_on) {  // Just entered the _FN2 layer.
      activate_numlock(true);
    } else {          // Just exited the _FN2 layer.
      activate_numlock(false);
    }
  }
  return state;
}

// Turn on/off NUM LOCK if current state is different
void activate_numlock(bool turn_on) {
    if (host_keyboard_led_state().num_lock != turn_on) {
        tap_code(KC_NUM);
    }
}

// INITIAL STARTUP
__attribute__((weak)) void keyboard_post_init_keymap(void) {}

void keyboard_post_init_user(void) {
    keyboard_post_init_keymap();
    #ifdef STARTUP_NUMLOCK_ON
    activate_numlock(true); // turn on Num lock by default so that the numpad layer always has predictable results
    #endif // STARTUP_NUMLOC_ON
    #ifdef IDLE_TIMEOUT_ENABLE
    timeout_timer = timer_read(); // set initial time for idle timeout
    #endif
}