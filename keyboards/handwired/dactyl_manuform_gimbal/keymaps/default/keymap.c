#include QMK_KEYBOARD_H

#include "DRV2605L.h"

extern uint16_t joystick_x_raw;
extern uint16_t joystick_y_raw;

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _NUM,
    _NAV,
    _SYMBOL,
    _MOUSE_LEFT,
    _MOUSE_RIGHT,
    _PLOVER,
    _CONFIG,
    _BLANK
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL,
    PL_1, PL_2, PL_3, PL_4, PL_5, PL_6, PL_7, PL_8, PL_9, PL_0,
    PL_S1, PL_T1, PL_K, PL_P1, PL_W, PL_H, PL_R1, PL_A, PL_O, PL_STAR,
    PL_E, PL_U, PL_F, PL_R2, PL_P2, PL_B, PL_L, PL_G, PL_T2, PL_S2, PL_D, PL_Z,
    PL_LCTL, PL_LALT, PL_LGUI,
    PL_RCTL, PL_RALT, PL_RGUI,
    MS_SCR,
    PARENS, BRACES, BRACKETS
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT
    (
     KC_Q,               LT(0, KC_W), KC_E,        KC_R,        KC_T,                 /**/ LT(0, KC_Y),       KC_U,                KC_I,    KC_O,    KC_P,    KC_BSPC,
     MT(MOD_LSFT, KC_A), KC_S,        KC_D,        KC_F,        KC_G,                 /**/ KC_H,              KC_J,                KC_K,    KC_L,    KC_SCLN, KC_QUOT,
     MT(MOD_LCTL, KC_Z), LT(0, KC_X), LT(0, KC_C), LT(0, KC_V), KC_B,                 /**/ KC_N,              KC_M,                KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
     /**/                              MT(MOD_LCTL, KC_TAB), MT(MOD_LSFT, KC_SPC),      MT(MOD_RSFT, KC_SPC), MT(MOD_LCTL, KC_ENT),
     /**/                              MO(_NAV),             LT(_NUM, KC_SPC),          LT(_NUM, KC_SPC),     MO(_NAV),
                                       KC_LALT,              KC_LGUI,                   KC_RGUI,              KC_RALT
     ),
    [_NUM] = LAYOUT(
     KC_1,   KC_2,   KC_3,   KC_4,    KC_5,   /**/ KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_NO,
     KC_F1,  KC_F2,  KC_F3,  KC_F4,   KC_F5,  /**/ KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_NO,
     KC_F11, KC_F12, KC_F13, KC_F14,  KC_F15, /**/ KC_F16,  KC_F17,  KC_F18,  KC_F11,  KC_F12,  KC_NO,
                             KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,
                             KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,
                             KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS
    ),
    [_NAV] = LAYOUT(
     KC_ESC,  KC_NO,   KC_NO,   KC_NO,   KC_ENT,  /**/ KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_PSCR, KC_DEL,
     KC_DEL,  KC_HOME, KC_UP,   KC_END,  KC_PGUP, /**/ KC_PGUP, KC_HOME, KC_UP  , KC_END,  KC_HOME, KC_PGUP,
     KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, /**/ KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  KC_PGDN,
     /**/                       KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS,
     /**/                       KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS,
     /**/                       KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS
    ),
    [_SYMBOL] = LAYOUT(
     KC_GRV,  KC_NO, KC_NO, KC_NO, KC_NO,     /**/ S(KC_9),    S(KC_0),    KC_NO,      KC_NO,     KC_NO,   KC_BSPC,
     KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,     /**/ S(KC_LBRC), S(KC_RBRC), S(KC_MINS), S(KC_EQL), KC_NO  , KC_NO,
     KC_NUBS, KC_NO, KC_NO, KC_NO, KC_NO,     /**/ KC_LBRC,    KC_RBRC,    KC_MINS,    KC_EQL,    KC_NUHS, KC_NO,
                            KC_TRNS, KC_TRNS,      KC_TRNS,    KC_TRNS,
                            KC_TRNS, KC_TRNS,      KC_TRNS,    KC_TRNS,
                            KC_TRNS, KC_TRNS,      KC_TRNS,    KC_TRNS
		       ),
    [_MOUSE_LEFT] = LAYOUT(
     KC_NO, KC_WH_U, MS_SCR,  KC_BTN2, KC_BTN1, /**/ KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     KC_NO, KC_WH_D, KC_MS_U, KC_BTN3, KC_BTN1, /**/ KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN2, /**/ KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                              KC_TRNS, KC_LSFT,      KC_TRNS, KC_TRNS,
                              KC_LCTL, KC_TRNS,      KC_TRNS, KC_TRNS,
                              KC_LALT, KC_TRNS,      KC_TRNS, KC_TRNS
    ),
    [_MOUSE_RIGHT] = LAYOUT(
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, /**/ KC_BTN1, KC_BTN2, KC_NO,   KC_WH_U,   KC_NO,   KC_NO,
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, /**/ KC_BTN1, KC_BTN3, KC_MS_U, KC_WH_D,   KC_NO,   KC_NO,
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, /**/ KC_BTN2, KC_MS_L, KC_MS_D, KC_MS_R,   KC_NO,   KC_NO,
                                KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS,
                                KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS,
                                KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS
    ),
    [_PLOVER] = LAYOUT(
     PL_1,  PL_2,  PL_3,  PL_4,    PL_5,    /**/ KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_NO,
     PL_S1, PL_T1, PL_P1, PL_H,    PL_STAR, /**/ PL_STAR, PL_F,    PL_P2,   PL_L,    PL_T2,   PL_D,
     PL_S1, PL_K,  PL_W,  PL_R1,   PL_STAR, /**/ PL_STAR, PL_R2,   PL_B,    PL_G,    PL_S2,   PL_Z,
                          PL_A,    PL_O,         PL_E,    PL_U,
                          PL_LCTL, KC_NO,        KC_NO,   PL_RCTL,
                          PL_LALT, PL_LGUI,      PL_RGUI, PL_RALT
    ),
    [_CONFIG] = LAYOUT(
     TG(_CONFIG), KC_NO, KC_NO, KC_NO, RGB_VAI, /**/ KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
     KC_NO,       KC_NO, KC_NO, KC_NO, RGB_VAD, /**/ KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
     KC_NO,       KC_NO, KC_NO, KC_NO, RGB_MOD, /**/ KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                KC_NO, KC_LSFT,      KC_NO,  KC_NO,
                                KC_NO, KC_NO,        KC_NO,  KC_NO,
                                KC_NO, KC_NO,        KC_NO,  KC_NO
    ),
    [_BLANK] = LAYOUT(
     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, /**/ KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, /**/ KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, /**/ KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                          KC_NO, KC_NO,      KC_NO,  KC_NO,
                          KC_NO, KC_NO,      KC_NO,  KC_NO,
                          KC_NO, KC_NO,      KC_NO,  KC_NO
    )
};

