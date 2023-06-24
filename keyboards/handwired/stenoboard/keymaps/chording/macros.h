void fn_PARENS(const struct Chord* self) {
    switch(*self->state) {
    case ACTIVATED:
      tap_code16(S(KC_9));
      tap_code16(S(KC_0));
      tap_code(KC_LEFT);
      break;
    default:
      break;
    }
}

void fn_BRACKETS(const struct Chord* self) {
    switch(*self->state) {
    case ACTIVATED:
      tap_code(KC_LBRC);
      tap_code(KC_RBRC);
      tap_code(KC_LEFT);
      break;
    default:
      break;
    }
}

void fn_ANGLE_BRACKETS(const struct Chord* self) {
    switch(*self->state) {
    case ACTIVATED:
      tap_code16(S(KC_COMMA));
      tap_code16(S(KC_DOT));
      tap_code(KC_LEFT);
      break;
    default:
      break;
    }
}

void fn_BRACES(const struct Chord* self) {
    switch(*self->state) {
    case ACTIVATED:
      tap_code16(S(KC_LBRC));
      tap_code16(S(KC_RBRC));
      tap_code(KC_LEFT);
      break;
    default:
      break;
    }
}
