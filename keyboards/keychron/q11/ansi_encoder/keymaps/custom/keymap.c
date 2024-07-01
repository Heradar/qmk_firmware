#include "keycodes.h"
#include QMK_KEYBOARD_H

enum custom_keycodes_user {
    SEND_EMAIL = SAFE_RANGE,
    MAC_LOCK,
    WIN_LOCK,
    WIN_BRIU,
    WIN_BRID,
};

enum layers{
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
    GAMING_BASE,
    GAMING_FN,
};

/*const key_override_t shift_space_override = ko_make_basic(MOD_MASK_SHIFT, KC_SPC, KC_BSPC);*/
const key_override_t shift_space_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_SPC, KC_BSPC, (1 << MAC_BASE | 1 << MAC_FN | 1 << WIN_BASE | 1 << WIN_FN));

const key_override_t **key_overrides = (const key_override_t *[]){
	&shift_space_override,
	NULL
};

bool dip_switch_update_user(uint8_t index, bool active) {
    if (index == 0) {
        default_layer_set(1UL << (active ? MAC_BASE : WIN_BASE));
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SEND_EMAIL:
            if (record->event.pressed) {
                SEND_STRING("example@example.com");
                #error "enter email before compiling";
            }
            break;
        case MAC_LOCK:
            if (record->event.pressed) {
                tap_code16(LCTL(LCMD(KC_Q)));
            }
            break;
        case WIN_LOCK:
            if (record->event.pressed) {
                tap_code16(LCMD(KC_L));
            }
            break;
        case WIN_BRIU:
            if (record->event.pressed) {
                register_code16(HYPR(KC_PGUP));
            } else {
                unregister_code16(HYPR(KC_PGUP));
            }
            break;
        case WIN_BRID:
            if (record->event.pressed) {
                register_code16(HYPR(KC_PGDN));
            } else {
                unregister_code16(HYPR(KC_PGDN));
            }
            break;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_91_ansi(
        MAC_LOCK,  KC_ESC,      KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_INS,   KC_DEL,   KC_MPLY,
        RGB_TOG,   KC_GRV,      KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        RGB_MOD,   KC_TAB,      KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        RGB_HUI,   KC_ESC,      KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
        RGB_SAI,   KC_LSFT,               KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
        RGB_SPI,   MO(MAC_FN),  KC_LCTL,  KC_LOPT,  KC_LCMD,            KC_SPC,                       KC_ENT,             KC_RCMD,  KC_LOPT,  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_91_ansi(
        _______,   _______,  KC_F1,    KC_F2,    KC_F3,       KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,     KC_F10,   KC_F11,   KC_F12,   _______,  _______,  _______,
        _______,   _______,  _______,  _______,  _______,     _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,            _______,
        RGB_RMOD,  _______,  _______,  _______,  SEND_EMAIL,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,            _______,
        RGB_HUD,   KC_CAPS,  _______,  _______,  _______,     _______,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT,  _______,  _______,            _______,            _______,
        RGB_SAD,   _______,            _______,  _______,     _______,  _______,  _______,  NK_TOGG,  _______,  _______,   _______,  _______,            _______,  KC_PGUP,
        RGB_SPD,   _______,  _______,  _______,  _______,               _______,                      _______,             _______,  _______,  _______,  KC_HOME,  KC_PGDN,  KC_END),


    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


    [WIN_BASE] = LAYOUT_91_ansi(
        WIN_LOCK,  KC_ESC,      WIN_BRID,  WIN_BRIU,  LGUI(KC_TAB),  LGUI(KC_E),  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_INS,   KC_DEL,   KC_MPLY,
        RGB_TOG,   KC_GRV,      KC_1,      KC_2,      KC_3,          KC_4,        KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        RGB_MOD,   KC_TAB,      KC_Q,      KC_W,      KC_E,          KC_R,        KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        RGB_HUI,   _______,     KC_A,      KC_S,      KC_D,          KC_F,        KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
        RGB_SAI,   KC_LSFT,                KC_Z,      KC_X,          KC_C,        KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
        RGB_SPI,   MO(WIN_FN),  KC_LCTL,   KC_LALT,   KC_LWIN,                    KC_SPC,                       KC_ENT,             KC_RWIN,  KC_RALT,  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_91_ansi(
        _______,   _______,  KC_F1,     KC_F2,    KC_F3,       KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,     KC_F10,   KC_F11,   KC_F12,   _______,  _______,  _______,
        _______,   _______,  _______,  _______,  _______,     _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,            _______,
        RGB_RMOD,  _______,  _______,  _______,  SEND_EMAIL,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,            _______,
        RGB_HUD,   _______,  _______,  _______,  _______,     _______,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT,  _______,  _______,            _______,            _______,
        RGB_SAD,   _______,            _______,  _______,     _______,  _______,  _______,  NK_TOGG,  _______,  _______,   _______,  _______,            _______,  _______,
        RGB_SPD,   _______,  _______,  _______,  _______,      _______,                      _______,             _______,  _______,  _______,  _______,  _______,  _______),


    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


    [GAMING_BASE] = LAYOUT_91_ansi(
        WIN_LOCK,  KC_ESC,      KC_F1,    KC_F2,    KC_F3,    KC_F4,  KC_F5,   KC_F6,  KC_F7,  KC_F8,   KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_INS,   KC_DEL,   KC_MPLY,
        RGB_TOG,   KC_GRV,      KC_1,     KC_2,     KC_3,     KC_4,   KC_5,    KC_6,   KC_7,   KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        RGB_MOD,   KC_TAB,      KC_Q,     KC_W,     KC_E,     KC_R,   KC_T,    KC_Y,   KC_U,   KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        RGB_HUI,   _______,     KC_A,     KC_S,     KC_D,     KC_F,   KC_G,    KC_H,   KC_J,   KC_K,    KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
        RGB_SAI,   KC_LSFT,               KC_Z,     KC_X,     KC_C,   KC_V,    KC_B,   KC_N,   KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,   KC_UP,
        RGB_SPI,   MO(GAMING_FN),  KC_LCTL,  KC_LALT,  KC_LWIN,          KC_SPC,                  KC_ENT,            KC_RWIN,  KC_RALT,  KC_RCTL,  KC_LEFT,   KC_DOWN,  KC_RGHT),


    [GAMING_FN] = LAYOUT_91_ansi(
        _______,   _______,  WIN_BRID,  WIN_BRIU,  LGUI(KC_TAB),  LGUI(KC_E),  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,   KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  _______,
        _______,   _______,  _______,   _______,   _______,       _______,     _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,            _______,
        RGB_RMOD,  _______,  _______,   _______,   SEND_EMAIL,    _______,     _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,            _______,
        RGB_HUD,   _______,  _______,   _______,   _______,       _______,     _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT,  _______,  _______,            _______,            _______,
        RGB_SAD,   _______,             _______,   _______,       _______,     _______,  _______,  NK_TOGG,  _______,  _______,   _______,  _______,            _______,  _______,
        RGB_SPD,   _______,  _______,   _______,   _______,                    _______,                      _______,             _______,  _______,  _______,  _______,  _______,  _______),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [MAC_BASE]    = { ENCODER_CCW_CW(KC_BRMD,  KC_BRMU),   ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MAC_FN]      = { ENCODER_CCW_CW(_______,  _______),   ENCODER_CCW_CW(_______, _______) },
    [WIN_BASE]    = { ENCODER_CCW_CW(WIN_BRID, WIN_BRIU),  ENCODER_CCW_CW(_______, _______) },
    [WIN_FN]      = { ENCODER_CCW_CW(_______,  _______),   ENCODER_CCW_CW(_______, _______) },
    [GAMING_BASE] = { ENCODER_CCW_CW(WIN_BRID, WIN_BRIU),  ENCODER_CCW_CW(_______, _______) },
    [GAMING_FN]   = { ENCODER_CCW_CW(_______,  _______),   ENCODER_CCW_CW(_______, _______) },
};
#endif // ENCODER_MAP_ENABLE

