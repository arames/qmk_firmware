#include QMK_KEYBOARD_H
#include "quantum.h"

#define ____ KC_TRANSPARENT
#define ______ KC_TRANSPARENT
#define ________ KC_TRANSPARENT

// Tap Dance -------------------------------------------------------------------

enum {
  TD_LSFTCAPS,
  TD_RSFTCAPS,
};

// This simple version does not work on macOS, as CAPS has to be pressed for
// some amount of time.
// qk_tap_dance_action_t tap_dance_actions[] = {
//   // Tap once for LShift, and twice for CAPS.
//   [TD_LSFTCAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
//   // Tap once for RShift, and twice for CAPS.
//   [TD_RSFTCAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS),
// };

// TODO: Is there a better way to track the state of caps lock?
bool caps_on = false;

void dance_kccaps_finished(qk_tap_dance_state_t *state, void *user_data, uint16_t kc) {
  if (state->count == 1) {
    register_code(kc);
  } else {
    register_code(KC_CAPS);
  }
}
void dance_lsftcaps_finished(qk_tap_dance_state_t *state, void *user_data) {
  dance_kccaps_finished(state, user_data, KC_LSFT);
}
void dance_rsftcaps_finished(qk_tap_dance_state_t *state, void *user_data) {
  dance_kccaps_finished(state, user_data, KC_RSFT);
}
void dance_kccaps_reset(qk_tap_dance_state_t *state, void *user_data, uint16_t kc) {
  if (state->count == 1) {
    unregister_code(kc);
  } else {
    _delay_ms(100); // For macOS. See note above.
    unregister_code(KC_CAPS);
    caps_on ^= 1;
  }
}
void dance_lsftcaps_reset(qk_tap_dance_state_t *state, void *user_data) {
  dance_kccaps_reset(state, user_data, KC_LSFT);
}
void dance_rsftcaps_reset(qk_tap_dance_state_t *state, void *user_data) {
  dance_kccaps_reset(state, user_data, KC_RSFT);
}
qk_tap_dance_action_t tap_dance_actions[] = {
 [TD_LSFTCAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_lsftcaps_finished, dance_lsftcaps_reset),
 [TD_RSFTCAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_rsftcaps_finished, dance_rsftcaps_reset)
};

// Layers ----------------------------------------------------------------------

enum KeyboardLayers {
  BASE,
  EXPERIMENTAL,
  SYMBOLS,
  NUMERIC,

  // Aliases
  EXP = EXPERIMENTAL,
  SYM = SYMBOLS,
  NUM = NUMERIC,
};

