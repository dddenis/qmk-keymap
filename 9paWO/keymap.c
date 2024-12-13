#include QMK_KEYBOARD_H
#include "version.h"
#define MOON_LED_LEVEL LED_LEVEL
#define ML_SAFE_RANGE SAFE_RANGE

#define TMUX LT(0, KC_TAB)
#define TMUX_KEY C(KC_A)

enum custom_keycodes {
  SMTD_KEYCODES_BEGIN = SAFE_RANGE,

  // Left HMR
  CKC_A,
  CKC_S,
  CKC_D,
  CKC_F,

  // Left thump cluster
  CKC_SPC,

  // Right thump cluster
  CKC_BSPC,

  // Right HMR
  CKC_J,
  CKC_K,
  CKC_L,
  CKC_SCLN,

  SMTD_KEYCODES_END,

  RGB_SLD = ML_SAFE_RANGE,
};

#include "sm_td/sm_td.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_voyager(
    KC_GRAVE,       KC_1,           KC_2,           KC_3,           KC_4,           KC_5,                                           KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINUS,       
    TMUX,           KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSLS,        
    MT(MOD_LSFT, KC_ESCAPE),CKC_A,  CKC_S,          CKC_D,          CKC_F,          KC_G,                                           KC_H,           CKC_J,          CKC_K,          CKC_L,          CKC_SCLN,       KC_QUOTE,       
    KC_LEFT_GUI,    KC_Z,           MT(MOD_LCTL, KC_X),KC_C,           KC_V,           KC_B,                                           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       CW_TOGG,        
                                                    CKC_SPC,        KC_TAB,                                         KC_ENTER,       CKC_BSPC
  ),
  [1] = LAYOUT_voyager(
    KC_ESCAPE,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,                                          KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         
    KC_GRAVE,       KC_QUOTE,       KC_MINUS,       KC_PLUS,        KC_DQUO,        KC_DOT,                                         KC_AMPR,        KC_UNDS,        KC_LBRC,        KC_RBRC,        KC_AT,          KC_F12,         
    KC_TRANSPARENT, KC_EXLM,        KC_LABK,        KC_RABK,        KC_EQUAL,       KC_HASH,                                        KC_PIPE,        KC_NO,          KC_LPRN,        KC_RPRN,        KC_SCLN,        KC_BSPC,        
    KC_TRANSPARENT, KC_CIRC,        KC_SLASH,       KC_ASTR,        KC_BSLS,        KC_TRANSPARENT,                                 KC_CIRC,        KC_DLR,         KC_LCBR,        KC_RCBR,        KC_PERC,        KC_ENTER,       
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [2] = LAYOUT_voyager(
    RGB_TOG,        TOGGLE_LAYER_COLOR,RGB_MODE_FORWARD,RGB_SLD,        RGB_VAD,        RGB_VAI,                                        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, QK_BOOT,        
    KC_TRANSPARENT, KC_TRANSPARENT, KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_AUDIO_MUTE,  KC_TRANSPARENT,                                 KC_HOME,        KC_PAGE_UP,     KC_PGDN,        KC_END,         KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_LEFT_GUI,    KC_LEFT_ALT,    KC_LEFT_CTRL,   KC_LEFT_SHIFT,  KC_TRANSPARENT,                                 KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, CG_TOGG, 
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
};

const uint16_t PROGMEM combo0[] = { KC_M, KC_COMMA, COMBO_END};
const uint16_t PROGMEM combo1[] = { KC_COMMA, KC_DOT, COMBO_END};
const uint16_t PROGMEM combo2[] = { KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM combo3[] = { KC_Z, MT(MOD_LCTL, KC_X), COMBO_END};
const uint16_t PROGMEM combo4[] = { MT(MOD_LCTL, KC_X), KC_C, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo0, KC_LBRC),
    COMBO(combo1, KC_RBRC),
    COMBO(combo2, LCTL(KC_V)),
    COMBO(combo3, LCTL(KC_X)),
    COMBO(combo4, LCTL(KC_C)),
};

static bool tmux_enabled = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_smtd(keycode, record)) {
    return false;
  }

  switch (keycode) {
    case TMUX:
      if (record->tap.count == 0) {
        tmux_enabled = record->event.pressed;
        return false;
      }
      break;

    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
  }

  if (tmux_enabled && record->event.pressed) {
    tap_code16(TMUX_KEY);
  }

  return true;
}



// Custom

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LT(1, KC_SPACE):
      return 0;

    default:
      return QUICK_TAP_TERM;
  }
}

void on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
  switch (keycode) {
    // Left HMR
    SMTD_MT(CKC_A, KC_A, KC_LGUI, 1)
    SMTD_MT(CKC_S, KC_S, KC_LALT, 1)
    SMTD_MT(CKC_D, KC_D, KC_LCTL, 1)
    SMTD_MT(CKC_F, KC_F, KC_LSFT, 1)

    // Left thumb cluster
    SMTD_LT(CKC_SPC, KC_SPC, 1, 2)

    // Right thumb cluster
    SMTD_LT(CKC_BSPC, KC_BSPC, 2, 2)

    // Right HMR
    SMTD_MT(CKC_J, KC_J, KC_RSFT, 1)
    SMTD_MT(CKC_K, KC_K, KC_RCTL, 1)
    SMTD_MT(CKC_L, KC_L, KC_LALT, 1)
    SMTD_MT(CKC_SCLN, KC_SCLN, KC_RGUI, 1)
  }
}
