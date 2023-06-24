#include <string.h>

#define _QWERTY 0
#define _PLOVER 1
#define _MOUSE 2
#define _NAV 3

enum combo_events {
     RESET_COMBO,
     MOUSE_COMBO,
     MIDDLE_MOUSE_COMBO,
     NAV_COMBO,
     NAV_SHIFT_COMBO,
     QUERTY_COMBO,
     LWORD_COMBO,
     RWORD_COMBO,
};

const uint16_t PROGMEM reset_combo[] = {STN_ST1, STN_ST2, STN_ST3, STN_ST4, COMBO_END};
const uint16_t PROGMEM mouse_combo[] = {STN_ST1, STN_ST2, COMBO_END};
const uint16_t PROGMEM middle_mouse_combo[] = {KC_BTN1, KC_BTN2, COMBO_END};
const uint16_t PROGMEM nav_combo[] = {STN_S1, STN_TL, STN_PL, STN_HL, COMBO_END};
const uint16_t PROGMEM nav_shift_combo[] = {STN_S1, STN_KL, STN_WL, STN_RL, COMBO_END};
const uint16_t PROGMEM qwerty_combo[] = {STN_ST1, STN_ST3, COMBO_END};
const uint16_t PROGMEM lword_combo[] = {KC_LEFT, KC_DOWN, COMBO_END};
const uint16_t PROGMEM rword_combo[] = {KC_DOWN, KC_RIGHT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(reset_combo, RESET),
    COMBO(mouse_combo, MO(_MOUSE)),
    COMBO(middle_mouse_combo, KC_BTN3),
    COMBO(nav_combo, MO(_NAV)),
    COMBO(nav_shift_combo, LM(_NAV, MOD_LSFT)),
    COMBO(qwerty_combo, TO(_QWERTY)),
    COMBO(lword_combo, C(KC_LEFT)),
    COMBO(rword_combo, C(KC_RIGHT)),
};

/*
def chord(keys):
    chord = [0, 0, 0, 0, 0, 0]
    for key in keys:
        idx = key // 7
        bit = 1 << (6 - (key % 7))
        chord[idx] |= bit
    return chord

s1 = 7
s2 = 8
tl = 9
kl = 10
hl = 13
rl = 14
o = 16
e = 24
rr = 27
pr = 28
lr = 30
sr = 33

def print_chord_bytes(keys):
    print(", ".join([hex(k) for k in chord(keys)]))

print_chord_bytes([s1])
print_chord_bytes([s1, s2])
print_chord_bytes([s1, tl])
print_chord_bytes([s2, pr])
print_chord_bytes([tl, kl, lr, sr])
print_chord_bytes([s2, tl, hl, rl, o, e, rr])
*/

const uint8_t chord_s1[6] = {0x0, 0x40, 0x0, 0x0, 0x0, 0x0};
const uint8_t chord_s1s2[6] = {0x00, 0x60, 0x00, 0x00, 0x00, 0x00};
const uint8_t chord_s1tl[6] = {0x00, 0x50, 0x00, 0x00, 0x00, 0x00};
const uint8_t chord_tkls[6] = {0x0, 0x18, 0x0, 0x0, 0x12, 0x0};
const uint8_t chord_s2pr[6] = {0x0, 0x20, 0x0, 0x0, 0x40, 0x0};
const uint8_t chord_sthroer[6] = {0x0, 0x31, 0x50, 0x9, 0x0, 0x0};

bool send_steno_chord_user(steno_mode_t mode, uint8_t chord[6]) {
    if (memcmp(chord, chord_s1, 6) == 0) {
        memcpy(chord, chord_tkls, 6);
    } else if (memcmp(chord, chord_s1s2, 6) == 0) {
        memcpy(chord, chord_s2pr, 6);
    } else if (memcmp(chord, chord_s1tl, 6) == 0) {
        memcpy(chord, chord_sthroer, 6);
    }

    return true;
}