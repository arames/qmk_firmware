#include QMK_KEYBOARD_H
#include "version.h"

enum KeyboardLayers {
  STANDARD,
  BASE,
  SYMBOLS,
  NUMERIC,
  MOVEMENT,
  FUNCTION,

  // Aliases
  STD = STANDARD,
  SYM = SYMBOLS,
  NUM = NUMERIC,
  MOV = MOVEMENT,
  FN = FUNCTION
};

// The main design elements are:
// * Modifiers on the home row keys.
// * Left-hand layer access, with the right hand accessing keys.

  /*
   * Well aligned comment and layout instances, ready for copy-pasting.
     ,-----------------------------------------.     ,------------------------------------------.
     |     |     |     |     |     |     |     |     |      |     |     |     |     |     |     |
     |-----+-----+-----+-----+-----+-----------|     |------+-----+-----+-----+-----+-----+-----|
     |     |     |     |     |     |     |     |     |      |     |     |     |     |     |     |
     |-----+-----+-----+-----+-----+-----|-----|     |------|-----+-----+-----+-----+-----+-----|
     |     |     |     |     |     |     |     |     |      |     |     |     |     |     |     |
     |-----+-----+-----+-----+-----+-----|-----'     `------|-----+-----+-----+-----+-----+-----|
     |     |     |     |     |     |     |                  |     |     |     |     |     |     |
     `------------------------------------                  ------------------------------------|
     |     |     |     |     |     |                              |     |     |     |     |     |
     `-----------------------------'                              `-----------------------------'
                                   ,-----------.     ,------------.
                                   |           |     |            |
                             ,-----+-----------|     |------------+-----.
                             |     |     |     |     |      |     |     |
                             |     |     |     |     |      |     |     |
                             |     |     |     |     |      |     |     |
                             `-----------------'     `------------------'

    [NONE] = LAYOUT_moonlander(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,        KC_NO,     KC_NO,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                    KC_NO, KC_NO, KC_NO,     KC_NO, KC_NO, KC_NO
    ),

    [TRANSPARENT] = LAYOUT_moonlander(
        _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______,     _______,          _______, _______, _______, _______, _______,
                                            _______, _______, _______,     _______, _______, _______
    ),
   */


enum custom_keycodes {
    VRSN = SAFE_RANGE,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
   * Well aligned comment and layout instances, ready for copy-pasting.
     ,-----------------------------------------.     ,------------------------------------------.
     |     |     |     |     |     |     |     |     |      |     |     |     |     |     |     |
     |-----+-----+-----+-----+-----+-----------|     |------+-----+-----+-----+-----+-----+-----|
     |     |     |     |     |     |     |     |     |      |     |     |     |     |     |     |
     |-----+-----+-----+-----+-----+-----|-----|     |------|-----+-----+-----+-----+-----+-----|
     |     |     |     |     |     |     |     |     |      |     |     |     |     |     |     |
     |-----+-----+-----+-----+-----+-----|-----'     `------|-----+-----+-----+-----+-----+-----|
     |     |     |     |     |     |     |                  |     |     |     |     |     |     |
     `------------------------------------                  ------------------------------------|
     |     |     |     |     |     |                              |     |     |     |     |     |
     `-----------------------------'                              `-----------------------------'
                                   ,-----------.     ,------------.
                                   |           |     |            |
                             ,-----+-----------|     |------------+-----.
                             |     |     |     |     |      |     |     |
                             |     |     |     |     |      |     |     |
                             |     |     |     |     |      |     |     |
                             `-----------------'     `------------------'

    [NONE] = LAYOUT_moonlander(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,        KC_NO,     KC_NO,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                    KC_NO, KC_NO, KC_NO,     KC_NO, KC_NO, KC_NO
    ),

    [TRANSPARENT] = LAYOUT_moonlander(
        _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______,     _______,          _______, _______, _______, _______, _______,
                                            _______, _______, _______,     _______, _______, _______
    ),
   */