#define LC(KC) LCTL_T(KC)
#define RC(KC) RCTL_T(KC)
#define LS(KC) LSFT_T(KC)
#define RS(KC) RSFT_T(KC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Basic layer
   *
   * ,--------------------------------------------------.           ,------------------------------------------------.
   * |     Esc     |  1  |  2  |  3  |  4  |  5  |      |           |      |  6  |  7  |  8  |  9  |  0  |    =      |
   * |-------------+-----+-----+-----+-----+------------|           |------+-----+-----+-----+-----+-----+-----------|
   * |             |  Q  |  W  |  E  |  R  |  T  | Tab  |           | Tab  |  Y  |  U  |  I  |  O  |  P  |    [      |
   * |-------------+-----+-----+-----+-----+-----|      |           |      |-----+-----+-----+-----+-----+-----------|
   * |   LCtrl/'   |  A  |  S  |  D  |  F  |  G  |------|           |------|  H  |  J  |  K  |  L  |  ;  |  RCtrl/-  |
   * |-------------+-----+-----+-----+-----+-----| Del  |           |Bspace|-----+-----+-----+-----+-----+-----------|
   * |   LShift    |  Z  |  X  |  C  |  V  |  B  |      |           |      |  N  |  M  |  ,  |  .  |  /  |  RShift   |
   * `--------------------------------------------------'           `------------------------------------------------'
   *        |      |     |     | Alt | Cmd |                                     |Left |Down | Up  |Right|      |
   *        `------------------------------'                                     `------------------------------'
   *                                         ,-------------.       ,---------------.
   *                                         |CAPS |       |       |TO BASE|TO EXP |
   *                                   ,-----|-----|-------|       |-------+-------+------.
   *                                   |     |     |       |       |       |       |      |
   *                                   | OSL | TT  |-------|       |-------| Enter |Space |
   *                                   | SYM | NUM |       |       |       |       |      |
   *                                   `-------------------'       `----------------------'
   *
   * Notes:
   * - The presence of `[` in the basic layer is to enable `Ctrl+[` to escape in
   *   (n)vi(m).
   * - Provide quick access to `-`, used so often in the terminal.
   */
  [BASE] = LAYOUT_ergodox_pretty(
      KC_ESC           , KC_1     , KC_2     , KC_3    , KC_4      , KC_5      , ________ , /**/ ________ , KC_6     , KC_7     , KC_8     , KC_9     , KC_0      , KC_EQUAL  ,                                
      ________         , KC_Q     , KC_W     , KC_E    , KC_R      , KC_T      , KC_TAB   , /**/ KC_TAB   , KC_Y     , KC_U     , KC_I     , KC_O     , KC_P      , KC_LBRC   ,                                
      LCTL_T(KC_QUOTE) , KC_A     , KC_S     , KC_D    , KC_F      , KC_G      ,            /**/            KC_H     , KC_J     , KC_K     , KC_L     , KC_SCOLON , RCTL_T(KC_MINUS) ,              
      KC_LSHIFT        , KC_Z     , KC_X     , KC_C    , KC_V      , KC_B      , KC_DEL   , /**/ KC_BSPC  , KC_N     , KC_M     , KC_COMMA , KC_DOT   , KC_SLASH  , KC_RSHIFT ,                                
      ________         , ________ , ________ , KC_LALT , KC_LGUI   ,                        /**/ KC_LEFT  , KC_DOWN  , KC_UP    , KC_RIGHT , ________ ,                                 
                                                                     KC_CAPS   , ________ , /**/ TO(BASE) , TO(EXP) ,                                                                                         
                                                                                 ________ , /**/ ________ ,                                                                                                    
                                                         OSL(SYM)  , TT(NUM)   , ________ , /**/ ________ , KC_ENTER , KC_SPACE                                                                                
      ),
  /* Experimental
   *
   * Notes:
   * - Most modifiers are made accessible on the home row. Settings are such
   *   that fast typing will not trigger the modifiers.
   * - The presence of `[` in the basic layer is to enable `Ctrl+[` to escape in
   *   (n)vi(m).
   * - Provide quick access to `-`, used often in the terminal.
   * - Provide quick access to `'`, used often for coding and writing.
   * - Since the SYM and shift keys are very easy to press together, accessing
   *   `_` and `"` is easy.
   *
   * TODO:
   * - Remove redundant keys:
   *   - Lshift is available on S and L, so is not needed with CAPS.
   *   - Cmd is availble next to the left enter, so not needed in the left
   *   hand bottom row.
   *   - Directional keys could be removed in favour of a move layer.
   *
   * ,-------------------------------------------------------.           ,-----------------------------------------------------------.
   * |     Esc     |   1   |    2   |  3  |  4  |  5  |      |           |      |  6  |  7  |  8  |    9     |    0    |      =      |
   * |-------------+-------+--------+-----+-----+------------|           |------+-----+-----+-----+----------+---------+-------------|
   * |             |   Q   |    W   |  E  |  R  |  T  | Tab  |           | Tab  |  Y  |  U  |  I  |    O     |    P    |      [      |
   * |-------------+-------+--------+-----+-----+-----|      |           |      |-----+-----+-----+----------+---------+-------------|
   * |      '      |A/LCtrl|S/LShift|D/SYM|F/NUM|  G  |------|           |------|  H  |  J  |  K  | LShift/L | LCtrl/; |      -      |
   * |-------------+-------+--------+-----+-----+-----| Del  |           |Bspace|-----+-----+-----+----------+---------+-------------|
   * | LShift/CAPS |   Z   |    X   |  C  |  V  |  B  |      |           |      |  N  |  M  |  ,  |    .     |    /    | RShift/CAPS |
   * `-------------------------------------------------------'           `-----------------------------------------------------------'
   *        |      |       |        | Alt | Cmd |                                     |Left |Down |    Up    |  Right  |      |
   *        `-----------------------------------'                                     `---------------------------------------'
   *                                             ,-------------.       ,-------------.
   *                                             |     |       |       |       |     |
   *                                       ,-----|-----|-------|       |-------+-----+-----.
   *                                       |GUI/ |     |       |       |       |GUI/ |     |
   *                                       |Space|Enter|-------|       |-------|Enter|Space|
   *                                       |     |     |       |       |       |     |     |
   *                                       `-------------------'       `-------------------'
   */
  [EXP] = LAYOUT_ergodox_pretty(
      KC_ESC          , KC_1     , KC_2     , KC_3        , KC_4         , KC_5     , ______ , /*|*/ _______ , KC_6     , KC_7     , KC_8     , KC_9     , KC_0          , KC_EQUAL  ,
      ________        , KC_Q     , KC_W     , KC_E        , KC_R         , KC_T     , KC_TAB , /*|*/ KC_TAB  , KC_Y     , KC_U     , KC_I     , KC_O     , KC_P          , KC_LBRC   ,
      KC_QUOTE        , LC(KC_A) , LS(KC_S) , LT(SYM,KC_D), LT(NUM,KC_F) , KC_G     ,          /*|*/           KC_H     , KC_J     , KC_K     , RS(KC_L) , RC(KC_SCOLON) , KC_MINUS ,
      TD(TD_LSFTCAPS) , KC_Z     , KC_X     , KC_C        , KC_V         , KC_B     , KC_DEL , /*|*/ KC_BSPC , KC_N     , KC_M     , KC_COMMA , KC_DOT   , KC_SLASH      , TD(TD_RSFTCAPS) ,
      ________        , ____     , ____     , KC_LALT     , KC_LGUI      ,                     /*|*/ KC_LEFT , KC_DOWN  , KC_UP    , KC_RIGHT , ______   ,
                                                                           ________ , ______ , /*|*/ TO(BASE), ________ ,
                                                                                      ______ , /*|*/ _______ ,
                                                        LGUI_T(KC_SPACE) , KC_ENTER , ______ , /*|*/ _______ , KC_ENTER , GUI_T(KC_SPACE)
      ),

  /* Symbols
   *
   * Notes:
   * - Symbols on the top row mostly match a "normal" layout.
   * - since the base layer has the shift and symbol modifier/layer next to each
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

  if (caps_on)
    ergodox_right_led_1_on();


  uint8_t layer = biton32(layer_state);

  switch (layer) {
    default:
      break;
  }
};
