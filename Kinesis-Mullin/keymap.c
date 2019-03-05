#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum kinesis_layers {
  _COLEMAK,   // Colemak (default layer)
  _QWERTY,    // Qwerty
  _COLEMAKGM, // Colemak gaming/vanilla (limited dual-role keys with layer access)
  _QWERTYGM,  // QWERTY gaming/vanilla (limited dual-role keys with layer access)
  _NUMBERS,   //Numbers
  _SYMBOL,   // Symbol 
  _NAVIGATION,  // Navigation
  _NUMPAD,    // Numpad
  _ADJUST,    // Adjust layer (accessed via tri-layer feature)
  _ADJUST2    // Second Adjust layer (accessed outside of tri-layer feature)
};

enum kinesis_keycodes {
  COLEMAK = SAFE_RANGE,
  QWERTY,
  COLEMAKGM,
  QWERTYGM,
  NUMPAD  = TG(_NUMPAD),
  ADJUST  = MO(_ADJUST2),
  // SPCFN   = LT(_FUNCTION, KC_SPC),
  // BSPCFN  = LT(_FUNCTION2, KC_BSPC),
  // ENTNS   = LT(_NUMBERS, KC_ENT),
  // DELNS   = LT(_NUMBERS2, KC_DEL),
  CTLESC  = CTL_T(KC_ESC),
  ALTAPP  = ALT_T(KC_APP),
  NKROTG  = MAGIC_TOGGLE_NKRO,
  SHFZ    = SFT_T(KC_Z),
  SHFS    = SFT_T(KC_SLSH),
  OSL_SYM = OSL(_SYMBOL),
  OSL_NUM = OSL(_NUMBERS),
  STAB    = LSFT(KC_TAB),
  NAVIGATION = MO(_NAVIGATION),
  UNDO = LCTL(KC_Z),
  CUT = LCTL(KC_X),
  COPY = LCTL(KC_C),
  PASTE= LCTL(KC_V)
};

#define _______ KC_TRNS
#define XXXXXXX KC_NO

//Tap Dance Declarations
enum {
  ADJ = 0,
  LBCB,
  RBCB,
  EQPL,
  PLEQ,
  MNUN,
  SLAS,
  GVTL,
  PPLEQ,
  PMNUN,
  PSLPAS
};

void dance_LAYER_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
     layer_on(_ADJUST2);
     set_oneshot_layer(_ADJUST2, ONESHOT_START);
  }
}
void dance_LAYER_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
     layer_off(_ADJUST2);
     clear_oneshot_layer_state(ONESHOT_PRESSED);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
[ADJ]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_LAYER_finished, dance_LAYER_reset),  //  Double-tap to activate Adjust layer via oneshot layer 
[LBCB]   = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_LCBR),  // Left bracket on a single-tap, left brace on a double-tap
[RBCB]   = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_RCBR),  // Right bracket on a single-tap, right brace on a double-tap
[EQPL]   = ACTION_TAP_DANCE_DOUBLE(KC_EQL, KC_PLUS),   // Plus sign on a single-tap, equal sign on a double-tap
[PLEQ]   = ACTION_TAP_DANCE_DOUBLE(KC_PLUS, KC_EQL),   // Equal sign on a single-tap, plus sign on a double-tap
[MNUN]   = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_UNDS),  // Minus sign on a single-tap, underscore on a double-tap
[SLAS]   = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_ASTR),  // Slash in a single-tap, asterisk in a double-tap
[GVTL]   = ACTION_TAP_DANCE_DOUBLE(KC_GRV, KC_TILD),   // Grave on a single-tap, tilde on a double-tap
[PPLEQ]  = ACTION_TAP_DANCE_DOUBLE(KC_PPLS, KC_EQL),   // Numpad plus sign on a single-tap, equal sign on a double-tap
[PMNUN]  = ACTION_TAP_DANCE_DOUBLE(KC_PMNS, KC_UNDS),  // Numpad minus sign on a single-tap, underscore on a double-tap
[PSLPAS] = ACTION_TAP_DANCE_DOUBLE(KC_PSLS, KC_PAST)   // Numpad slash on a single-tap, numpad asterisk on a double-tap
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Colemak
  ,-----------------------------------------------------------------------------------------------------------.
  | ESC |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 | PScr| SLck| Paus|Numpd|Adjst|
  `-----------------------------------------------------------------------------------------------------------'
  ,-------------------------------------------.                   ,-------------------------------------------.
  |    =   |   1  |   2  |   3  |   4  |   5  |                   |   6  |   7  |   8  |   9  |   0  |   -    |
  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
  |   Tab  |   Q  |   W  |   F  |   P  |   G  |                   |   J  |   L  |   U  |   Y  |   ;  |   \    |
  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
  |Esc/Ctrl|   A  |   R  |   S  |   T  |   D  |                   |   H  |   N  |   E  |   I  |   O  |   '    |
  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
  |SC Shift|   Z  |   X  |   C  |   V  |   B  |                   |   K  |   M  |   ,  |   .  |   /  |SC Shift|
  `--------+------+------+------+------+------'                   `------+------+------+------+------+--------'
           |  Ins |   `  |   [  |   ]  |                                 | Left | Down |  Up  | Right|
	         `---------------------------'                                 `---------------------------'
	                          ,---------------.                   ,---------------.
	                          |Esc/Ctl| Hyper |                   |  RAlt |  RCtl |
	                  ,-------|-------|-------|                   |-------+-------+-------.
	                  |       |       |App/Alt|                   |  RGUI |       |       |
	                  |  NAV  | NUMBER|-------|                   |-------| SYMBOL| Space |
	                  |       |       |  Bspc |                   | Enter |       |       |
	                  `-----------------------'                   `-----------------------' 