  /* Standard layer
   *
   * Standard keycodes.
   * This layer is intended to define the location of standard keycodes. It does
   * not have any special keycodes, except for a toggle to the normal layer. It
   * is intended as a rarely used layer, when custom functions (e.g. home row
   * modifiers) should not get in the way.
   *
   * TODO: Add standard locations for ctrl and shift ?
   *
   * ,-----------------------------------------.     ,------------------------------------------.
   * | Esc |  1  |  2  |  3  |  4  |  5  |     |     |      |  6  |  7  |  8  |  9  |  0  |  =  |
   * |-----+-----+-----+-----+-----+-----------|     |------+-----+-----+-----+-----+-----+-----|
   * |     |  Q  |  W  |  E  |  R  |  T  | Tab |     | Tab  |  Y  |  U  |  I  |  O  |  P  |     |
   * |-----+-----+-----+-----+-----+-----|-----|     |------|-----+-----+-----+-----+-----+-----|
   * |  '  |  A  |  S  |  D  |  F  |  G  | Del |     |Bspace|  H  |  J  |  K  |  L  |  ;  |  -  |
   * |-----+-----+-----+-----+-----+-----|-----'     `------|-----+-----+-----+-----+-----+-----|
   * |Shift|  Z  |  X  |  C  |  V  |  B  |                  |  N  |  M  |  ,  |  .  |  /  |Shift|
   * `-----------------------------------'                  `-----------------------------------|
   * | DF1 |     |     | Ctrl| Alt |                              | Alt | Ctrl|     |     |     |
   * `-----------------------------'                              `-----------------------------'
   *                               ,-----------.     ,------------.
   *                               |           |     |            |
   *                         ,-----+-----------|     |------------+-----.
   *                         |     |     |     |     |      |     |     |
   *                         |Space|Enter|     |     |      |Enter|Space|
   *                         |     |     |     |     |      |     |     |
   *                         `-----------------'     `------------------'
   */
  [STANDARD] = LAYOUT_moonlander(
      KC_ESC , KC_1 , KC_2 , KC_3   , KC_4   , KC_5  , KC_NO , /*|*/ KC_NO  , KC_6  , KC_7   , KC_8   , KC_9  , KC_0   , KC_EQL ,
      KC_NO  , KC_Q , KC_W , KC_E   , KC_R   , KC_T  , KC_TAB, /*|*/ KC_TAB , KC_Y  , KC_U   , KC_I   , KC_O  , KC_P   , KC_NO  ,
      KC_QUOT, KC_A , KC_S , KC_D   , KC_F   , KC_G  , KC_DEL, /*|*/ KC_BSPC, KC_H  , KC_J   , KC_K   , KC_L  , KC_SCLN, KC_MINS,
      KC_LSFT, KC_Z , KC_X , KC_C   , KC_V   , KC_B  ,         /*|*/          KC_N  , KC_M   , KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
      DF(1)  , KC_NO, KC_NO, KC_LCTL, KC_LALT,         KC_NO , /*|*/ KC_NO  ,         KC_RALT, KC_RCTL, KC_NO , KC_NO  , KC_NO  ,
                                      KC_SPC , KC_ENT, KC_NO , /*|*/ KC_NO  , KC_ENT, KC_SPC
  ),