const uint16_t PROGMEM combo_config[] = {KC_W, KC_S, KC_E, KC_D, KC_R, KC_F, KC_T, KC_G, COMBO_END};
const uint16_t PROGMEM combo_symbol_left[] = {KC_LGUI, KC_LALT, COMBO_END};
const uint16_t PROGMEM combo_symbol_right[] = {KC_RGUI, KC_RALT, COMBO_END};
const uint16_t PROGMEM combo_parens[] = {S(KC_9), S(KC_0), COMBO_END};
const uint16_t PROGMEM combo_brackets[] = {KC_LBRC, KC_RBRC, COMBO_END};
const uint16_t PROGMEM combo_braces[] = {S(KC_LBRC), S(KC_RBRC), COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
				   COMBO(combo_config, TG(_CONFIG)),
				   COMBO(combo_symbol_left, MO(_SYMBOL)),
				   COMBO(combo_symbol_right, MO(_SYMBOL)),
				   COMBO(combo_parens, PARENS),
				   COMBO(combo_braces, BRACES),
				   COMBO(combo_brackets, BRACKETS)
};

const rgblight_segment_t PROGMEM mouse_light_layer[] =
  RGBLIGHT_LAYER_SEGMENTS(
			  {0, 2, 0, 255, 128},
			  {8, 2, 0, 255, 128}
			  );

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(mouse_light_layer);

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case MT(MOD_LSFT, KC_A):
  case MT(MOD_LCTL, KC_Z):
    return 200;
  default:
    return TAPPING_TERM;
    }
}