*/
[_COLEMAK] = LAYOUT_pretty(
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, NUMPAD,  ADJUST,
  KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                                                          KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS,
  CTLESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                                                          KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_LSPO, SHFZ,    KC_X,    KC_C,    KC_V,    KC_B,                                                          KC_K,    KC_M,    KC_COMM, KC_DOT,  SHFS, KC_RSPC,
           KC_INS,  KC_GRV,  KC_LBRC, KC_CAPS,                                                                         KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
                                                        CTLESC,    ALL_T(KC_NO),        KC_RALT, KC_RCTL,
                                                                   ALTAPP,              KC_RGUI,
                                          NAVIGATION,   OSL_NUM,   KC_BSPC,             KC_ENT,  OSL_SYM, KC_SPC
),

/* QWERTY
  ,-----------------------------------------------------------------------------------------------------------.
  | ESC |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 | PScr| SLck| Paus|Numpd|Adjst|
  `-----------------------------------------------------------------------------------------------------------'
  ,-------------------------------------------.                   ,-------------------------------------------.
  |    =   |   1  |   2  |   3  |   4  |   5  |                   |   6  |   7  |   8  |   9  |   0  |   -    |
  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
  |   Tab  |   Q  |   W  |   E  |   R  |   T  |                   |   Y  |   U  |   I  |   O  |   P  |   \    |
  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
  |Esc/Ctrl|   A  |   S  |   D  |   F  |   G  |                   |   H  |   J  |   K  |   L  |   ;  |   '    |
  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
  |SC Shift|   Z  |   X  |   C  |   V  |   B  |                   |   N  |   M  |   ,  |   .  |   /  |SC Shift|
  `--------+------+------+------+------+------'                   `------+------+------+------+------+--------'
	         |  Ins |   `  |   [  |   ]  |                                 | Left | Down |  Up  | Right|
	         `---------------------------'                                 `---------------------------'
	                             ,---------------.                   ,---------------.
	                             |Esc/Ctl| Hyper |                   |  RAlt |  RCtl |
	                     ,-------|-------|-------|                   |-------+-------+-------.
	                     |       |       |App/Alt|                   |  RGUI |       |       |
	                     |  NAV  | NUMBER|-------|                   |-------| SYMBOL| Space |
	                     |       |       |  Bspc |                   | Enter |       |       |
	                     `-----------------------'                   `-----------------------' 
*/
[_QWERTY] = LAYOUT_pretty(
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, NUMPAD,  ADJUST,
  KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  CTLESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                                          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                                          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
           KC_INS,  KC_GRV,  KC_LBRC, KC_RBRC,                                                                         KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
                                                    CTLESC,   ALL_T(KC_NO),            KC_RALT, KC_RCTL,
                                                              ALTAPP,                  KC_RGUI,
                                        NAVIGATION, OSL_NUM,  KC_BSPC,                 KC_ENT,  OSL_SYM,KC_SPC
),

