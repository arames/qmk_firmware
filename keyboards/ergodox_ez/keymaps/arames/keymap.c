#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "config.h"

#define BASE 0 // Default layer
#define SYMB 1 // Symbols
#define NUM  2 // Numeric keypad and function keys


// Left hand.
// KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
// KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
// KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
// KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
// KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
//
//           KC_TRNS , KC_TRNS ,
//           KC_TRNS ,
// KC_TRNS , KC_TRNS , KC_TRNS ,
//
// Right hand.
// KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
// KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
//           KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
// KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
//                     KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
//
// KC_TRNS , KC_TRNS ,
// KC_TRNS ,
// KC_TRNS , KC_TRNS , KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |   ]    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   \    |   Q  |   W  |   E  |   R  |   T  |      |           | Del  |   Y  |   U  |   I  |   O  |   P  |   [    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   '    |A/Ctrl|   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |;/Ctrl|   -    |
 * |--------+------+------+------+------+------| Tab  |           |Bspace|------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Home | End  | Opt  | Alt  |      |                                       | Left | Down |  Up  |Right |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                         ,------------.       ,-------------.
 *                                         |CAPS |      |       | PgDn | PgUp |
 *                                   ,-----|-----|------|       |------+------+------.
 *                                   |     |     |      |       |      |      |      |
 *                                   | Cmd |OSL 1|------|       |------|Enter |Space |
 *                                   |     |     | TT 2 |       | Esc  |      |      |
 *                                   `------------------'       `--------------------'
 */
[BASE] = LAYOUT_ergodox(
      KC_GRAVE  , KC_1        , KC_2    , KC_3    , KC_4    , KC_5 , KC_TRNS ,
      KC_BSLASH , KC_Q        , KC_W    , KC_E    , KC_R    , KC_T , KC_TRNS ,
      KC_QUOTE  , CTL_T(KC_A) , KC_S    , KC_D    , KC_F    , KC_G ,
      KC_LSFT   , KC_Z        , KC_X    , KC_C    , KC_V    , KC_B , KC_TAB  ,
      KC_HOME   , KC_END      , KC_LALT , KC_LALT , KC_TRNS ,

                KC_CAPS , KC_TRNS ,
                          KC_TRNS ,
      KC_LGUI , OSL(1)  , TT(2)   ,

      KC_TRNS   , KC_6    , KC_7  , KC_8     , KC_9    , KC_0              , KC_RBRC  ,
      KC_DELETE , KC_Y    , KC_U  , KC_I     , KC_O    , KC_P              , KC_LBRC  ,
                  KC_H    , KC_J  , KC_K     , KC_L    , RCTL_T(KC_SCOLON) , KC_MINUS ,
      KC_BSPACE , KC_N    , KC_M  , KC_COMMA , KC_DOT  , KC_SLASH          , KC_RSFT  ,
      KC_LEFT   , KC_DOWN , KC_UP , KC_RIGHT , KC_TRNS ,

      KC_PGDOWN, KC_PGUP,
      KC_TRNS  ,
      KC_ESC   , KC_ENTER, KC_SPACE
    ),
/* Keymap 1: Symbols
 *
 * ,-------------------------------------------.           ,-------------------------------------------.
 * |       |     |     |     |     |     |                 |     |     |  ^  |  &  |  |  |  ~  |       |
 * |-------+-----+-----+-----+-----+-----------|           |-----+-----+-----+-----+-----+-----+-------|
 * |       |     |     |     |     |     |     |           |     |     |     |  {  |  }  |     |       |
 * |-------+-----+-----+-----+-----+-----|     |           |     |-----+-----+-----+-----+-----+-------|
 * |       |     |     |     |     |     |-----|           |-----|     |  *  |  (  |  )  |  \  |       |
 * |-------+-----+-----+-----+-----+-----|     |           |     |-----+-----+-----+-----+-----+-------|
 * |       |     |     |     |     |     |     |           |     |     |  =  |  [  |  ]  |     |       |
 * `-------+-----+-----+-----+-----+-----------'           `-----------+-----+-----+-----+-----+-------'
 *   |     |     |     |     |     |                                   |     |     |     |     |     |
 *   `-----------------------------'                                   `-----------------------------'
 *                                   ,-----------.       ,-----------.
 *                                   |     |     |       |     |     |
 *                            ,------|-----|-----|       |-----+-----+------.
 *                            |      |     |     |       |     |     |      |
 *                            |      |     |-----|       |-----|     |      |
 *                            |      |     |     |       |     |     |      |
 *                            `------------------'       `------------------'
 */
