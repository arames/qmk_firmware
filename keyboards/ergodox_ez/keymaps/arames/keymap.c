#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "config.h"

#define ________ KC_TRNS

/*
 * Keyboard representation for convenient copy-paste:
 *
 * ,-----------------------------------------------.           ,-----------------------------------------------.
 * |           |     |     |     |     |     |     |           |     |     |     |     |     |     |           |
 * |-----------+-----+-----+-----+-----+-----------|           |-----+-----+-----+-----+-----+-----+-----------|
 * |           |     |     |     |     |     |     |           |     |     |     |     |     |     |           |
 * |-----------+-----+-----+-----+-----+-----|     |           |     |-----+-----+-----+-----+-----+-----------|
 * |           |     |     |     |     |     |-----|           |-----|     |     |     |     |     |           |
 * |-----------+-----+-----+-----+-----+-----|     |           |     |-----+-----+-----+-----+-----+-----------|
 * |           |     |     |     |     |     |     |           |     |     |     |     |     |     |           |
 * `-----------+-----+-----+-----+-----+-----------'           `-----------+-----+-----+-----+-----+-----------'
 *       |     |     |     |     |     |                                   |     |     |     |     |     |
 *       `-----------------------------'                                   `-----------------------------'
 *                                     ,-----------.           ,-----------.
 *                                     |     |     |           |     |     |
 *                               ,-----|-----|-----|           |-----+-----+-----.
 *                               |     |     |     |           |     |     |     |
 *                               |     |     |-----|           |-----|     |     |
 *                               |     |     |     |           |     |     |     |
 *                               `-----------------'           `-----------------'
 */

/*
 * Key layouts for both hands for convenient copy-paste.
 *
 * [LAYER_INDEX] = LAYOUT_ergodox(
 *     ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
 *     ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
 *     ________ , ________ , ________ , ________ , ________ , ________ ,
 *     ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
 *     ________ , ________ , ________ , ________ , ________ ,
 *
 *                                                            ________ , ________ ,
 *                                                                       ________ ,
 *                                                 ________ , ________ , ________ ,
 *
 *     ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
 *     ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
 *                ________ , ________ , ________ , ________ , ________ , ________ ,
 *     ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
 *                           ________ , ________ , ________ , ________ , ________ ,
 *
 *     ________ , ________ ,
 *     ________ ,
 *     ________ , ________ , ________
 *     ),
 */


// TODO:
// * num layer
// 2) Test shift/caps with tap dance.
//    b) turn on a led in caps
// 3) Movement layer vim style? Plus includes up/down home/end keys?
// 10) Consider a vim layer. See `keyboards/ergodox_ez/keymaps/vim/`.

// ## Symbols use (short) study:
//
// Characters `,`, `.`, `/`, `;`, and `:` are used extremely frequently.
// (Use-cases: filesystem paths, vim , writing.)
//
// To select candidates for the basex layer or convenient position, here is a
// count of characters in typical C++ code I work on:
//     )  77172
//     (  77133
//     :  67577
//     /  48201
//     .  46250
//     ;  42996
//     ,  40950
//     _  34014
//     -  32667
//     =  28254
//     *  19205
//     >  19090
//     {  11550
//     }  11549
//     "  11223
//     &  10045
//     <  6420
//     !  3786
//     '  2921
//     +  2848
//     [  2679
//     ]  2676
//     |  2356
//     #  1225
//     \  711
//     %  224
//     @  149
//     `  125
//     $  86
//     ~  71
//     ^  4
//

enum KeyboardLayers {
  BASE,
  EXPERIMENTAL,
  NORMAL,
  SYMBOLS,
  NUMERIC,
  MOVEMENT,