/* Number layer
   (Multiple characters: single-tap for first, double-tap for second)
  ,-----------------------------------------------------------------------------------------------------------.
  |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
  `-----------------------------------------------------------------------------------------------------------'
  ,-------------------------------------------.                   ,-------------------------------------------.
  |   F12  |  F1  |  F2  |  F3  |  F4  |  F5  |                   |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
  |        |   !  | STab |  Tab |   =  |  Del |                   |   -  |   7  |   8  |   9  |   *  |        |
  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
  |        | Ctrl |  Win | Shift|  Alt |   ^  |                   | BSPC |   4  |   5  |   6  |  ENT |        |
  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
  |        |   (  |   <  |   %  |   >  |   )  |                   |   +  |   1  |   2  |   3  |   /  |        |
  `--------+------+------+------+------+------'                  `------+------+------+------+------+--------'
	         |      |      |      |      |                                 |      |      |      |      |
	         `---------------------------'                                 `---------------------------'
	                          ,---------------.                   ,---------------.
	                          |       |       |                   |       |       |
	                  ,-------|-------|-------|                   |-------+-------+-------.
	                  |       |       |       |                   |       |       |       |
	                  |       |       |-------|                   |-------|       |       |
	                  |       |       |       |                   |       |       |       |
	                  `-----------------------'                   `-----------------------' 
*/
[_NUMBERS] = LAYOUT_pretty(
  _______, _______, _______, _______,  _______,  _______,  _______, _______, _______, _______, _______, _______, _______,  _______,  _______,  _______, _______, _______,
  KC_F12,  KC_F1,   KC_F2,   KC_F3,    KC_F4,    KC_F5,                                                          KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,  KC_F11,
  _______, KC_EXLM, STAB,    KC_TAB,   KC_EQL,   KC_DEL,                                                         KC_MINS,  KC_P7,    KC_P8,    KC_P9,   KC_ASTR, _______, 
  _______, KC_LCTL, KC_LSFT, KC_LGUI,  KC_LALT,  KC_CIRC,                                                        KC_BSPC,  KC_P4,    KC_P5,    KC_P6,   KC_ENT,  _______, 
  _______, KC_LPRN, KC_GT,   KC_PERC,  KC_LT,    KC_RPRN,                                                        KC_PLUS,  KC_P1,    KC_P2,    KC_P3,   KC_SLSH, _______,
           _______, _______, _______,  _______,                                                                            KC_P0,    KC_P0,    _______, _______, 
                                                           _______, _______,                   _______, _______,
                                                                    _______,                   _______,
                                                 _______,  _______, _______,                   _______, _______, _______
),

/* Navigation layer
  ,-----------------------------------------------------------------------------------------------------------.
  |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
  `-----------------------------------------------------------------------------------------------------------'
  ,-------------------------------------------.                   ,-------------------------------------------.
  |   F12  |  F1  |  F2  |  F3  |  F4  |  F5  |                   |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
  |        | Enter| STab | Tab  |  Esc | Del  |                   | STab | PgUp |  Up  | PgDn |  Win |        |
  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
  |        | Ctrl | Shft |  Win |  Alt |  BS  |                   |  BS  | Left | Down | Right|  Ent |        |
  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
  |        | Undo |  Cut | Copy | Paste| Sel.A|                   |  Tab | Home |  Del | End  |Ctrl+Y|        |
  `--------+------+------+------+------+------'                   `------+------+------+------+------+--------'
	         |      |      |      |      |                                 |      |      |      |      |
	         `---------------------------'                                 `---------------------------'
	                            ,---------------.                   ,---------------.
	                            |       |       |                   |       |       |
	                    ,-------|-------|-------|                   |-------+-------+-------.
	                    |       |       |       |                   |       |       |       |
	                    |       |       |-------|                   |-------|       |       |
	                    |       |       |       |                   |       |       |       |
	                    `-----------------------'                   `-----------------------' 
*/
[_NAVIGATION] = LAYOUT_pretty(
  _______, _______, _______, _______, _______,  _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,    _______,
  KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,                                                             KC_F6,   KC_F7,   KC_F8,   KC_F9,      KC_F10,     KC_F11,
  _______, KC_ENT,  STAB,    KC_TAB,  KC_ESC,   KC_DEL,                                                            STAB,    KC_PGUP, KC_UP,   KC_PGDN,    KC_LGUI,    _______,
  _______, KC_LCTL, KC_LSFT, KC_LGUI, KC_LALT,  KC_BSPC,                                                           KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT,    KC_ENT,     _______,
  _______, UNDO,    CUT,     COPY,    PASTE   , LCTL(KC_A),                                                        KC_TAB,  KC_HOME, KC_DEL,  KC_END,     LCTL(KC_Y), _______,
           _______,    _______,    _______,    _______,                                                                     _______, _______, _______,    _______,
                                                                        _______, _______,                   _______, _______,
                                                                                 _______,                   _______,
                                                           _______,     _______, _______,                   _______, KC_ENT, _______
),

