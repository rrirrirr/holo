#include QMK_KEYBOARD_H
#include "keymap_swedish.h"
#include "sendstring_swedish.h"

enum layers {
    _HOELOEKAK = 0,
    _QWERTY,
    _PRACTICE,
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
#define SPWIN  MT(MOD_LGUI, LSG(KC_U))
#define TABMV  MT(MOD_LGUI|MOD_LCTL, LGUI(KC_TAB))


#define LG MT(MOD_LSFT, KC_G)
#define LD MT(MOD_LSFT, KC_D)
#define LY MT(MOD_LALT, KC_Y)

#define LESC MT(MOD_LALT, KC_ESC)
#define LO LT(_VIEW, KC_O)
#define LI LT(_SELECT, KC_I)
#define LH LT(_MOVEMENT, KC_H)
#define LE LT(_SEARCH, KC_E)
#define LR LT(_CURSOR, KC_R)
#define LWORD LT(_WORD, KC_ESC)

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
            return true;
        case MT(MOD_LGUI, LSG(KC_U)):
            if (record->tap.count && record->event.pressed) {
                tap_code16(LSG(KC_U)); // Intercept hold function to send Ctrl-X
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
      * ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
      * │ Q │ W │ E │ R │ T │       │ Y │ U │ I │ O │ P │
      * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
      * │ A │ S │ D │ F │ G │       │ H │ J │ K │ L │ ; │
      * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
      * │ Z │ X │ C │ V │ B │       │ N │ M │ , │ . │ / │
      * └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
      *           ┌───┐                   ┌───┐
      *           │DEL├───┐           ┌───┤ESC│
      *           └───┤SPC├───┐   ┌───┤BSP├───┘
      *               └───│LOW│   │RSE├───┘
      *                   └───┘   └───┘
      */


    [_QWERTY] = LAYOUT_split_3x5_3(
        KC_Q,    KC_W,              KC_E,            KC_R,            KC_T,               KC_Y,         KC_U,              KC_I,              KC_O,           KC_P,
        KC_A,    KC_S,             KC_D,             KC_F,    KC_G,               KC_H,         LSFT_T(KC_J),      LCTL_T(KC_K),      RALT_T(KC_L),   KC_SCLN,
        KC_Z,    KC_X,              KC_C,            KC_V,            KC_B,               KC_N,         KC_M,              KC_COMM,           KC_DOT,         KC_SLSH,
                                    LH,          KC_SPC,          MO(1),              MO(2),        KC_ENT,           KC_ESC
    ),

    [_PRACTICE] = LAYOUT_split_3x5_3(
        KC_K,    KC_Y,              KC_O,           KC_AE,           KC_X,               KC_Z,         KC_W,      KC_L,      KC_G,   KC_B,
        KC_H,    KC_I,              KC_E,     		KC_A,            KC_OE,              KC_D,         KC_T,      KC_R,      KC_S,   KC_N,
        KC_F,    KC_J,              KC_Q,           KC_AA,           KC_DOT,             KC_V,         KC_M,      KC_COMM,   KC_C,   KC_P,
                                    LH,          KC_SPC,          MO(1),              MO(2),        KC_ENT,      KC_U
    ),

    [_HOELOEKAK] = LAYOUT_split_3x5_3(
     KC_TAB, LY ,     LO  ,    KC_AE,   KC_B ,               KC_C,   KC_F ,  KC_L ,   KC_P ,  KC_Z,
     LH ,    LI   ,   LE  ,    KC_A ,   LG ,                 LD,   KC_T ,  KC_N ,   KC_S ,  LR,
     CTL_Q , KC_AA,   KC_OE,   KC_U ,   KC_K ,               KC_J,   KC_M ,  KC_V,    KC_W ,  KC_X,
                   LWORD, SFT_T(KC_SPC), SPWIN, 		  TABMV, LT(_NUMBERS,KC_ENT), LT(_SYMBOLS, KC_U)
    ),


    [_SELECT] = LAYOUT_split_3x5_3(
      _______, _______, _______, _______, _______,             _______, _______, KC_F8,   KC_P,    _______,
      _______, _______, _______, _______, _______,             KC_D,    KC_F5,   KC_F6,   KC_F7,   _______,
      _______, _______, _______, _______, _______, 					   _______, _______, _______, _______, _______,
                                 _______, _______, _______,    _______, _______, _______
    ),

    [_SELECT_SHIFT] = LAYOUT_split_3x5_3(
      _______, _______, _______, _______, _______,             _______, _______, S(KC_F8),   KC_P, _______,
      _______, _______, _______, _______, _______,             KC_D,    S(KC_F5),   S(KC_F6),   S(KC_F7), _______,
      _______, _______, _______, _______, _______, 					   _______, _______, _______, _______, _______,
                        _______, _______, _______, 					   _______, _______, _______
    ),

    [_WORD] = LAYOUT_split_3x5_3(
      _______, _______, _______, _______, _______,                 _______, _______, KC_F4,   _______, _______,
      MO(_WORD_SHIFT), _______, _______, _______, KC_DEL,          KC_BSPC, KC_F1,   KC_F2,   KC_F3, _______,
      RCS(KC_ESC), _______, _______, _______, _______,             _______, _______, _______, _______, _______,
                           _______, _______, _______,             KC_TAB, _______, _______
    ),
    [_WORD_SHIFT] = LAYOUT_split_3x5_3(
      _______, _______, _______, _______, _______,           _______, _______, S(KC_F4),   _______, _______,
      _______, _______, _______, _______, S(KC_DEL),         S(KC_BSPC),  S(KC_F1),   S(KC_F2),   S(KC_F3), _______,
      _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______,
                                 _______, _______, _______,  _______, _______, _______
    ),

    [_SEARCH] = LAYOUT_split_3x5_3(
      _______, _______, _______, _______, _______,            _______, _______, KC_F12,   _______, _______,
      _______, _______, _______, _______, _______,            _______,  KC_F9,  KC_F10,   KC_F11, _______,
      _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______,
                        _______, _______, _______,					  _______, _______, _______
    ),

    [_SEARCH_SHIFT] = LAYOUT_split_3x5_3(
      _______, _______, _______, _______, _______,            _______, _______, KC_F4,   _______, _______,
      _______, _______, _______, _______, KC_DEL,             KC_BSPC,    KC_F1,   KC_F2,   KC_F3, _______,
      _______, _______, _______, _______, _______,  					_______, _______, _______, _______, _______,
                        _______, _______, _______, 						_______, _______, _______
    ),
    [_CURSOR] = LAYOUT_split_3x5_3(
      _______, _______, _______, _______, _______,                 _______, _______, C(KC_F8),   _______, _______,
      LCA(KC_H), LCA(KC_I), LCA(KC_E), LCA(KC_A), LCA(KC_G),    	LCA(KC_D), C(KC_F1), C(KC_F6),  C(KC_F3), LCA(KC_R),
      _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______,
                                 _______, _______, _______,       _______, _______, _______
    ),
    [_VIEW] = LAYOUT_split_3x5_3(
      _______, _______, _______, _______, _______,            _______, _______, KC_PGUP,  _______, _______,
      _______, _______, _______, _______, KC_DEL,             KC_BSPC, S(KC_TAB), KC_PGDN,   KC_TAB, _______,
      _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______,
                        _______, _______, _______,            _______, _______, _______
    ),
    [_SYMBOLS] = LAYOUT_split_3x5_3(
      _______, S(SE_3), ALGR(SE_2), SE_TILD, SE_PIPE,                _______, _______, SE_DLR, _______, _______,
      SE_LABK, SE_RABK, S(SE_8), SE_LCBR, SE_LBRC,                   LCA(SE_PLUS), S(SE_2), SE_SLSH, SE_QUOT , SE_GRV,
      RCS(KC_ESC), _______, S(SE_9), SE_RCBR, SE_RBRC,               LCA(SE_PLUS), SE_BSLS, SE_BSLS, SE_QUOT, SE_GRV,
                            LGUI(KC_Y), KC_TAB, LCAG(KC_Z),					 _______, KC_TAB, _______
    ),

    [_NUMBERS] = LAYOUT_split_3x5_3(
     _______, SE_CIRC, SE_ASTR, SE_PLUS, S(SE_5),                             _______,   SE_4,   SE_5,   SE_6, _______,
     LT(0,C(SE_1)), LT(0,SE_MINS), LT(0,SE_DOT), LT(0,SE_COMM), S(SE_PLUS),   SE_0,    SE_1,   SE_2,   SE_3, _______,
     RCS(KC_ESC), _______, S(SE_6), S(SE_1), LT(0,SE_EQL),       							_______,   SE_7,   SE_8,   SE_9, _______,
                           LGUI(KC_Y), KC_TAB, LCAG(KC_Z),     								_______, _______, _______
    ),
    [_MOVEMENT] = LAYOUT_split_3x5_3(
      _______, _______, _______, _______, _______,           _______, _______, KC_UP,   _______, KC_KB_VOLUME_UP,
      _______, _______, _______, _______, KC_DEL,            KC_BSPC,    KC_LEFT,   KC_DOWN,   KC_RIGHT, _______,
      _______, _______, TG(_PRACTICE), TG(_HOELOEKAK), TG(_QWERTY),					 _______, _______, _______, _______, KC_KB_VOLUME_DOWN,
                        _______, _______, _______,					 _______, _______, _______
    ),
};

