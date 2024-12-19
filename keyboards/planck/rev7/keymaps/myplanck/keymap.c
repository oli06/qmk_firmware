#include QMK_KEYBOARD_H


#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2
#define MAX_LAYERS 3
// #define _LAYER3 3
// #define _LAYER4 4
// #define _LAYER5 5
// #define _LAYER6 6

enum custom_keycodes {
    LAYER0 = SAFE_RANGE,
    LAYER1,
    LAYER2,
    // LAYER3,
    // LAYER4,
    // LAYER5,
    // LAYER6,
    LAYER_INCREMENT,
    LAYER_DECREMENT,
};

uint8_t LAYER_LEVEL = 0;

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
    KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Z, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
    KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Y, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, SC_SENT,
    KC_NO, KC_LCTL, KC_LALT, KC_LGUI, KC_NO, KC_SPC, KC_SPC, TG(_LAYER1), KC_RGUI, KC_NO, KC_NO, KC_NO
),

[_LAYER1] = LAYOUT(KC_TAB, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_P7, KC_P8, KC_P9, KC_PSLS, KC_BSPC,
 KC_ESC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_P4, KC_P5, KC_P6, KC_PAST, KC_PEQL,
 KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_P1, KC_P2, KC_P3, KC_PMNS, KC_ENT,
 KC_NO, KC_LCTL, KC_LALT, KC_LGUI, TG(_LAYER1), KC_SPC, KC_SPC, TG(_LAYER2), KC_P0, KC_PDOT, KC_PPLS, KC_PCMM),

[_LAYER2] = LAYOUT(
    KC_TAB, KC_C, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_BSPC,
    KC_ESC, KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_SLSH,
    KC_LSFT, KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_ENT,
    KC_NO, KC_LCTL, KC_LALT, KC_LGUI, TG(_LAYER2), KC_SPC, KC_SPC, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LAYER_INCREMENT:
            if (record->event.pressed) {
                if (LAYER_LEVEL < MAX_LAYERS) {
                    ++LAYER_LEVEL;
                }
                layer_move(LAYER_LEVEL);
            }
            break;
        case LAYER_DECREMENT:
            if (record->event.pressed) {
                if (LAYER_LEVEL > 0) {
                    --LAYER_LEVEL;
                }
                layer_move(LAYER_LEVEL);
            }
            break;
    }
    return true;
};