/* Symbol layer
   (Left side duplicates layout from the Numbers layer, just with numpad output; right side layout close to PC numpad layout)
  ,-----------------------------------------------------------------------------------------------------------.
  |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
  `-----------------------------------------------------------------------------------------------------------'
  ,-------------------------------------------.                   ,-------------------------------------------.
  |        |      |      |      |      |      |                   |      |      |      |      |      |        |
  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
  |        |   :  |   -  |   "  |   +  |   |  |                   |   \  |   )  |   }  |   ]  |   >  |        |
  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
  |        |   ;  |   _  |   '  |   =  |   ?  |                   |   /  |   (  |   {  |   [  |   <  |        |
  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
  |        |   !  |   @  |   #  |   $  |   %  |                   |   ^  |   &  |   *  |   ~  |   `  |        |
  `--------+------+------+------+------+------'                   `------+------+------+------+------+--------'
	         |      |      |      |      |                                 |      |      |      |      |
	         `---------------------------'                                 `---------------------------'
	                          ,---------------.                   ,---------------.
	                          |       |       |                   |       |       |
	                  ,-------|-------|-------|                   |-------+-------+-------.
	                  |       |       |       |                   |       |       |       |
	                  |       |       |-------|                   |-------|       |       |
	                  |       |       |       |                   |       |       |       |
	                  `-----------------------'                   `-----------------------' 
*/
[_SYMBOL] = LAYOUT_pretty(
  _______, _______, _______, _______,  _______,   _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______,  _______,   _______,                                                         _______, _______, _______, _______, _______, _______,
  _______, KC_COLN, KC_UNDS, KC_DQT,   KC_PLUS,   KC_PIPE,                                                         KC_BSLS, KC_RPRN, KC_RCBR, KC_RBRC, KC_GT, _______,
  _______, KC_SCLN, KC_MINS, KC_QUOT,  KC_EQL,    KC_QUES,                                                         KC_SLSH, KC_LPRN, KC_LCBR, KC_LBRC, KC_LT,  _______,
  _______, KC_EXLM, KC_AT,   KC_HASH,  KC_DLR,    KC_PERC,                                                         KC_CIRC, KC_AMPR, KC_ASTR, KC_TILD, KC_GRV, _______,
           _______, _______, _______,  _______,                                                                            _______, _______, _______, _______,
                                                               _______, _______,                   _______, _______,
                                                                        _______,                   _______,
                                                    _______,   _______, _______,                   _______, _______, _______
),

