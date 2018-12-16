#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define COLEMAK 0
#define NUM 1
#define SYM 2
#define NAV 3
#define FUNC 4

// Fillers to make layering more clear
#define ________ KC_TRNS
#define XXXXXXX KC_NO

#define KC_STab LSFT(KC_TAB)

//Custom control + key combos
#define KC_UNDO LCTL_T(KC_Z)
#define KC_CUT LCTL_T(KC_X)
#define KC_COPY LCTL_T(KC_C)
#define KC_PASTE LCTL_T(KC_V)
#define KC_ALL LCTL_T(KC_A)
#define KC_REDO LCTL_T(KC_Y)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[COLEMAK] = LAYOUT_ortho_4x12_KC(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┬────────┐
    |   Q    ,    W   ,    F   ,    P   ,   G    ,  TAB   ,                         |  BSLS  ,    J   ,    L   ,    U   ,    Y   ,  SCLN  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
    |   A    ,    R   ,    S   ,    T   ,   D    ,  ESC   ,                         |  QUOT  ,    H   ,    N   ,    E   ,    I   ,    O   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
    |   Z    ,    X   ,    C   ,    V   ,   B    ,  LSFT  ,                         |  RSFT  ,    K   ,    M   ,  COMM  ,   DOT  ,  SLSH  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
    |  LCLT  ,  LALT  ,  LGUI  ,  LSFT  ,   SPC  ,   DEL  ,                         |  ENT   ,  BSPC  ,   NAV  ,  RGUI  ,  RALT  ,  RCLT      
  //└────────┴────────┴────────┴────────┴────────┴────────┘                         └────────┴────────┴────────┴────────┴────────┴────────┘
),
[NUM] = LAYOUT_ortho_4x12_KC(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┬────────┐
    |  EXLM  ,  STab  ,   TAB  ,   EQL  ,   DEL  ,________,                         |________,  MINS  ,    7   ,    8   ,    9   ,  ASTR  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
    |  LCLT  ,  LGUI  ,  LSFT  ,  LALT  ,  AMPR  ,________,                         |________,  BSPC  ,    4   ,    5   ,    6   ,  ENT   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
    |  LBRC  ,   LT   ,  PERC  ,   GT   ,  RBRC  ,________,                         |________,  PLUS  ,    1   ,    2   ,    3   ,  SLSH  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
    |________,________,________,  LSFT  ,   SPC  ,   DEL  ,                         |  ENT   ,  BSPC  ,    0   ,   DOT  ,________,________     
  //└────────┴────────┴────────┴────────┴────────┴────────┘                         └────────┴────────┴────────┴────────┴────────┴────────┘
),

[NAV] = LAYOUT_ortho_4x12_KC(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┬────────┐
    |  ENT   ,  STab  ,  TAB   ,  ESC   ,  DEL   ,________,                         |________,  STab  ,  PGUP  ,   UP   ,  PGDN  ,  SCLN  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
    |  LCLT  ,  LGUI  ,  LSFT  ,  LALT  ,  BSPC  ,________,                         |________,  BSPC  ,  LEFT  ,  DOWN  ,  RGHT  ,  ENT   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
    |  UNDO  ,  CUT   ,  COPY  ,  PASTE ,  ALL   ,________,                         |________,  TAB   ,  HOME  ,   DEL  ,  END   ,  SHFT  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
    |________,________,________,  LSFT  ,   SPC  ,   DEL  ,                         |  ENT   ,  BSPC  ,  NAV   ,________,________,________     
  //└────────┴────────┴────────┴────────┴────────┴────────┘                         └────────┴────────┴────────┴────────┴────────┴────────┘
),

[SYM] = LAYOUT_ortho_4x12_KC(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┬────────┐
    |  COLN  ,  UNDS  ,  DQT   ,  PLUS  ,  PIPE  ,________,                         |________,  BSLS  ,  RPRN  ,  RCBR  ,  RBRC  ,   GT   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
    |  SCLN  ,  MINS  ,  QUOT  ,  EQL   ,  AMPR  ,________,                         |________,  SLSH  ,  LPRN  ,  LCBR  ,  LBRC  ,   LT   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
    |  EXLM  ,  QUES  ,  AT    ,  DLR   ,  ASTR  ,________,                         |________,  HASH  ,  CIRC  ,  PERC  ,  TILD  ,  GRV   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
    |________,________,________,  LSFT  ,   SPC  ,   DEL  ,                         |  ENT   ,  BSPC  ,  NAV   ,________,________,________     
  //└────────┴────────┴────────┴────────┴────────┴────────┘                         └────────┴────────┴────────┴────────┴────────┴────────┘
),

[FUNC] = LAYOUT_ortho_4x12_KC(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┬────────┐
    |  COLN  ,  UNDS  ,  DQT   ,  PLUS  ,  PIPE  ,________,                         |________,  BSLS  ,  RPRN  ,  RCBR  ,  RBRC  ,   GT   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
    |  SCLN  ,  MINS  ,  QUOT  ,  EQL   ,  AMPR  ,________,                         |________,  SLSH  ,  LPRN  ,  LCBR  ,  LBRC  ,   LT   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
    |  EXLM  ,  QUES  ,  AT    ,  DLR   ,  ASTR  ,________,                         |________,  HASH  ,  CIRC  ,  PERC  ,  TILD  ,  GRV   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┤
    |________,________,________,  LSFT  ,   SPC  ,   DEL  ,                         |  ENT   ,  BSPC  ,  NAV   ,________,________,________     
  //└────────┴────────┴────────┴────────┴────────┴────────┘                         └────────┴────────┴────────┴────────┴────────┴────────┘
),



};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}