  /* Base layer
   *
   * The base layer adds modifiers and layernavigation.
   * The main design elements are:
   * - Modifiers on the home row keys.
   * - Left-hand layer access, with the right hand accessing keys.

   * Notes:
   * - Most modifiers are made accessible on the home row. Settings are set so
   *   that fast typing will not trigger the modifiers.
   *   Getting used to it required some time. But I eventually found it really
   *   convenient. All symbols are easily accessible with a minimum number of
   *   keys. The symbol layer (on `d`) and shift (on `s`) can conveniently be
   *   used together. For example `{ = s + [ = s+d+k`.
   * - There are no directional keys. Use the MOVEMENT layer instead.
   * - Provide quick access to `-`, used often in the terminal.
   * - Provide quick access to `'`, used often for coding and writing.
   * - The presence of `[` in the base layer is to enable `Ctrl+[` to escape in
   *   (n)vi(m) or tmux.
   *
   */
#define LC(KC) LCTL_T(KC)
#define RC(KC) RCTL_T(KC)
#define LS(KC) LSFT_T(KC)
#define RS(KC) RSFT_T(KC)
   [BASE] = LAYOUT_moonlander(
       _______, _______ , _______ , _______     , _______       , _______, _______,     _______, _______, _______        , _______, _______ , _______    , _______,
       _______, _______ , _______ , _______     , _______       , _______, _______,     _______, _______, _______        , _______, _______ , _______    , KC_LBRC,
       _______, LC(KC_A), LS(KC_S), LT(SYM,KC_D), LT(NUM,KC_F)  , _______, _______,     _______, _______, _______        , _______, RS(KC_L), RC(KC_SCLN), _______,
       CW_TOGG, _______ , _______ , _______     , _______       , _______,                       _______, _______        , _______, _______, _______     , KC_UNDS,
       DF(0)  , _______ , _______ , _______     , _______       ,          TT(FN) ,     KC_CAPS,          _______        , _______, _______ , _______    , _______,
                                                  LGUI_T(KC_SPC), _______, TT(MOV),     TT(MOV), _______, RGUI_T(KC_SPC)
   ),

   /* Symbols
    *
    * ,-----------------------------------------.     ,------------------------------------------.
    * |     |     |     |     |     |     |     |     |      |  ^  |  &  |  *  |  \  |     |     |
    * |-----+-----+-----+-----+-----+-----------|     |------+-----+-----+-----+-----+-----+-----|
    * |     |     |     |     |     |     |     |     |      |  @  |  ~  |  (  |  )  |  `  |     |
    * |-----+-----+-----+-----+-----+-----|-----|     |------|-----+-----+-----+-----+-----+-----|
    * |     |     |     |     |     |     |     |     |      |  #  |  =  |  [  |  ]  |  $  |     |
    * |-----+-----+-----+-----+-----+-----|-----'     `------|-----+-----+-----+-----+-----+-----|
    * |     |     |     |     |     |     |                  |     |     |  <  |  >  |  %  |     |
    * `------------------------------------                  ------------------------------------|
    * |     |     |     |     |     |                              |     |     |     |     |     |
    * `-----------------------------'                              `-----------------------------'
    *                               ,-----------.     ,------------.
    *                               |           |     |            |
    *                         ,-----+-----------|     |------------+-----.
    *                         |     |     |     |     |      |     |     |
    *                         |     |     |     |     |      |     |     |
    *                         |     |     |     |     |      |     |     |
    *                         `-----------------'     `------------------'
    */
    [SYMBOLS] = LAYOUT_moonlander(
        _______, _______, _______, _______, _______, _______, _______,     _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_BSLS, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,     _______, KC_AT  , KC_EXLM, KC_LPRN, KC_RPRN, KC_GRV , _______,
        _______, _______, _______, _______, _______, _______, _______,     _______, KC_HASH, KC_EQL , KC_LBRC, KC_RBRC, KC_DLR , _______,
        _______, _______, _______, _______, _______, _______,                       _______, _______, KC_LT  , KC_GT  , KC_PERC, _______,
        _______, _______, _______, _______, _______,          _______,     _______,          _______, _______, _______, _______, _______,
                                            _______, _______, _______,     _______, _______, _______
    ),

