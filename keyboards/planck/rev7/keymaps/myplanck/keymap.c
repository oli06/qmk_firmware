#include QMK_KEYBOARD_H

#define OS_DETECTION_SINGLE_REPORT //this setting may help with delayed stability issues when switching devices on some KVMs (see https://docs.qmk.fm/features/os_detection#troubleshooting)

//duration for tap dance
// #define TAPPING_TERM 175


#define _L0 0
#define _L2 2
#define _LFN 3
#define VIM 4
#define _LADJUST 5


enum custom_keycodes {
    CKBL = SAFE_RANGE, //Change Keyboard Language
    // AP_GLOB,
    BLUB,
    STAR_AND_BACKSLASH,
    MINUS_PLUS,
    // KC_GLOBE,
};
bool detected_host_os_is_windows = false;
bool umlaut_key_held = false;

//delete when backspace+shift is pressed
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
//volume up when vol down+shift is pressed
const key_override_t volume_down_override = ko_make_basic(MOD_MASK_SHIFT, KC_VOLD, KC_VOLU);

// const key_override_t AT_when_q_alt = ko_make_basic(MOD_MASK_ALT, KC_Q, S(KC_2));

// const key_override_t EUR_when_e_alt = ko_make_basic(MOD_MASK_ALT, KC_E, S(KC_2));
const key_override_t backtick_when_single_tick_and_shift = ko_make_basic(MOD_MASK_SHIFT, KC_QUOT, KC_GRAVE);

// All available key overrides
const key_override_t *key_overrides[] = {
	&delete_key_override,
    &volume_down_override,
    // &backtick_when_single_tick_and_shift,
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
[_L0] = LAYOUT(
    KC_ESC,     KC_Q,       KC_W,           KC_E,       KC_R,           KC_T, KC_Z, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
    KC_TAB,     KC_A,       KC_S,    KC_D,       KC_F,           KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
    KC_LSFT,    KC_Y,       KC_X,           KC_C,       KC_V,           KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, MT(MOD_RSFT, KC_ENT),
    MO(_LFN), QK_LLCK,    KC_LCTL,        KC_LGUI,    MO(_L2),    KC_SPC, KC_SPC, MO(VIM),  KC_RALT, QK_LLCK, CKBL, BLUB
),

[VIM] = LAYOUT(
    _______,   KC_4,   KC_2,   KC_3,       KC_1,   KC_5,   KC_6,        KC_0,   KC_8,   KC_9, KC_7,    _______,
    _______, S(KC_3), S(KC_6), S(KC_5),  S(KC_4), STAR_AND_BACKSLASH, MINUS_PLUS,  S(KC_9), S(KC_0), KC_LBRC, KC_RBRC, KC_GRAVE,
    _______, S(KC_GRAVE), S(KC_BACKSLASH), S(KC_1),  KC_EQUAL, S(KC_7), S(KC_MINS), S(KC_2), _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______
),

/*
 * Movement layer:
 * home, page up, page down, end: move to the beginning / end of the line
 * hjkl: left, down, up, right
 * bnm,: , ___, ___,
 * left hand: asdf: mod-tap for asdf and: kc_lctl, KC_LALT / options, kc_lshift, KC_LGUI
 */
[_L2] = LAYOUT(
    _______, KC_NO, KC_NO, KC_NO,                       KC_NO, KC_NO, KC_HOME,  MT(KC_LSFT, KC_PAGE_UP),  KC_NO, KC_END, KC_NO, _______,
    _______, KC_NO, KC_NO, MT(KC_LALT, KC_PAGE_DOWN),   KC_NO, KC_NO, KC_LEFT,  KC_DOWN,                    KC_UP, KC_RIGHT, KC_NO, KC_NO,
    _______, KC_NO, KC_NO, KC_NO,                       KC_NO, KC_NO, KC_NO,    KC_NO,                      KC_NO, KC_NO, KC_NO, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),


[_LFN] = LAYOUT(
    KC_F1,   KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
    KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_LADJUST] = LAYOUT(
    KC_NO, KC_L, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MINUS_PLUS:
            if (record->event.pressed) {
                if(get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
                    //shift + kc_equal is +
                    tap_code(KC_EQUAL);

                    return false;
                } else {
                    tap_code(KC_MINUS);
                    return false;
                }
            }
            break;
        case STAR_AND_BACKSLASH:
            if (record->event.pressed) {
                if(get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
                    uint8_t mods = get_mods();

                    del_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
                    tap_code(KC_BACKSLASH);
                    set_mods(mods);

                    return false;
                } else {
                    tap_code16(S(KC_8));
                    return false;
                }
            }
            break;
        case KC_E:
            if (record->event.pressed) {
                if(get_mods() & (MOD_BIT(KC_RALT) | MOD_BIT(KC_LALT))) {
                    tap_code16(S(KC_2));
                    return false;
                }
            }
            break;

        case KC_Q:
            if (record->event.pressed) {
                if(get_mods() & (MOD_BIT(KC_RALT) | MOD_BIT(KC_LALT))) {
                    uint8_t mods = get_mods();

                    // Remove Alt (or RAlt / AltGr)
                    del_mods(MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT));

                    tap_code16(S(KC_2));
                    set_mods(mods);
                    return false;
                }
            }
            break;

        case BLUB:
            umlaut_key_held = record->event.pressed;
            return false; // Don't send anything for this key

        case KC_U:
            if (record->event.pressed) {
                if (umlaut_key_held) {
                    tap_code16(A(KC_U));   // ⌥+U: macOS umlaut dead key
                    tap_code(KC_U);        // then type U
                    return false;
                }
            }
            break;
        case KC_A:
            if (record->event.pressed) {
                if (umlaut_key_held) {
                    tap_code16(A(KC_U));   // ⌥+U: macOS umlaut dead key
                    tap_code(KC_A);        // then type U
                    return false;
                }
            }
            break;
        case KC_O:
            if (record->event.pressed) {
                if (umlaut_key_held) {
                    tap_code16(A(KC_U));   // ⌥+U: macOS umlaut dead key
                    tap_code(KC_O);        // then type U
                    return false;
                }
            }
            break;
        // case LT(0,KC_S): //sends s on tap and ß on hold
        //     if (record->tap.count && record->event.pressed) {
        //         return true;
        //     } else if (record->event.pressed) {
        //         tap_code16(RALT(KC_S)); // ALTG + S sends ß
        //         return false;
        //     }
        //     break;
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

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _L2, VIM, _LADJUST);
}


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