[SYMB] = LAYOUT_ergodox(
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
              KC_TRNS , KC_TRNS ,
              KC_TRNS ,
    KC_TRNS , KC_TRNS , TO(0),

    KC_TRNS , KC_CIRC , KC_AMPR        , KC_PIPE , KC_TILD , KC_TRNS   , KC_TRNS ,
    KC_TRNS , KC_TRNS , KC_TRNS        , KC_LCBR , KC_RCBR , KC_TRNS   , KC_TRNS ,
              KC_TRNS , KC_KP_ASTERISK , KC_LPRN , KC_RPRN , KC_BSLASH , KC_TRNS ,
    KC_TRNS , KC_TRNS , KC_EQUAL       , KC_LBRC , KC_RBRC , KC_TRNS   , KC_TRNS ,
                        KC_TRNS        , KC_TRNS , KC_TRNS , KC_EQUAL  , KC_TRNS ,
    KC_TRNS , KC_TRNS ,
    KC_TRNS ,
    KC_TRNS , KC_TRNS , KC_TRNS
),
/* Keymap 2: Numeric keypad and function keys
 *
 * ,-------------------------------------------.           ,-------------------------------------------.
 * |  Esc  | F1  | F2  | F3  | F4  | F5  |     |           |     | F6  | F7  | F8  | F9  | F10 |  F11  |
 * |-------+-----+-----+-----+-----+-----------|           |-----+-----+-----+-----+-----+-----+-------|
 * |       |     |     |     |     |     |     |           |     |     |  7  |  8  |  9  |     |  F12  |
 * |-------+-----+-----+-----+-----+-----|     |           |     |-----+-----+-----+-----+-----+-------|
 * |       |     |     |           |     |-----|           |-----|  +  |  4  |  5  |  6  |  *  |       |
 * |-------+-----+-----+-----+-----+-----|     |           |     |-----+-----+-----+-----+-----+-------|
 * |       |     |     |     |     |     |     |           |     |  -  |  1  |  2  |  3  |  /  |       |
 * `-------+-----+-----+-----+-----+-----------'           `-----------+-----+-----+-----+-----+-------'
 *   |     |     |     |     |     |                                   | Tab |  0  |  .  |  =  |     |
 *   `-----------------------------'                                   `-----------------------------'
 *                                   ,-----------.       ,-----------.
 *                                   |     |     |       |     |     |
 *                            ,------|-----|-----|       |-----+-----+------.
 *                            |      |     |     |       |     |     |      |
 *                            |      |     |-----|       |-----|     |      |
 *                            |      |     |TO 0 |       |     |     |      |
 *                            `------------------'       `------------------'
 */
[NUM] = LAYOUT_ergodox(
    KC_ESC  , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_TRNS ,
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
              KC_TRNS , KC_TRNS ,
              KC_TRNS ,
    KC_TRNS , KC_TRNS , TO(0),

    KC_TRNS , KC_F6   , KC_F7  , KC_F8  , KC_F9     , KC_F10   , KC_F11  ,
    KC_TRNS , KC_TRNS , KC_7   , KC_8   , KC_9      , KC_TRNS  , KC_F12  ,
              KC_PLUS , KC_4   , KC_5   , KC_6      , KC_ASTR  , KC_TRNS ,
    KC_TRNS , KC_MINS , KC_1   , KC_2   , KC_3      , KC_SLSH  , KC_TRNS ,
                        KC_TAB , KC_0   , KC_KP_DOT , KC_EQUAL , KC_TRNS ,
    KC_TRNS , KC_TRNS ,
    KC_TRNS ,
    KC_TRNS , KC_TRNS , KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        register_code(KC_RSFT);
      } else {
        unregister_code(KC_RSFT);
      }
      break;
  }
  return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

  uint8_t layer = biton32(layer_state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    case SYMB:
      ergodox_right_led_1_on();
      break;
    case NUM:
      ergodox_right_led_2_on();
      break;
    default:
      // none
      break;
  }

};