   /* Numeric keypad
    *
    * Modelled after the standard Apple keyboard numeric keypad.
    *
    * ,-----------------------------------------.     ,------------------------------------------.
    * |     |     |     |     |     |     |     |     |      |     |     |  =  |  /  |  *  |     |
    * |-----+-----+-----+-----+-----+-----------|     |------+-----+-----+-----+-----+-----+-----|
    * |     |     |     |     |     |     |     |     |      |     |  7  |  8  |  9  |  -  |     |
    * |-----+-----+-----+-----+-----+-----|-----|     |------|-----+-----+-----+-----+-----+-----|
    * |     |     |     |     |     |     |     |     |      |     |  4  |  5  |  6  |  +  |     |
    * |-----+-----+-----+-----+-----+-----|-----'     `------|-----+-----+-----+-----+-----+-----|
    * |     |     |     |     |     |     |                  |     |  1  |  2  |  3  |     |     |
    * `------------------------------------                  ------------------------------------|
    * |     |     |     |     |     |                              |     |  0  |  .  |     |     |
    * `-----------------------------'                              `-----------------------------'
    *                               ,-----------.     ,------------.
    *                               |           |     |            |
    *                         ,-----+-----------|     |------------+-----.
    *                         |     |     |     |     |      |     |     |
    *                         |     |     |     |     |      |     |     |
    *                         |     |     |     |     |      |     |     |
    *                         `-----------------'     `------------------'
    */
    [NUMERIC] = LAYOUT_moonlander(
        _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, KC_EQL , KC_SLSH, KC_ASTR, _______,
        _______, _______, _______, _______, _______, _______, _______,     _______, _______, KC_7   , KC_8   , KC_9   , KC_MINS, _______,
        _______, _______, _______, _______, _______, _______, _______,     _______, _______, KC_4   , KC_5   , KC_6   , KC_PLUS, _______,
        _______, _______, _______, _______, _______, _______,                       _______, KC_1   , KC_2   , KC_3   , _______, _______,
        _______, _______, _______, _______, _______,          _______,     _______,          _______, KC_0   , KC_DOT , _______, _______,
                                            _______, _______, _______,     _______, _______, _______
    ),

   /* Movement
    *
    * This immitates vim-style movement through standard keys.
    *
    * TODO: Fix for Linux
    *
    * ,-----------------------------------------.     ,------------------------------------------.
    * |     |     |     |     |     |     |     |     |      |     |     |     |     |     |     |
    * |-----+-----+-----+-----+-----+-----------|     |------+-----+-----+-----+-----+-----+-----|
    * |     |     |     |     |     |     |     |     |      |     |     |     |     |     |     |
    * |-----+-----+-----+-----+-----+-----|-----|     |------|-----+-----+-----+-----+-----+-----|
    * |     |     |     |     |     |     |     |     |      |     |     |     |     |     |     |
    * |-----+-----+-----+-----+-----+-----|-----'     `------|-----+-----+-----+-----+-----+-----|
    * |     |     |     |     |     |     |                  |     |     |     |     |     |     |
    * `------------------------------------                  ------------------------------------|
    * |     |     |     |     |     |                              |     |     |     |     |     |
    * `-----------------------------'                              `-----------------------------'
    *                               ,-----------.     ,------------.
    *                               |           |     |            |
    *                         ,-----+-----------|     |------------+-----.
    *                         |     |     |     |     |      |     |     |
    *                         |     |     |     |     |      |     |     |
    *                         |     |     |     |     |      |     |     |
    *                         `-----------------'     `------------------'
    */
    [MOVEMENT] = LAYOUT_moonlander(
        _______, _______, _______   , _______, KC_END    , _______, _______,     _______, _______, _______, _______, _______, KC_HOME, _______,
        _______, _______, A(KC_RGHT), _______, _______   , _______, _______,     _______, _______, KC_PGUP, _______, TG(MOV), _______, _______,
        _______, _______, _______   , KC_PGDN, _______   , _______, _______,     _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_END , _______,
        _______, _______, _______   , _______, _______   , _______,                       _______, _______, _______, _______, _______, _______,
        _______, _______, _______   , _______, A(KC_LEFT),          _______,     _______,          _______, _______, _______, _______, _______,
                                                  _______, _______, _______,     _______, _______, _______
    ),