bool get_haptic_enabled_key(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case QK_MOD_TAP ... QK_MOD_TAP_MAX:
    if (record->tap.count == 0) return true;
    break;
  }

  return false;
}
  
    static void hold_haptic(void) {
      DRV_pulse(6); // Sharp click - 30%.
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case LT(0, KC_X):
    if (record->tap.count && record->event.pressed) {
      return true; // Normal processing of tap keycode
    } else if (record->event.pressed) {
      tap_code16(C(KC_X)); // Intercept hold function to send Ctrl-x.
      hold_haptic();
      return false;
    }
    return true;
  case LT(0, KC_C):
    if (record->tap.count && record->event.pressed) {
      return true; // Normal processing of tap keycode
    } else if (record->event.pressed) {
      tap_code16(C(KC_C)); // Intercept hold function to send Ctrl-c.
      hold_haptic();
      return false;
    }
    return true;
  case LT(0, KC_V):
    if (record->tap.count && record->event.pressed) {
      return true; // Normal processing of tap keycode
    } else if (record->event.pressed) {
      tap_code16(C(KC_V)); // Intercept hold function to send Ctrl-v.
      hold_haptic();
      return false;
    }
    return true;
  case LT(0, KC_W):
    if (record->tap.count && record->event.pressed) {
      return true; // Normal processing of tap keycode
    } else if (record->event.pressed) {
      tap_code16(A(KC_W)); // Intercept hold function to send Alt-w.
      hold_haptic();
      return false;
    }
    return true;
  case LT(0, KC_Y):
    if (record->tap.count && record->event.pressed) {
      return true; // Normal processing of tap keycode
    } else if (record->event.pressed) {
      tap_code16(C(KC_Y)); // Intercept hold function to send Ctrl-y.
      hold_haptic();
      return false;
    }
    return true;
  case PARENS:
    if (record->event.pressed) {
      tap_code16(S(KC_9));
      tap_code16(S(KC_0));
      tap_code(KC_LEFT);
    }
    return false;
  case BRACKETS:
    if (record->event.pressed) {
      tap_code(KC_LBRC);
      tap_code(KC_RBRC);
      tap_code(KC_LEFT);
    }
    return false;
  case BRACES:
    if (record->event.pressed) {
      tap_code16(S(KC_LBRC));
      tap_code16(S(KC_RBRC));
      tap_code(KC_LEFT);
    }
    return false;
  case QMKBEST:
    if (record->event.pressed) {
      // when keycode QMKBEST is pressed
      SEND_STRING("QMK is the best thing ever!");
    } else {
      // when keycode QMKBEST is released
    }
    break;
  case QMKURL:
    if (record->event.pressed) {
      // when keycode QMKURL is pressed
      SEND_STRING("https://qmk.fm/\n");
    } else {
      // when keycode QMKURL is released
    }
    break;
  }
  return true;
}

void enable_mouse_layer_left(void) {
  if (IS_LAYER_OFF(_MOUSE_LEFT)) {
    layer_on(_MOUSE_LEFT);
  }
}

void disable_mouse_layer_left(void) {
  if (IS_LAYER_ON(_MOUSE_LEFT)) {
    layer_off(_MOUSE_LEFT);
  }
}

void enable_mouse_layer_right(void) {
  if (IS_LAYER_OFF(_MOUSE_RIGHT)) {
    layer_on(_MOUSE_RIGHT);
  }
}

void disable_mouse_layer_right(void) {
  if (IS_LAYER_ON(_MOUSE_RIGHT)) {
    layer_off(_MOUSE_RIGHT);
  }
}

void oled_task_user(void) {
  oled_set_cursor(0, 0);
  
  oled_write_P(PSTR("Layer: "), false);
    
  switch (get_highest_layer(layer_state)) {
  case _BASE:
    oled_write_P(PSTR("QWERTY    \n"), false);
    break;
  case _NUM:
    oled_write_P(PSTR("Numbers   \n"), false);
    break;
  case _NAV:
    oled_write_P(PSTR("Navigation\n"), false);
    break;
  case _SYMBOL:
    oled_write_P(PSTR("Symbol    \n"), false);
    break;
  case _MOUSE_LEFT:
    oled_write_P(PSTR("Mouse (L) \n"), false);
    break;
  case _MOUSE_RIGHT:
    oled_write_P(PSTR("Mouse (R) \n"), false);
    break;
  case _PLOVER:
    oled_write_P(PSTR("Plover    \n"), false);
    break;
  case _CONFIG:
    oled_write_P(PSTR("Config    \n"), false);
    break;
  default:
    // Or use the write_ln shortcut over adding '\n' to the end of your string
    oled_write_P(PSTR("Undefined \n"), false);
  }

  // Host Keyboard LED Status
  led_t led_state = host_keyboard_led_state();
  oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
  oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
  oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
  oled_write_P("\n", false);

  if (false) {
    char msg[256];
    sprintf(msg, "JS: %04d %04d", joystick_x_raw, joystick_y_raw);
    oled_write(msg, false);
  }
}

static bool layer_was_base = true;

layer_state_t layer_state_set_user(layer_state_t state) {
  rgblight_set_layer_state(0, layer_state_cmp(state, _MOUSE_LEFT));
  switch(biton32(state)) {
  case _BASE:
    if (!layer_was_base) {
      DRV_pulse(30); // Short double-click strong 4 - 30%.
      layer_was_base = true;
    }
    break;
  case _NUM:
  case _SYMBOL:
    //layer_was_base = false;
    DRV_pulse(6); // Sharp click - 30%.
    break;
  case _MOUSE_LEFT:
  case _MOUSE_RIGHT:
    layer_was_base = false;
    DRV_pulse(9); // Soft bump - 30%
    break;
  }
  
  return state;
}

void keyboard_post_init_user(void) {
  rgblight_layers = my_rgb_layers;
}
