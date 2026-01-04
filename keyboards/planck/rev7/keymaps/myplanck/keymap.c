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

// All available key overrides
const key_override_t *key_overrides[] = {
	&delete_key_override,
    &volume_down_override,
    // &AT_when_q_alt,
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
    // _______,   KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_LBRC,   KC_RBRC,  _______,
    _______,   KC_4,   KC_2,   KC_3,       KC_1,   KC_5,   KC_6,        KC_0,   KC_8,   KC_9, KC_7,    _______,
    _______, S(KC_3), S(KC_6), _______,  S(KC_4),   S(KC_8), KC_NO,  _______, _______, S(KC_9), S(KC_0), _______,
    _______, _______, _______, _______,  KC_NO,   KC_NO,   KC_NO,   _______, _______, S(KC_LBRC), S(KC_RBRC), _______,
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

/**

Vim editor shortcuts
^ and $ are on the home row, for jumping to the start/end of current line.
# and * are on the home row, to search behind/ahead for word under cursor.
= is on the home row, to automatically indent current line or selection.
, and ; are above the home block, for navigating between f/F/t/T jumps.
( and ) are above the home block, for jumping to previous/next sentence.
{ and } are on the home block, for jumping to previous/next paragraph.
< and > are on the home block, for decreasing/increasing indentation.
[ and ] are below the home block, for addressing previous/next things.
? and / are stacked vertically, to search behind/ahead for regex pattern.
% is on the thumb’s home key, for jumping to cursor’s matching delimiter.
: is on the middle thumb key, for entering Vim’s command mode comfortably.
:% is an inward swipe by the thumb, for a command across the whole buffer.
@: is an inward swipe by the thumb, to repeat the most recent command line.

Inward rolling bigrams
() for parentheses.
<> for angle brackets.
[] for square brackets.
{} for curly braces.
(); for zero-arity function calls in C and related languages.
); for function call statements in C and related languages.
(" for starting a string value argument for a function call.
[" for starting a string value for a list or hashtable lookup.
=" for HTML attributes and Bourne shell variable assignments.
.* for regular expressions.
~/ for home directory paths in UNIX.
<- for assignment in R and in Elixir’s with statements.
-> for thin arrows in C, C++, and Elixir.
=> for fat arrows in Perl, Ruby, and Elixir.
!= for “not equal to” value comparison in many languages.
<= for “less than or equal to” comparison in many languages.
^= for bitwise XOR assignment in C and related languages.
|> for the pipe operator in Elixir.
!( for negating a group in Boolean expressions.
"$ for quoted variable substitution in Bourne shell.
!$ for last argument of previous command in Bourne shell.
$? for exit status of previous command in Bourne shell.
<% for directive tags in Ruby’s ERB and Elixir’s EEx templates.
<? for directive tags in PHP templates.
#{ for string interpolation in Ruby and Elixir.
`' for legacy curly quotes.
</ for element closing tags in XML and HTML.
~> for pessimistic version constraint in SemVer.
\. for literal period in regular expressions.
~/ for home directory paths in UNIX.
!? for interrobang in English prose.
Outward rolling bigrams
=~ for regular expression matching in Perl, Ruby, and Elixir.
-= for negative accumulation in C and related languages.
+= for accumulation in C and many languages.
%= for modulo assignment in C and related languages.
>= for “greater than or equal to” value comparison.
>& and &< for file descriptor redirection in Bourne shell.
$_ for value of last argument of previous command in Bourne shell.
$< for the first source of a rule in Makefile.
$^ for all sources of a rule in Makefile.
$@ for the target of a rule in Makefile.
%> for directive tags in Ruby’s ERB and Elixir’s EEx templates.
?> for directive tags in PHP templates.
${ for variable interpolation in Bourne shell.
%{ for maps (hash tables) in Elixir.
?! for interrobang in English prose.
 */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
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