   /* Function
    *
    * Function and other special keys.
    *
    * TODO: Add media and other keys.
    *
    * ,-----------------------------------------.     ,-----------------------------------------------.
    * |     | F1  | F2  | F3  | F4  | F5  |     |     |      | F6  | F7  | F8  | F9  |     | RGB_TOG  |
    * |-----+-----+-----+-----+-----+-----------|     |------+-----+-----+-----+-----+-----+----------|
    * |     |     |     |     |     |     |     |     |      |     | F7  | F8  | F9  |     | RGB_MOD  |
    * |-----+-----+-----+-----+-----+-----|-----|     |------|-----+-----+-----+-----+-----+----------|
    * |     |     |     |     |     |     |     |     |      |     | F4  | F5  | F6  |     | RGB_RMOD |
    * |-----+-----+-----+-----+-----+-----|-----'     `------|-----+-----+-----+-----+-----+----------|
    * |     |     |     |     |     |     |                  |     | F1  | F2  | F3  |     |          |
    * `------------------------------------                  -----------------------------------------|
    * |     |     |     |     |     |                              |     |     |     |     |          |
    * `-----------------------------'                              `----------------------------------'
    *                               ,-----------.     ,------------.
    *                               |           |     |            |
    *                         ,-----+-----------|     |------------+-----.
    *                         |     |     |     |     |      |     |     |
    *                         |     |     |     |     |      |     |     |
    *                         |g    |     |     |     |      |     |     |
    *                         `-----------------'     `------------------'
    */
    [FUNCTION] = LAYOUT_moonlander(
        _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , _______,     _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , _______, RGB_TOG,
        _______, _______, _______, _______, _______, _______, _______,     _______, _______, KC_F7  , KC_F8  , KC_F9  , _______, RGB_MOD,
        _______, _______, _______, _______, _______, _______, _______,     _______, _______, KC_F4  , KC_F5  , KC_F6  , _______, RGB_RMOD,
        _______, _______, _______, _______, _______, _______,                       _______, KC_F1  , KC_F2  , KC_F3  , _______, _______,
        _______, _______, _______, _______, _______,          _______,     _______,          _______, _______, _______, _______, _______,
                                            _______, _______, _______,     _______, _______, _______
    ),
};


/*
bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LC(KC_A):
    case LS(KC_S):
    case RS(KC_L):
      return true;
    default:
      return false;
  }
}
*/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
        case VRSN:
            SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            return false;
        }
    }
    return true;
}

bool led_update_user(led_t led_state) {
    return true;
}

void caps_word_set_user(bool active) {
    ML_LED_1(false);
    ML_LED_2(false);
    ML_LED_3(false);
    ML_LED_4(false);
    ML_LED_5(false);
    ML_LED_6(false);

    if (active) {
        ML_LED_3(true); ML_LED_6(true);
    }
}

static const struct {
    bool enabled;
    uint8_t r, g, b;
} layers_color_config[] = {
    [STANDARD] = {false,   0,   0,   0},
    [BASE]     = {false,   0,   0,   0},
    [SYMBOLS]  = {true,  255, 192,   0},
    [NUMERIC]  = {true,    0,   0, 255},
    [MOVEMENT] = {true,    0, 255,   0},
    [FUNCTION] = {true,  255,   0,   0},
};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
   if (get_highest_layer(layer_state) > 0) {
       uint8_t layer = get_highest_layer(layer_state);

       // Layer config: [layer]{enabled, r, g, b}
       if (!layers_color_config[layer].enabled) {
           return false;
       }

       for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
           for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
               uint8_t index = g_led_config.matrix_co[row][col];

               if (index >= led_min && index < led_max && index != NO_LED &&
               keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                   rgb_matrix_set_color(index, layers_color_config[layer].r, layers_color_config[layer].g, layers_color_config[layer].b);
               }
           }
       }
   }
   return false;
}

void keyboard_post_init_user(void) {
    // Use this once and comment out, to set the default layer, to avoid repeating the write to EEPROM on every init.
    //set_single_persistent_default_layer(BASE);
}
