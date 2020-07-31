#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* ,-----------------------------------------------------------------------------------------.
   * | Esc | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   | 0   | -   | =   | Backspace |
   * |-----------------------------------------------------------------------------------------+
   * | Tab    | Q   | W   | E   | R   | T   | Y   | U   | I   | O   | P   | [   | ]   |   \    |
   * |-----------------------------------------------------------------------------------------+
   * | Caps     | A   | S   | D   | F   | G   | H   | J   | K   | L   | ;   | '   | Enter      |
   * |-----------------------------------------------------------------------------------------+
   * | Shift     | Z   | X   | C   | V   | B   | N   | M   | ,   | .   | /   | ` ~ | Up |  Fn  |
   * |-----------------------------------------------------------------------------------------+
   * | Ctrl | Alt  | Cmd  |               Space                |  Cmd  | Alt | Left| Down|Right|
   * `-----------------------------------------------------------------------------------------'
   */
  LAYOUT_all(
    KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_NO, KC_BSPC,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
    KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
    KC_LSFT, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_GRV, KC_UP, MO(1),
    KC_LCTL, KC_LALT, KC_LGUI, KC_NO, KC_SPC, KC_NO, KC_RGUI, KC_RALT, KC_LEFT, KC_DOWN, KC_RIGHT),

  /* ,-----------------------------------------------------------------------------------------.
   * |     |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |           |
   * |-----------------------------------------------------------------------------------------+
   * |        |     |     |  Up |     |     |     |     |  0  |  1  |  2  |  3  |     |        |
   * |-----------------------------------------------------------------------------------------+
   * |         |     | Left| Down|Right|     |     |     |     |  4  |  5  |  6  |             |
   * |-----------------------------------------------------------------------------------------+
   * |           |     |     |     |     |     |     |     |     |  7  |  8  |  9  |     |     |
   * |-----------------------------------------------------------------------------------------+
   * |      |      |      |                                      |     |     |     |     |     |
   * `-----------------------------------------------------------------------------------------'
   */
  LAYOUT_all(
    KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_F11, KC_F12, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_0, KC_1, KC_2, KC_3, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_4, KC_5, KC_6, KC_TRNS,
    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_7, KC_8, KC_9, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

static bool lgui_pressed = false; // (1)
static bool rgui_pressed = false; // (1)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_LGUI:
      if (record->event.pressed) {
        lgui_pressed = true; // (2)
      } else {
        if (lgui_pressed) { // (4)
          unregister_code(KC_LGUI);
          tap_code(KC_LANG2);
          lgui_pressed = false;
          return false;
        }
        lgui_pressed = false;
      }
      break;
    case KC_RGUI:
      if (record->event.pressed) {
        rgui_pressed = true; // (2)
      } else {
        if (rgui_pressed) { // (4)
          unregister_code(KC_RGUI);
          tap_code(KC_LANG1);;
          rgui_pressed = false;
          return false;
        }
        rgui_pressed = false;
      }
      break;
    default: // (3)
      if (record->event.pressed) {
        // reset the flag
        lgui_pressed = false;
        rgui_pressed = false;
      }
      break;
  }
  return true;
}
