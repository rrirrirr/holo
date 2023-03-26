/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a KC_D of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "keymap_swedish.h"
#include "sendstring_swedish.h"

enum layers {
    _HOELOEKAK = 0,
    _HOELOE,
    _NUMBERS,
    _MOVEMENT,
    _VIEW,
    _SELECT,
    _SEARCH,
    _CURSOR,
    _WORD,
    _SYMBOLS,
    _SELECT_SHIFT,
    _SEARCH_SHIFT,
    _WORD_SHIFT
};

#define KC_AA SE_ARNG
#define KC_AE SE_ADIA
#define KC_OE SE_ODIA
// Aliases for readability
#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define CTL_Q MT(MOD_RCTL, KC_Q)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)
#define SPWIN  MT(MOD_LGUI, S(KC_SPACE))
#define TABMV  MT(MOD_LGUI|MOD_LCTL, LGUI(KC_TAB))


#define LESC MT(MOD_LALT, KC_ESC)
#define LO LT(_VIEW, KC_O) 
#define LI LT(_SELECT, KC_I) 
#define LH LT(_MOVEMENT, KC_H) 
#define LE LT(_SEARCH, KC_E) 
#define LR LT(_CURSOR, KC_R) 
#define LWORD LT(_WORD, KC_Y) 

#define LSYM LT(_SYMBOLS, KC_Y) 
#define LNUM LT(_NUMBERS, KC_Y) 


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(0,SE_EQL):
           if (record->tap.count && record->event.pressed) {
                tap_code16(SE_EQL); // Intercept tap function to send Ctrl-C
            } else if (record->event.pressed) {
                 SEND_STRING("=>");
            }
            return false;
        case MT(MOD_LGUI|MOD_LCTL, LGUI(KC_TAB)):
            if (record->tap.count && record->event.pressed) {
                tap_code16(LGUI(KC_TAB)); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case LT(0,LGUI(KC_M)):
           if (record->tap.count && record->event.pressed) {
                tap_code16(LGUI(KC_M)); // Intercept tap function to send Ctrl-C
            } else if (record->event.pressed) {
                tap_code16(LCAG(KC_Z)); // Intercept hold function to send Ctrl-V
            }
            return false;
        case LT(0,SE_DOT):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(SE_COLN); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case LT(0,C(SE_1)):
           if (record->tap.count && record->event.pressed) {
                 SEND_STRING("_");
            } else if (record->event.pressed) {
                 SEND_STRING("<-");
            }
            return false;
        case LT(0,SE_MINS):
            if (!record->tap.count && record->event.pressed) {
                // tap_code16(); // Intercept hold function to send Ctrl-C
                 SEND_STRING("->");
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case LT(0,SE_COMM):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(SE_SCLN); // Intercept hold function to send Ctrl-V
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
    }
    return true;
}
// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |Ctrl/' "|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | [ {  |CapsLk|  |F-keys|  ] } |   N  |   M  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Adjust| LGUI | LAlt/| Space| Nav  |  | Sym  | Space| AltGr| RGUI | Menu |
 *                        |      |      | Enter|      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_HOELOE] = LAYOUT(
     S(KC_ESC), KC_TAB ,KC_Y   ,  KC_O  ,   KC_QUOT, KC_B ,                                     	  KC_C,   KC_F ,  KC_L ,   KC_P, KC_Z, KC_BSPC,
     LESC,     KC_H ,  KC_I   ,  KC_E  ,   KC_A ,   KC_G ,                                        KC_D,   KC_T ,  KC_N ,   KC_S, KC_R, CTL_QUOT,
     KC_LCTL ,  KC_Q ,  KC_LBRC,  KC_SCLN,  KC_U ,   KC_K , KC_DEL,KC_CAPS,   				  KC_S,   KC_BSPC,    KC_J,   KC_M ,   KC_V, KC_W, KC_X, KC_RSFT,
                                KC_S   , KC_LGUI, ALT_ENT, SFT_T(KC_SPC), KC_S   ,    KC_S  , LT(_NUMBERS, KC_SPC) ,LT(_SYMBOLS, KC_S ), KC_RGUI, KC_APP
    ),
    [_HOELOEKAK] = LAYOUT(
     RCS(KC_ESC), KC_TAB, KC_Y ,   LO    ,  KC_AE, KC_B ,                                        KC_C,   KC_F ,  KC_L ,   KC_P ,  KC_Z , KC_KB_VOLUME_UP,
     LESC,		  LH ,  LI   ,   LE  ,    KC_A ,   KC_G ,                                        KC_D,   KC_T ,  KC_N ,   KC_S ,  LR,    LSG(KC_U),
     KC_LCTL ,  CTL_Q ,  KC_AA, KC_OE, KC_U ,   KC_K , KC_BTN1,  	KC_BTN2,       	KC_BTN1,  	KC_BTN2, KC_J,   KC_M ,  KC_V,    KC_W ,  KC_X,  		 KC_KB_VOLUME_DOWN,
                              LGUI(KC_Y) , KC_LALT, LWORD, SFT_T(KC_SPC), SPWIN  ,  TABMV, LT(_NUMBERS,KC_ENT) ,LT(_SYMBOLS, KC_S), LT(0, LGUI(KC_M)), LGUI(KC_M)
    ),


    [_SELECT] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, KC_F8,   KC_P, _______, _______,
      _______, _______, _______, _______, _______, _______,                                     KC_D,    KC_F5,   KC_F6,   KC_F7, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_SELECT_SHIFT] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, S(KC_F8),   KC_P, _______, _______,
      _______, _______, _______, _______, _______, _______,                                     KC_D,    S(KC_F5),   S(KC_F6),   S(KC_F7), _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_WORD] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, KC_F4,   _______, _______, _______,
      _______, MO(_WORD_SHIFT), _______, _______, _______, KC_DEL,                               KC_BSPC, KC_F1,   KC_F2,   KC_F3, _______, _______,
      _______, RCS(KC_ESC), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                           _______, _______, _______, _______, _______,            _______, _______, KC_TAB, _______, _______
    ),
    [_WORD_SHIFT] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, S(KC_F4),   _______, _______, _______,
      _______, _______, _______, _______, _______, S(KC_DEL),                               S(KC_BSPC),  S(KC_F1),   S(KC_F2),   S(KC_F3), _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_SEARCH] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, KC_F12,   _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                                     _______,  KC_F9,  KC_F10,   KC_F11, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_SEARCH_SHIFT] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, KC_F4,   _______, _______, _______,
      _______, _______, _______, _______, _______, KC_DEL,                                     KC_BSPC,    KC_F1,   KC_F2,   KC_F3, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_CURSOR] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, C(KC_F8),   _______, _______, _______,
      _______, LCA(KC_H), LCA(KC_I), LCA(KC_E), LCA(KC_A), LCA(KC_G),    								LCA(KC_D), C(KC_F1), C(KC_F6),  C(KC_F3), LCA(KC_R), _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_VIEW] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, KC_PGUP,  _______, _______, _______,
      _______, _______, _______, _______, _______, KC_DEL,                                     KC_BSPC, S(KC_TAB), KC_PGDN,   KC_TAB, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_SYMBOLS] = LAYOUT(
      _______, _______, S(SE_3), ALGR(SE_2), SE_TILD, SE_PIPE,                                       _______, _______, SE_DLR, _______, _______, _______,
      _______, SE_LABK, SE_RABK, S(SE_8), SE_LCBR, SE_LBRC,                                      LCA(SE_PLUS), S(SE_2), SE_SLSH, SE_QUOT , SE_GRV, _______,
      _______, RCS(KC_ESC), _______, S(SE_9), SE_RCBR, SE_RBRC, _______, _______,           _______, _______, LCA(SE_PLUS), SE_BSLS, SE_BSLS, SE_QUOT, SE_GRV, _______,
                                 _______, _______, LGUI(KC_Y), KC_TAB, LCAG(KC_Z),								 _______, KC_TAB, _______, _______, _______
    ),
    [_NUMBERS] = LAYOUT(
      _______, _______, SE_CIRC, SE_ASTR, SE_PLUS, S(SE_5),                                       _______,   SE_4,   SE_5,   SE_6, _______, _______,
     _______, LT(0,C(SE_1)), LT(0,SE_MINS), LT(0,SE_DOT), LT(0,SE_COMM), S(SE_PLUS),             SE_0,    SE_1,   SE_2,   SE_3, _______, _______,
      _______, RCS(KC_ESC), _______, S(SE_6), S(SE_1), LT(0,SE_EQL), _______, _______, _______, _______, _______,   SE_7,   SE_8,   SE_9, _______, _______,
                           _______, _______, LGUI(KC_Y), KC_TAB, LCAG(KC_Z),      _______, _______, _______, _______, _______
    ),
    [_MOVEMENT] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, KC_UP,   _______, _______, _______,
      _______, _______, _______, _______, _______, KC_DEL,                                     KC_BSPC,    KC_LEFT,   KC_DOWN,   KC_RIGHT, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * For your convenience, here's a KC_D of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

/* DELETE THIS LINE TO UNCOMMENT (1/2)
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // QMK Logo and version information
        // clang-format off
        static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        oled_write_P(qmk_logo, false);
        oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _QWERTY:
                oled_write_P(PSTR("QWERTY\n"), false);
                break;
            case _DVORAK:
                oled_write_P(PSTR("Dvorak\n"), false);
                break;
            case _COLEMAK_DH:
                oled_write_P(PSTR("Colemak-DH\n"), false);
                break;
            case _NAV:
                oled_write_P(PSTR("Nav\n"), false);
                break;
            case _SYM:
                oled_write_P(PSTR("Sym\n"), false);
                break;
            case _FUNCTION:
                oled_write_P(PSTR("Function\n"), false);
                break;
            case _ADJUST:
                oled_write_P(PSTR("Adjust\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    } else {
        // clang-format off
        static const char PROGMEM kyria_logo[] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
            0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
        };
        // clang-format on
        oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
    }
    return false;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}
#endif
DELETE THIS LINE TO UNCOMMENT (2/2) */

