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
};

bool detected_host_os_is_windows = false;

//delete when backspace+shift is pressed
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
//volume up when vol down+shift is pressed
const key_override_t volume_down_override = ko_make_basic(MOD_MASK_SHIFT, KC_VOLD, KC_VOLU);

// All available key overrides
const key_override_t *key_overrides[] = {
	&delete_key_override,
    &volume_down_override,
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
    KC_TAB,     KC_A,       LT(0, KC_S),    KC_D,       KC_F,           KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
    KC_LSFT,    KC_Y,       KC_X,           KC_C,       KC_V,           KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, MT(MOD_RSFT, KC_ENT),
    CKBL,       KC_LCTL,    KC_LALT,        KC_LGUI,    MO(_LAYER2),    KC_SPC, KC_SPC, TG(_LAYER1), KC_RALT, KC_RCTL, KC_NO, KC_NO
),

[_LAYER1] = LAYOUT(
    _______,   KC_F7,   KC_F8,   KC_F9,       KC_NO,  KC_NO,  KC_NO,       KC_P7, KC_P8,   KC_P9, KC_PSLS, _______,
    _______,   KC_F4,   KC_F5,   KC_F6,       KC_NO,  KC_NO,  KC_NO,       KC_P4, KC_P5,   KC_P6, KC_PAST, KC_PEQL,
    _______,   KC_F1,   KC_F2,   KC_F3,       KC_NO,  KC_NO,  KC_NO,       KC_P1, KC_P2,   KC_P3, KC_PMNS,  _______,
    _______, _______, _______, _______, MO(_LAYER1), _______, _______, TG(_LAYER2), KC_P0, KC_PDOT, KC_PPLS, KC_PCMM
),

/*
 * Movement layer:
 * home, page up, page down, end: move to the beginning / end of the line
 * hjkl: left, down, up, right
 * bnm,: , ___, ___,
 * left hand: asdf: mod-tap for asdf and: kc_lctl, KC_LALT / options, kc_lshift, KC_LGUI
 */
[_LAYER2] = LAYOUT(
    _______, KC_NO, KC_NO, KC_NO,                       KC_NO, KC_NO, KC_HOME,  MT(KC_LSFT, KC_PAGE_DOWN),  KC_NO, KC_END, KC_NO, _______,
    _______, KC_NO, KC_NO, MT(KC_LALT, KC_PAGE_DOWN),   KC_NO, KC_NO, KC_LEFT,  KC_DOWN,                    KC_UP, KC_RIGHT, KC_NO, KC_NO,
    _______, KC_NO, KC_NO, KC_NO,                       KC_NO, KC_NO, KC_NO,    KC_NO,                      KC_NO, KC_NO, KC_NO, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),

};


/**
* Produces an umlaut (äöüÄÖÜ) when pressing one of those keys together with ALT. Otherwise nothing happens
*/
bool produce_umlaut(uint16_t keycode, keyrecord_t *record) {
    if(keycode == KC_A || keycode == KC_U || keycode == KC_O) {
        if (record->event.pressed) {
            if(detected_host_os_is_windows) {
                //TODO: NYI on windows
                return true;
            } else {
                uint8_t mods = get_mods();        // save user's real modifiers

                if (mods & (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT))) {    // user is holding any Alt
                    clear_mods();                 // <--- prevent macOS from seeing it

                    // send macOS "Option + U" dead key
                    register_code(KC_RALT);
                    tap_code(KC_U);
                    unregister_code(KC_RALT);

                    wait_ms(5);

                    bool shift_on = mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
                    if(shift_on) {
                        tap_code16(LSFT(keycode));
                    } else {
                        tap_code(keycode);               // send final letter
                    }
                    set_mods(mods);               // restore user's modifiers
                } else {
                    tap_code(keycode);               // normal u
                }
            }
        }

        return false;
    }

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // case LEFT_WINDOW:
        //     if (record->event.pressed) {
        //         tap_code16(LCTL(KC_LEFT));
        //     }
        //     break;
        // case RIGHT_WINDOW:
        //     if (record->event.pressed) {
        //         tap_code16(LCTL(KC_RIGHT));
        //     }
        //     break;
        case KC_U:
            return produce_umlaut(keycode, record);
        case KC_A:
            return produce_umlaut(keycode, record);
        case KC_O:
            return produce_umlaut(keycode, record);
        case LT(0,KC_S): //sends s on tap and ß on hold
            if (record->tap.count && record->event.pressed) {
                return true;
            } else if (record->event.pressed) {
                tap_code16(RALT(KC_S)); // ALTG + S sends ß
                return false;
            }
            break;
        case LT(0, KC_A):
            if (record->tap.count && record->event.pressed) {
                return true;
            } else if (record->event.pressed) {
                tap_code16(RALT(KC_Q)); // ALTG + Q sends äÄ
                return false;
            }
            break;
        case LT(0, KC_O):
            if (record->tap.count && record->event.pressed) {
                return true;
            } else if (record->event.pressed) {
                tap_code16(RALT(KC_P)); // ALTG + P sends öÖ
                return false;
            }
            break;
        case LT(0, KC_U):
            if (record->tap.count && record->event.pressed) {
                return true;
            } else if (record->event.pressed) {
                tap_code16(RALT(KC_Y)); // ALTG + Y sends üÜ
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