/* Colemak gaming/vanilla
   (Limited access to Function or Numbers layers; mainly used for gaming; double-tap and hold TD(ADJ) above LAlt to access Adjust layer)
  ,-----------------------------------------------------------------------------------------------------------.
  | ESC |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 | PScr| SLck| Paus|Numpd|Adjst|
  `-----------------------------------------------------------------------------------------------------------'
  ,-------------------------------------------.                   ,-------------------------------------------.
  |    =   |   1  |   2  |   3  |   4  |   5  |                   |   6  |   7  |   8  |   9  |   0  |   -    |
  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
  |   Tab  |   Q  |   W  |   F  |   P  |   G  |                   |   J  |   L  |   U  |   Y  |   ;  |   \    |
  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
  |  Ctrl  |   A  |   R  |   S  |   T  |   D  |                   |   H  |   N  |   E  |   I  |   O  |   '    |
  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
  |  Shift |   Z  |   X  |   C  |   V  |   B  |                   |   K  |   M  |   ,  |   .  |   /  |  Shift |
  `--------+------+------+------+------+------'                   `------+------+------+------+------+--------'
	       |  Ins |   `  |   [  |   ]  |                                 | Left | Down |  Up  | Right|
	       `---------------------------'                                 `---------------------------'
	                          ,---------------.                   ,---------------.
	                          |Esc/Ctl|TD(ADJ)|                   |  RAlt |  RCtl |
	                  ,-------|-------|-------|                   |-------+-------+-------.
	                  |       |       |  LAlt |                   |  RGUI |       |       |
	                  | Space | Enter |-------|                   |-------| Delete|  Bspc |
	                  |       |       |Bspc/FN|                   | Ent/NS|       |       |
	                  `-----------------------'                   `-----------------------' 
*/
[_COLEMAKGM] = LAYOUT_pretty(
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, NUMPAD,  ADJUST,
  KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                                                          KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS,
  KC_LCTL, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                                                          KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                                          KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
           KC_INS,  KC_GRV,  KC_LBRC, KC_RBRC,                                                                         KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
                                                        CTLESC,  TD(ADJ),                   KC_RALT, KC_RCTL,
                                                                 KC_LALT,                   KC_RGUI,
                                               KC_SPC,  KC_ENT,  KC_BSPC,                   KC_ENT,   KC_DEL,  KC_BSPC
),

/* QWERTY gaming/vanilla
   (Limited access to Function or Numbers layers; mainly used for gaming; double-tap and hold TD(ADJ) above LAlt to access Adjust layer)
  ,-----------------------------------------------------------------------------------------------------------.
  | ESC |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 | PScr| SLck| Paus|Numpd|Adjst|
  `-----------------------------------------------------------------------------------------------------------'
  ,-------------------------------------------.                   ,-------------------------------------------.
  |    =   |   1  |   2  |   3  |   4  |   5  |                   |   6  |   7  |   8  |   9  |   0  |   -    |
  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
  |   Tab  |   Q  |   W  |   E  |   R  |   T  |                   |   Y  |   U  |   I  |   O  |   P  |   \    |
  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
  |  Ctrl  |   A  |   S  |   D  |   F  |   G  |                   |   H  |   J  |   K  |   L  |   ;  |   '    |
  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
  |  Shift |   Z  |   X  |   C  |   V  |   B  |                   |   N  |   M  |   ,  |   .  |   /  |  Shift |
  `--------+------+------+------+------+------'                   `------+------+------+------+------+--------'
	       |  Ins |   `  |   [  |   ]  |                                 | Left | Down |  Up  | Right|
	       `---------------------------'                                 `---------------------------'
	                          ,---------------.                   ,---------------.
	                          |Esc/Ctl|TD(ADJ)|                   |  RAlt |  RCtl |
	                  ,-------|-------|-------|                   |-------+-------+-------.
	                  |       |       |  LAlt |                   |  RGUI |       |       |
	                  | Space | Enter |-------|                   |-------| Delete|  Bspc |
	                  |       |       |Bspc/FN|                   | Ent/NS|       |       |
	                  `-----------------------'                   `-----------------------' 
*/
[_QWERTYGM] = LAYOUT_pretty(
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, NUMPAD,  ADJUST,
  KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                                          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                                          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
           KC_INS,  KC_GRV,  KC_LBRC, KC_RBRC,                                                                         KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
                                                        CTLESC,  TD(ADJ),                   KC_RALT, KC_RCTL,
                                                                 KC_LALT,                   KC_RGUI,
                                               KC_SPC,  KC_ENT,  KC_BSPC,                    KC_ENT,   KC_DEL,  KC_BSPC
),