  // Aliases
  EXP = EXPERIMENTAL,
  NOR = NORMAL,
  SYM = SYMBOLS,
  NUM = NUMERIC,
  MOV = MOVEMENT
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Basic layer
   *
   * ,--------------------------------------------------.           ,------------------------------------------------.
   * |     Esc     |  0  |  1  |  2  |  3  |  4  |      |           |      |  5  |  6  |  7  |  8  |  9  |    =      |
   * |-------------+-----+-----+-----+-----+------------|           |------+-----+-----+-----+-----+-----+-----------|
   * | LT(MOV, \)  |  Q  |  W  |  E  |  R  |  T  | Tab  |           | Tab  |  Y  |  U  |  I  |  O  |  P  |    [      |
   * |-------------+-----+-----+-----+-----+-----|      |           |      |-----+-----+-----+-----+-----+-----------|
   * |   LCtrl/'   |  A  |  S  |  D  |  F  |  G  |------|           |------|  H  |  J  |  K  |  L  |  ;  |  RCtrl/-  |
   * |-------------+-----+-----+-----+-----+-----| Del  |           |Bspace|-----+-----+-----+-----+-----+-----------|
   * |   LShift    |  Z  |  X  |  C  |  V  |  B  |      |           |      |  N  |  M  |  ,  |  .  |  /  |  RShift   |
   * `--------------------------------------------------'           `------------------------------------------------'
   *        |      |     |     | Alt | Cmd |                                     |Left |Down | Up  |Right|      |
   *        `------------------------------'                                     `------------------------------'
   *                                         ,-------------.       ,--------------.
   *                                         |CAPS |       |       |TO NORM|      |
   *                                   ,-----|-----|-------|       |-------+------+------.
   *                                   |     |     |       |       |TO EXP |      |      |
   *                                   | OSL | TT  |-------|       |-------|Enter |Space |
   *                                   | SYM | NUM |MO MOV |       |TO BASE|      |      |
   *                                   `-------------------'       `---------------------'
   *
   * Notes:
   * - The presence of `[` in the basic layer is to enable `Ctrl+[` to escape in
   *   (n)vi(m).
   * - Provide quick access to `-`, used so often in the terminal.
   */
  [BASE] = LAYOUT_ergodox(
      KC_ESC           , KC_1     , KC_2     , KC_3    , KC_4      , KC_5      , ________ ,
      LT(MOV, KC_BSLS) , KC_Q     , KC_W     , KC_E    , KC_R      , KC_T      , KC_TAB   ,
      LCTL_T(KC_QUOTE) , KC_A     , KC_S     , KC_D    , KC_F      , KC_G      ,
      KC_LSHIFT        , KC_Z     , KC_X     , KC_C    , KC_V      , KC_B      , KC_DEL   ,
      ________         , ________ , ________ , KC_LALT , KC_LGUI   ,
                                                                     KC_CAPS   , ________ ,
                                                                                 ________ ,
                                                         OSL(SYM)  , TT(NUM)   , MO(MOV)  ,

      ________         , KC_6     , KC_7     , KC_8     , KC_9     , KC_0      , KC_EQUAL  ,
      KC_TAB           , KC_Y     , KC_U     , KC_I     , KC_O     , KC_P      , KC_LBRC   ,
                         KC_H     , KC_J     , KC_K     , KC_L     , KC_SCOLON , RCTL_T(KC_MINUS) ,
      KC_BSPC          , KC_N     , KC_M     , KC_COMMA , KC_DOT   , KC_SLASH  , KC_RSHIFT ,
      KC_LEFT          , KC_DOWN  , KC_UP    , KC_RIGHT , ________ ,
      TO(NOR)          , ________ ,
      TO(EXP)          ,
      TO(BASE)         , KC_ENTER , KC_SPACE
      ),

  /* Experimental layer
   *
   * Use this layer to test out changes to the base layer.
   *
   * ,-------------------------------------------------.           ,-----------------------------------------------.
   * |           |     |     |     |     |     |       |           |     |     |     |     |     |     |           |
   * |-----------+-----+-----+-----+-----+-------------|           |-----+-----+-----+-----+-----+-----+-----------|
   * |           |     |     |     |     |     |       |           |     |     |     |     |     |     |           |
   * |-----------+-----+-----+-----+-----+-----|       |           |     |-----+-----+-----+-----+-----+-----------|
   * |           |     |     |     |     |     |-------|           |-----|     |     |     |     |     |           |
   * |-----------+-----+-----+-----+-----+-----|       |           |     |-----+-----+-----+-----+-----+-----------|
   * |           |     |     |     |     |     |       |           |     |     |     |     |     |     |           |
   * `-----------+-----+-----+-----+-----+-------------'           `-----------+-----+-----+-----+-----+-----------'
   *       |     |     |     |     |     |                                     |     |     |     |     |     |
   *       `-----------------------------'                                     `-----------------------------'
   *                                     ,-------------.           ,-----------.
   *                                     |     |       |           |     |     |
   *                               ,-----|-----|-------|           |-----+-----+-----.
   *                               |     |     |       |           |     |     |     |
   *                               |     |     |-------|           |-----|     |     |
   *                               |     |     |       |           |     |     |     |
   *                               `-------------------'           `-----------------'
   */
  [EXPERIMENTAL] = LAYOUT_ergodox(
      ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
      ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
      ________ , ________ , ________ , ________ , ________ , ________ ,
      ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
      ________ , ________ , ________ , ________ , ________ ,
 
                                                             ________ , ________ ,
                                                                        ________ ,
                                                  ________ , ________ , ________ ,
 
      ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
      ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
                 ________ , ________ , ________ , ________ , ________ , ________ ,
      ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
                            ________ , ________ , ________ , ________ , ________ ,
 
      ________ , ________ ,
      ________ ,
      ________ , ________ , ________
      ),

  /* Normal layer
   *
   * This layer avoids any special features, to map closely to a "normal" layout.
   * TODO
   *
   * ,--------------------------------------------------.           ,------------------------------------------------.
   * |     Esc     |  0  |  1  |  2  |  3  |  4  |      |           |      |  5  |  6  |  7  |  8  |  9  |    =      |
   * |-------------+-----+-----+-----+-----+------------|           |------+-----+-----+-----+-----+-----+-----------|
   * | LT(MOV, \)  |  Q  |  W  |  E  |  R  |  T  | Tab  |           | Tab  |  Y  |  U  |  I  |  O  |  P  |    [      |
   * |-------------+-----+-----+-----+-----+-----|      |           |      |-----+-----+-----+-----+-----+-----------|
   * |   LCtrl/'   |  A  |  S  |  D  |  F  |  G  |------|           |------|  H  |  J  |  K  |  L  |  ;  |  RCtrl/-  |
   * |-------------+-----+-----+-----+-----+-----| Del  |           |Bspace|-----+-----+-----+-----+-----+-----------|
   * |   LShift    |  Z  |  X  |  C  |  V  |  B  |      |           |      |  N  |  M  |  ,  |  .  |  /  |  RShift   |
   * `--------------------------------------------------'           `------------------------------------------------'
   *        |      |     |     | Alt | Cmd |                                     |Left |Down | Up  |Right|      |
   *        `------------------------------'                                     `------------------------------'
   *                                         ,-------------.       ,--------------.
   *                                         |CAPS |       |       |       |      |
   *                                   ,-----|-----|-------|       |-------+------+------.
   *                                   |     |     |       |       |       |      |      |
   *                                   | OSL | TT  |-------|       |-------|Enter |Space |
   *                                   | SYM | NUM |MO MOV |       |       |      |      |
   *                                   `-------------------'       `---------------------'
   */
  [NORMAL] = LAYOUT_ergodox(
      KC_ESC           , KC_1     , KC_2     , KC_3    , KC_4      , KC_5      , ________ ,
      LT(MOV, KC_BSLS) , KC_Q     , KC_W     , KC_E    , KC_R      , KC_T      , KC_TAB   ,
      LCTL_T(KC_QUOTE) , KC_A     , KC_S     , KC_D    , KC_F      , KC_G      ,
      KC_LSHIFT        , KC_Z     , KC_X     , KC_C    , KC_V      , KC_B      , KC_DEL   ,
      ________         , ________ , ________ , KC_LALT , KC_LGUI   ,
                                                                     KC_CAPS   , ________ ,
                                                                                 ________ ,
                                                         OSL(SYM)  , TT(NUM)   , MO(MOV)  ,

      ________         , KC_6     , KC_7     , KC_8     , KC_9     , KC_0      , KC_EQUAL  ,
      KC_TAB           , KC_Y     , KC_U     , KC_I     , KC_O     , KC_P      , KC_LBRC   ,
                         KC_H     , KC_J     , KC_K     , KC_L     , KC_SCOLON , RCTL_T(KC_MINUS) ,
      KC_BSPC          , KC_N     , KC_M     , KC_COMMA , KC_DOT   , KC_SLASH  , KC_RSHIFT ,
      KC_LEFT          , KC_DOWN  , KC_UP    , KC_RIGHT , ________ ,
      ________         , ________ ,
      ________         ,
      ________         , KC_ENTER , KC_SPACE
      ),

  /* Symbols
   *
   * Notes:
   * - Symbols on the first row mostly match a "normal" layout.
   * - TODO `+`, `-`, `*`, `/` should be available in the same place as for the
   *   numeric layer.
   *  - TODO: Are angled-brackets in the wrong place? With shift, they are one row higher
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
   *   TODO: priority:
   *        `_` on a non-modified key would be nice
   *
   *  TODO: Other idea: move space/enter down a key, to allow OSL on the right
   *  hand, and spread keys on both hands.
   *  Or use LT to make it do both
   *
   * ,-------------------------------------------.           ,-------------------------------------------.
   * |       |     |     |     |     |     |                 |     |  ^  |  &  |  *  |  |  |  ~  |       |
   * |-------+-----+-----+-----+-----+-----------|           |-----+-----+-----+-----+-----+-----+-------|
   * |       |     |     |     |     |     |     |           |     |  @  |  !  |  (  |  )  |  `  |   _   |
   * |-------+-----+-----+-----+-----+-----|     |           |     |-----+-----+-----+-----+-----+-------|
   * |       |     |     |     |     |     |-----|           |-----|  #  |  =  |  {  |  }  |  $  |   -   |
   * |-------+-----+-----+-----+-----+-----|     |           |     |-----+-----+-----+-----+-----+-------|
   * |       |     |     |     |     |     |     |           |     |  \  |  +  |  [  |  ]  |  %  |       |
   * '-------+-----+-----+-----+-----+-----------'            -----------+-----+-----+-----+-----+-------'
   *   |     |     |     |     |     |                                   |     |  <  |  >  |     |     |
   *   `-----------------------------'                                   `-----------------------------'
   *                                   ,-----------.       ,-----------.
   *                                   |     |     |       |     |     |
   *                            ,------|-----|-----|       |-----+-----+------.
   *                            |      |     |     |       |     |     |      |
   *                            |      |     |-----|       |-----|     |      |
   *                            |      |     |     |       |     |     |      |
   *                            `------------------'       `------------------'
   */
  [SYMBOLS] = LAYOUT_ergodox(
      ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
      ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
      ________ , ________ , ________ , ________ , ________ , ________ ,
      ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
      ________ , ________ , ________ , ________ , ________ ,
                                                             ________ , ________ ,
                                                                        ________ ,
                                                  ________ , ________ , ________ ,

      ________ , KC_CIRC  , KC_AMPR  , KC_ASTR  , KC_PIPE  , KC_TILDE , ________ ,
      ________ , KC_AT    , KC_EXLM  , KC_LPRN  , KC_RPRN  , KC_GRAVE , KC_UNDS  ,
                 KC_HASH  , KC_EQUAL , KC_LCBR  , KC_RCBR  , KC_DLR   , KC_MINUS ,
      ________ , KC_BSLS  , KC_PLUS  , KC_LBRC  , KC_RBRC  , KC_PERC  , ________ ,
                            ________ , KC_LT    , KC_GT    , ________ , ________ ,
      ________ , ________ ,
      ________ ,
      ________ , ________ , ________
  ),

  /* Numeric keypad
   *
   * ,-------------------------------------------.           ,-------------------------------------------.
   * |       |     |     |     |     |     |     |           |     |     |     |     |     |     |       |
   * |-------+-----+-----+-----+-----+-----------|           |-----+-----+-----+-----+-----+-----+-------|
   * |       |     |     |     |     |     |     |           |     |     |  7  |  8  |  9  |     |       |
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
   *                            |      |     |     |       |     |     |      |
   *                            `------------------'       `------------------'
   */
  [NUMERIC] = LAYOUT_ergodox(
      ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
      ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
      ________ , ________ , ________ , ________ , ________ , ________ ,
      ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
      ________ , ________ , ________ , ________ , ________ ,
                                                             ________ , ________ ,
                                                                        ________ ,
                                                  ________ , ________ , ________ ,

      ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
      ________ , ________ , KC_KP_7  , KC_KP_8  , KC_KP_9  , ________ , ________ ,
                 KC_PLUS  , KC_KP_4  , KC_KP_5  , KC_KP_6  , KC_PAST  , ________ ,
      ________ , KC_MINS  , KC_KP_1  , KC_KP_2  , KC_KP_3  , KC_PSLS  , ________ ,
                            KC_TAB   , KC_KP_0  , KC_PDOT  , KC_PEQL  , ________ ,
      ________ , ________ ,
      ________ ,
      ________ , ________ , ________
  ),
  /*
 * ,---------------------------------------------------.           ,-----------------------------------------------------.
 * |             |     |     |     |     |      |      |           |      |      |      |      |      |      |           |
 * |-------------+-----+-----+-----+-----+-------------|           |------+------+------+------+------+------+-----------|
 * |             |     |     |     |     |      |      |           |      |      |      |      |      |      |           |
 * |-------------+-----+-----+-----+-----+------|      |           |      |------+------+------+------+------+-----------|
 * |             |     |     |     |     |      |------|           |------| Left | Down |  Up  |Right |      |           |
 * |-------------+-----+-----+-----+-----+------|      |           |      |------+------+------+------+------+-----------|
 * |             |     |     |     |     |      |      |           |      |      |      |      |      |      |           |
 * `-------------+-----+-----+-----+-----+-------------'           `-------------+------+------+------+------+-----------'
 *        |      |     |     |     |     |                                       |      |      |      |      |      |
 *        `------------------------------'                                       `----------------------------------'
 *                                         ,------------.       ,-------------.
 *                                         |     |      |       |      |      |
 *                                   ,-----|-----|------|       |------+------+------.
 *                                   |     |     |      |       |      |      |      |
 *                                   |     |     |------|       |------|      |      |
 *                                   |     |     |      |       |      |      |      |
 *                                   `------------------'       `--------------------'
 */
  [MOVEMENT] = LAYOUT_ergodox(
      ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
      ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
      ________ , ________ , ________ , ________ , ________ , ________ ,
      ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
      ________ , ________ , ________ , ________ , ________ ,
                                                             ________ , ________ ,
                                                                        ________ ,
                                                  ________ , ________ , ________ ,

      ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
      ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
                 KC_LEFT  , KC_DOWN  , KC_UP    , KC_RIGHT , ________ , ________ ,
      ________ , ________ , ________ , ________ , ________ , ________ , ________ ,
                            ________ , ________ , ________ , ________ , ________ ,
      ________ , ________ ,
      ________ ,
      ________ , ________ , ________
  ),
};


// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  ergodox_led_all_off();
};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

  ergodox_led_all_off();

  uint8_t layer = biton32(layer_state);

  switch (layer) {
    case EXPERIMENTAL:
      ergodox_right_led_1_on();
      break;
    case SYMBOLS:
      ergodox_right_led_2_on();
      break;
    case NUMERIC:
      ergodox_right_led_3_on();
      break;
    default:
      break;
  }
};
