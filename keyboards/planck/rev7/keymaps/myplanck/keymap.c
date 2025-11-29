#include QMK_KEYBOARD_H

#define OS_DETECTION_SINGLE_REPORT //this setting may help with delayed stability issues when switching devices on some KVMs (see https://docs.qmk.fm/features/os_detection#troubleshooting)

//duration for tap dance
// #define TAPPING_TERM 175


#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2


enum custom_keycodes {
    LAYER0 = SAFE_RANGE,
    LAYER1, //number pad
    LAYER2, //arrow keys --> move around layer
    CKBL, //Change Keyboard Language
    AP_GLOB,
};

bool detected_host_os_is_windows = false;

//delete when backspace+shift is pressed
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
//volume up when vol down+shift is pressed
const key_override_t volume_down_override = ko_make_basic(MOD_MASK_SHIFT, KC_VOLD, KC_VOLU);

const key_override_t ko_1_to_f1 = ko_make_basic(MOD_MASK_SHIFT, KC_1, KC_F1);
const key_override_t ko_0_to_f12 = ko_make_basic(MOD_MASK_SHIFT, KC_0, KC_F12);

// All available key overrides
const key_override_t *key_overrides[] = {
	&delete_key_override,
    &volume_down_override,
    &ko_1_to_f1,
    &ko_0_to_f12
};

 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_LAYER0] = LAYOUT(
    KC_ESC,     KC_Q,       KC_W,           KC_E,       KC_R,           KC_T, KC_Z, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
    KC_TAB,     KC_A,       KC_S,    KC_D,       KC_F,           KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
    KC_LSFT,    KC_Y,       KC_X,           KC_C,       KC_V,           KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, MT(MOD_RSFT, KC_ENT),
    AP_GLOB, KC_LCTL,    KC_LALT,        KC_LGUI,    MO(_LAYER2),    KC_SPC, KC_SPC, TG(_LAYER1), KC_RALT, KC_RCTL, KC_NO, KC_NO
),

[_LAYER1] = LAYOUT(
    _______,   KC_P1,   KC_P2,   KC_P3,       KC_P4,   KC_P5,   KC_P6,        KC_P7,   KC_P8,   KC_P9, KC_0,    _______,
    _______, _______, _______, _______,       KC_NO,   KC_NO,   KC_NO,      _______,   KC_P5,   KC_P6, KC_PAST, KC_PEQL,
    _______, _______, _______, _______,       KC_NO,   KC_NO,   KC_NO,      _______,   KC_P2,   KC_P3, KC_PMNS, _______,
    _______, _______, _______, _______, MO(_LAYER1), _______, _______,  TG(_LAYER2), _______, _______, _______, _______
),

/*
 * Movement layer:
 * home, page up, page down, end: move to the beginning / end of the line
 * hjkl: left, down, up, right
 * bnm,: , ___, ___,
 * left hand: asdf: mod-tap for asdf and: kc_lctl, KC_LALT / options, kc_lshift, KC_LGUI
 */
[_LAYER2] = LAYOUT(
    _______, KC_NO, KC_NO, KC_NO,                       KC_NO, KC_NO, KC_HOME,  MT(KC_LSFT, KC_PAGE_UP),  KC_NO, KC_END, KC_NO, _______,
    _______, KC_NO, KC_NO, MT(KC_LALT, KC_PAGE_DOWN),   KC_NO, KC_NO, KC_LEFT,  KC_DOWN,                    KC_UP, KC_RIGHT, KC_NO, KC_NO,
    _______, KC_NO, KC_NO, KC_NO,                       KC_NO, KC_NO, KC_NO,    KC_NO,                      KC_NO, KC_NO, KC_NO, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),

};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case AP_GLOB:
            host_consumer_send(record->event.pressed ? AC_NEXT_KEYBOARD_LAYOUT_SELECT : 0);
            return false;

        case LT(0,KC_S): //sends s on tap and ß on hold
            if (record->tap.count && record->event.pressed) {
                return true;
            } else if (record->event.pressed) {
                tap_code16(RALT(KC_S)); // ALTG + S sends ß
                return false;
            }
            break;
        case CKBL:
            if (record->event.pressed) {
                if (detected_host_os_is_windows) {
                    tap_code16(LGUI(KC_SPC));
                } else {
                    tap_code16(LCTL(KC_SPC));
                }
            }
            break;
    }
    return true;
};

//detect host os and switch
bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (!process_detected_host_os_user(detected_os)) {
        return false;
    }
    switch (detected_os) {
        case OS_WINDOWS:
            detected_host_os_is_windows = true;
            break;
        default:
            detected_host_os_is_windows = false;
            break;
    }

    return true;
}
