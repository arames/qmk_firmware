#include QMK_KEYBOARD_H
#include "quantum.h"

#define ____ KC_TRANSPARENT
#define ______ KC_TRANSPARENT
#define ________ KC_TRANSPARENT

// Layers ----------------------------------------------------------------------

enum KeyboardLayers {
  BASE,
  SYMBOLS,
  NUMERIC,
  MOVEMENT,

  // Aliases
  SYM = SYMBOLS,
  NUM = NUMERIC,
  MOV = MOVEMENT
};

#define LC(KC) LCTL_T(KC)
#define RC(KC) RCTL_T(KC)
#define LS(KC) LSFT_T(KC)
#define RS(KC) RSFT_T(KC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base layer
   *
   * Notes:
   * - Most modifiers are made accessible on the home row. Settings are set so
   *   that fast typing will not trigger the modifiers.
   *   Getting used to it requires some time. But eventually I found it really
   *   convenient.
   * - Since the SYM and shift keys are very easy to press together, accessing
   *   shifted special keys is very easy (e.g. curly brackets).
   * - The (hold) shift key on the left hand is more convenient than CAPS
   * - There are no directional keys. Use the MOVEMENT layer instead.
   * - Provide quick access to `-`, used often in the terminal.
   * - Provide quick access to `'`, used often for coding and writing.
   * - The presence of `[` in the base layer is to enable `Ctrl+[` to escape in
   *   (n)vi(m).
   *
   * TODO:
   * - Have a LED indicate the CAPS status.
   *
   * ,---------------------------------------------------.           ,------------------------------------------------------.
   * |   Esc   |   1   |    2   |  3  |  4  |  5  |      |           |      |  6  |  7  |  8  |    9     |    0    |    =   |
   * |---------+-------+--------+-----+-----+------------|           |------+-----+-----+-----+----------+---------+--------|
   * | TT MOV  |   Q   |    W   |  E  |  R  |  T  | Tab  |           | Tab  |  Y  |  U  |  I  |    O     |    P    |    [   |
   * |---------+-------+--------+-----+-----+-----|      |           |      |-----+-----+-----+----------+---------+--------|
   * |    '    |A/LCtrl|S/LShift|D/SYM|F/NUM|  G  |------|           |------|  H  |  J  |  K  | LShift/L | LCtrl/; |    -   |
   * |---------+-------+--------+-----+-----+-----| Del  |           |Bspace|-----+-----+-----+----------+---------+--------|
   * |   CAPS  |   Z   |    X   |  C  |  V  |  B  |      |           |      |  N  |  M  |  ,  |    .     |    /    |  CAPS  |
   * `---------------------------------------------------'           `------------------------------------------------------'
   *      |    |       |        |     | Alt |                                     | Alt |     |          |         |     |
   *      `---------------------------------'                                     `--------------------------------------'
   *                                         ,--------------.       ,---------------.
   *                                         |TT NUM|       |       |       |       |
   *                                   ,-----|------|-------|       |-------+-------+-----.
   *                                   |GUI/ |Shift/|       |       |       |       |GUI/ |
   *                                   |Space|Enter |-------|       |-------| Enter |Space|
   *                                   |     |      |TT MOV |       |TT MOV |       |     |
   *                                   `--------------------'       `---------------------'
   */
  [BASE] = LAYOUT_ergodox_pretty(
      KC_ESC   , KC_1     , KC_2     , KC_3        , KC_4         , KC_5         , _______ , /*|*/ _______ , KC_6     , KC_7     , KC_8     , KC_9     , KC_0          , KC_EQUAL  ,
      TT(MOV)  , KC_Q     , KC_W     , KC_E        , KC_R         , KC_T         , KC_TAB  , /*|*/ KC_TAB  , KC_Y     , KC_U     , KC_I     , KC_O     , KC_P          , KC_LBRC   ,
      KC_QUOTE , LC(KC_A) , LS(KC_S) , LT(SYM,KC_D), LT(NUM,KC_F) , KC_G         ,           /*|*/           KC_H     , KC_J     , KC_K     , RS(KC_L) , RC(KC_SCOLON) , KC_MINUS ,
      KC_CAPS  , KC_Z     , KC_X     , KC_C        , KC_V         , KC_B         , KC_DEL  , /*|*/ KC_BSPC , KC_N     , KC_M     , KC_COMMA , KC_DOT   , KC_SLASH      , KC_CAPS ,
      ________ , ____     , ____     , _______     , KC_LALT      ,                          /*|*/ KC_RALT , _______  , _______  , ________ , ______   ,
                                                                    TT(NUM)      , _______ , /*|*/ _______ , _______  ,
                                                                                   _______ , /*|*/ _______ ,
                                                 LGUI_T(KC_SPACE) , LS(KC_ENTER) , TT(MOV) , /*|*/ TT(MOV) , KC_ENTER , GUI_T(KC_SPACE)
      ),

  /* Symbols
   *
   * Notes:
   * - Symbols on the top row mostly match a "normal" layout.
   * - Since the base layer has the shift and symbol modifier/layer next to each
   *   other (on S and D), accessing the shifted symbols is easy, and we do not
   *   need to allocate a key for shifted symbols!
   *
   * - TODO: Like multiple TODOs below already indicate (some of them may be
   *   obsolete), there should be some coherency between the base, symbols, and
   *   num layers.
   *
   * - TODO `+`, `-`, `*`, `/` should be available in the same place as for the
   *   numeric layer.
   *
   * Misc notes:
   * - `$` and `%` next to each other work quite well:
   *   - The combination end-of-line / matching bracket/parenthesis.
   *   - They are also close to the `/`, so work well with my vim "path"
   *   shortcuts `%%` and `$$`.
   *
   * - TODO: Missing symbols : ! @ # $ % + -  ^   &  *  |  ~  =
   *   relations: ^ $
   *          - / * & |
   *            (div mul) (deref addrs) (and or)
   *            but they are not used as pairs. So they can be close, but don't
   *            require fast successive typing.
   *          + -
   *
   * ,-------------------------------------------.           ,-------------------------------------------.
   * |       |     |     |     |     |     |                 |     |  ^  |  &  |  *  |  \  |     |       |
   * |-------+-----+-----+-----+-----+-----------|           |-----+-----+-----+-----+-----+-----+-------|
   * |       |     |     |     |     |     |     |           |     |  @  |  !  |  (  |  )  |  `  |       |
   * |-------+-----+-----+-----+-----+-----|     |           |     |-----+-----+-----+-----+-----+-------|
   * |       |     |     |     |     |     |-----|           |-----|  #  |  =  |  [  |  ]  |  $  |       |
   * |-------+-----+-----+-----+-----+-----|     |           |     |-----+-----+-----+-----+-----+-------|
   * |       |     |     |     |     |     |     |           |     |     |     |  <  |  >  |  %  |       |
   * '-------+-----+-----+-----+-----+-----------'            -----------+-----+-----+-----+-----+-------'
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
  [SYMBOLS] = LAYOUT_ergodox_pretty(
      ________ , ________ , ________ , ________ , ________ , ________ , ________ , /*|*/ ________ , KC_CIRC  , KC_AMPR  , KC_ASTR  , KC_BSLS  , ________ , ________ ,
      ________ , ________ , ________ , ________ , ________ , ________ , ________ , /*|*/ ________ , KC_AT    , KC_EXLM  , KC_LPRN  , KC_RPRN  , KC_GRAVE , ________ ,
      ________ , ________ , ________ , ________ , ________ , ________ ,            /*|*/            KC_HASH  , KC_EQUAL , KC_LBRC  , KC_RBRC  , KC_DLR   , ________ ,
      ________ , ________ , ________ , ________ , ________ , ________ , ________ , /*|*/ ________ , ________ , ________ , KC_LT    , KC_GT    , KC_PERC  , ________ ,
      ________ , ________ , ________ , ________ , ________ ,                       /*|*/                       ________ , ________ , ________ , ________ , ________ ,
                                                             ________ , ________ , /*|*/ ________ , ________ ,
                                                                        ________ , /*|*/ ________ ,
                                                  ________ , ________ , ________ , /*|*/ ________ , ________ , ________
  ),

  /* Numeric keypad
   *
   * ,-------------------------------------------.           ,-------------------------------------------.
   * |       |     |     |     |     |     |     |           |     |     |     |     |     |     |       |
   * |-------+-----+-----+-----+-----+-----------|           |-----+-----+-----+-----+-----+-----+-------|
   * |       |     |     |     |     |     |     |           |     |     |  7  |  8  |  9  |     |       |
   * |-------+-----+-----+-----+-----+-----|     |           |     |-----+-----+-----+-----+-----+-------|
   * |       |     |     |     |     |     |-----|           |-----|  +  |  4  |  5  |  6  |  *  |       |
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
   *                            |      |     |     |       |     |     |      |
   *                            `------------------'       `------------------'
   */
  [NUMERIC] = LAYOUT_ergodox_pretty(
      ________ , ________ , ________ , ________ , ________ , ________ , ________ , /*|*/ ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
      ________ , ________ , ________ , ________ , ________ , ________ , ________ , /*|*/ ________ , ________ , KC_KP_7  , KC_KP_8  , KC_KP_9  , ________ , ________ ,
      ________ , ________ , ________ , ________ , ________ , ________ ,            /*|*/            KC_PLUS  , KC_KP_4  , KC_KP_5  , KC_KP_6  , KC_PAST  , ________ ,
      ________ , ________ , ________ , ________ , ________ , ________ , ________ , /*|*/ ________ , KC_MINS  , KC_KP_1  , KC_KP_2  , KC_KP_3  , KC_PSLS  , ________ ,
      ________ , ________ , ________ , ________ , ________ ,                       /*|*/                       KC_TAB   , KC_KP_0  , KC_PDOT  , KC_PEQL  , ________ ,
                                                             ________ , ________ , /*|*/ ________ , ________ ,
                                                                        ________ , /*|*/ ________ ,
                                                  ________ , ________ , ________ , /*|*/ ________ , ________ , ________
  ),

  [MOVEMENT] = LAYOUT_ergodox_pretty(
      ________ , ________ , ________    , ________ , KC_END   , ________   , ________ , /*|*/ ________ , ________ , ________ , ________ , ________ , KC_HOME  , ________ ,
      ________ , ________ , A(KC_RIGHT) , ________ , ________ , ________   , ________ , /*|*/ ________ , ________ , KC_PGUP  , TT(MOV)  , ________ , ________ , ________ ,
      ________ , ________ , ________    , KC_PGDN  , ________ , ________   ,            /*|*/            KC_LEFT  , KC_DOWN  , KC_UP    , KC_RIGHT , KC_END   , ________ ,
      ________ , ________ , ________    , ________ , ________ , A(KC_LEFT) , ________ , /*|*/ ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
      ________ , ________ , ________    , ________ , ________ ,                         /*|*/                       ________ , ________ , ________ , ________ , ________ ,
                                                                ________   , ________ , /*|*/ ________ , ________ ,
                                                                             ________ , /*|*/ ________ ,
                                                     ________ , ________   , ________ , /*|*/ ________ , ________ , ________
  )
};

bool get_ignore_mod_tap_interrupt(uint16_t keycode) {
  switch (keycode) {
    case LC(KC_A):
    case LS(KC_S):
    case RS(KC_L):
      return true;
    default:
      return false;
  }
}

// Matrix ----------------------------------------------------------------------

// Runs only once when the keyboard initializes.
void matrix_init_user(void) {
  ergodox_led_all_off();
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
  ergodox_led_all_off();

  uint8_t layer = biton32(layer_state);

  switch (layer) {
    case NUMERIC:
      ergodox_right_led_2_on();
      break;
    case MOVEMENT:
      ergodox_right_led_3_on();
      break;
    default:
      break;
  }
};