/* Adjust layer
   (Enter/Number + Delete/Number2 under non-gaming/vanilla layers or press & hold Adjust key on function row; Numpad is a toggle)
  ,-----------------------------------------------------------------------------------------------------------.
  |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
  `-----------------------------------------------------------------------------------------------------------'
  ,-------------------------------------------.                   ,-------------------------------------------.
  |        |Colmak|Qwerty|      |ClmkGM| QWGM |                   |Numpad|      |      |      |      | RESET  |
  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
  |        |      |      |      |      |      |                   |      |      |      |      |      |        |
  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
  |        |      |      |      |      |      |                   |      | NKRO |      |      |      |        |
  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
  |        |      |      |      |      |      |                   |      |      |      |      |      |        |
  `--------+------+------+------+------+------'                   `------+------+------+------+------+--------'
	       |      |      |      |      |                                 |      |      |      |      |
	       `---------------------------'                                 `---------------------------'
	                          ,---------------.                   ,---------------.
	                          |       |       |                   |       |       |
	                  ,-------|-------|-------|                   |-------+-------+-------.
	                  |       |       |       |                   |       |       |       |
	                  |       |       |-------|                   |-------|       |       |
	                  |       |       |       |                   |       |       |       |
	                  `-----------------------'                   `-----------------------'  
*/
[_ADJUST] = LAYOUT_pretty(
  _______, _______, _______, _______, _______,   _______,  _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, COLEMAK, QWERTY,  _______, COLEMAKGM, QWERTYGM,                                                        NUMPAD,  _______, _______, _______, _______, RESET,
  _______, _______, _______, _______, _______,   _______,                                                         _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______,   _______,                                                         _______, NKROTG,  _______, _______, _______, _______,
  _______, _______, _______, _______, _______,   _______,                                                         _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______,                                                                             _______, _______, _______, _______, 
                                                           _______, _______,                    _______, _______,
                                                                    _______,                    _______,
                                                 _______,  _______, _______,                    _______, _______, _______
),

[_ADJUST2] = LAYOUT_pretty(
  _______, _______, _______, _______, _______,   _______,  _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, COLEMAK, QWERTY,  _______, COLEMAKGM, QWERTYGM,                                                        NUMPAD,  _______, _______, _______, _______, RESET,
  _______, _______, _______, _______, _______,   _______,                                                         _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______,   _______,                                                         _______, NKROTG,  _______, _______, _______, _______,
  _______, _______, _______, _______, _______,   _______,                                                         _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______,                                                                             _______, _______, _______, _______, 
                                                           _______, _______,                    _______, _______,
                                                                    _______,                    _______,
                                                 _______,  _______, _______,                    _______, _______, _______
)

};

// uint32_t layer_state_set_user(uint32_t state) {
//   return update_tri_layer_state(state, _NUMBERS, _SYMBOL, _NAVIGATION);
// }

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
	case COLEMAK:
      if (record->event.pressed) {
        default_layer_set(1UL << _COLEMAK);
//        persistent_default_layer_set(1UL << _COLEMAK);
        layer_off ( _QWERTY);
        layer_off ( _NUMBERS);
        layer_off ( _SYMBOL);
        layer_off ( _NAVIGATION);
        layer_off ( _NUMPAD);
        layer_off ( _COLEMAKGM);
        layer_off ( _QWERTYGM);
        layer_off ( _ADJUST);
        layer_off ( _ADJUST2);
	  }
      return false;
      break;
    case QWERTY:
      if (record->event.pressed) {
        default_layer_set(1UL << _QWERTY);
//        persistent_default_layer_set(1UL << _QWERTY);
        layer_off ( _COLEMAK);
        layer_off ( _NUMBERS);
        layer_off ( _SYMBOL);
        layer_off ( _NAVIGATION);
        layer_off ( _NUMPAD);
        layer_off ( _COLEMAKGM);
        layer_off ( _QWERTYGM);
        layer_off ( _ADJUST);
        layer_off ( _ADJUST2);
      }
      return false;
      break;
    case COLEMAKGM:
      if (record->event.pressed) {
        default_layer_set(1UL << _COLEMAKGM);
        layer_off ( _QWERTY);
        layer_off ( _COLEMAK);
        layer_off ( _NUMBERS);
        layer_off ( _SYMBOL);
        layer_off ( _NAVIGATION);
        layer_off ( _NUMPAD);
        layer_off ( _COLEMAKGM);
        layer_off ( _QWERTYGM);
        layer_off ( _ADJUST);
        layer_off ( _ADJUST2);
	  }
      return false;
      break;
    case QWERTYGM:
      if (record->event.pressed) {
        default_layer_set(1UL << _QWERTYGM);
        layer_off ( _QWERTY);
        layer_off ( _COLEMAK);
        layer_off ( _NUMBERS);
        layer_off ( _SYMBOL);
        layer_off ( _NAVIGATION);
        layer_off ( _NUMPAD);
        layer_off ( _COLEMAKGM);
        layer_off ( _QWERTYGM);
        layer_off ( _ADJUST);
        layer_off ( _ADJUST2);
	  }
      return false;
      break;
  }
  return true;
}