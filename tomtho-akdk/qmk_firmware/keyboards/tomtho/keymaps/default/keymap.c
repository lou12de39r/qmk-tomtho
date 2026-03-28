/* SPDX-License-Identifier: GPL-2.0-or-later */
#include QMK_KEYBOARD_H
#include "process_tap_dance.h"
#include "quantum/keymap_extras/keymap_japanese.h"
#include "mousekey.h"

// ==========================================================
// Tap Dance
// ==========================================================

enum {
    TD_LGUI_D = 0,
    TD_Q_SMART
};

void dance_lgui_d_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) register_code(KC_LGUI);
    else if (state->count == 2) {
        register_code(KC_LGUI);
        tap_code(KC_D);
    }
}
void dance_lgui_d_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_LGUI);
}

void dance_q_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        tap_code16(A(KC_F4));
        return;
    }
    if (state->count == 1) tap_code(KC_Q);
    else if (state->count == 2) tap_code16(G(KC_TAB));
}
void dance_q_reset(tap_dance_state_t *state, void *user_data) {}

tap_dance_action_t tap_dance_actions[] = {
    [TD_LGUI_D] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_lgui_d_finished, dance_lgui_d_reset),
    [TD_Q_SMART] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_q_finished, dance_q_reset),
};

// ==========================================================
// Combo
// ==========================================================

enum combo_events {
    COMBO_DEL,
    COMBO_DOT,
    COMBO_SCREENSHOT,
    COMBO_UNDS,
    COMBO_COLN,
    COMBO_SCLN,
    COMBO_PAREN
};

const uint16_t PROGMEM del_combo[] = {KC_DOWN, KC_RGHT, COMBO_END};
const uint16_t PROGMEM dot_combo[] = {KC_COMM, KC_UP, COMBO_END};
const uint16_t PROGMEM screenshot_combo[] = {LT(5,KC_J), KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM paren_combo[] = {LT(5,KC_J), KC_K, COMBO_END};
const uint16_t PROGMEM unds_combo[] = {KC_L, KC_MINS, COMBO_END};
const uint16_t PROGMEM coln_combo[] = {KC_9, KC_Y, COMBO_END};
const uint16_t PROGMEM scln_combo[] = {KC_6, KC_H, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [COMBO_DEL] = COMBO(del_combo, KC_DEL),
    [COMBO_DOT] = COMBO(dot_combo, KC_DOT),
    [COMBO_SCREENSHOT] = COMBO(screenshot_combo, LGUI(LSFT(KC_S))),
    [COMBO_UNDS] = COMBO(unds_combo, JP_UNDS),
    [COMBO_COLN] = COMBO(coln_combo, JP_COLN),
    [COMBO_SCLN] = COMBO(scln_combo, KC_SCLN),
    [COMBO_PAREN] = COMBO_ACTION(paren_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    if (!pressed) return;
    switch(combo_index) {
        case COMBO_PAREN:
            tap_code16(JP_LPRN);
            tap_code16(JP_RPRN);
            break;
    }
}

// ==========================================================
// layer5 GUI first only
// ==========================================================

static bool layer5_first = true;

layer_state_t layer_state_set_user(layer_state_t state) {
    if (layer_state_cmp(state, 5)) {
        layer5_first = true;
    }
    return state;
}

// ==========================================================
// custom keycodes
// ==========================================================

enum custom_keycodes {
    MC_PASS = SAFE_RANGE,
    MC_MAIL,
    MC_XL_NOBORDER,
    MC_XL_VALIGN,
    MC_USER,

    GUI_1,
    GUI_2,
    GUI_3,
    GUI_4,
    GUI_5,
    GUI_6,
    GUI_7,
    GUI_8,
    GUI_9,
    GUI_0
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (!record->event.pressed) return true;

    switch (keycode) {

        case GUI_1: if(layer5_first){tap_code16(LGUI(KC_1));layer5_first=false;} else tap_code(KC_1); return false;
        case GUI_2: if(layer5_first){tap_code16(LGUI(KC_2));layer5_first=false;} else tap_code(KC_2); return false;
        case GUI_3: if(layer5_first){tap_code16(LGUI(KC_3));layer5_first=false;} else tap_code(KC_3); return false;
        case GUI_4: if(layer5_first){tap_code16(LGUI(KC_4));layer5_first=false;} else tap_code(KC_4); return false;
        case GUI_5: if(layer5_first){tap_code16(LGUI(KC_5));layer5_first=false;} else tap_code(KC_5); return false;
        case GUI_6: if(layer5_first){tap_code16(LGUI(KC_6));layer5_first=false;} else tap_code(KC_6); return false;
        case GUI_7: if(layer5_first){tap_code16(LGUI(KC_7));layer5_first=false;} else tap_code(KC_7); return false;
        case GUI_8: if(layer5_first){tap_code16(LGUI(KC_8));layer5_first=false;} else tap_code(KC_8); return false;
        case GUI_9: if(layer5_first){tap_code16(LGUI(KC_9));layer5_first=false;} else tap_code(KC_9); return false;
        case GUI_0: if(layer5_first){tap_code16(LGUI(KC_0));layer5_first=false;} else tap_code(KC_0); return false;

        case MC_PASS:
            SEND_STRING("Wwhowaito1");
            return false;

        case MC_MAIL:
            SEND_STRING("lou12de39r");
            tap_code16(JP_AT);
            SEND_STRING("gmail");
            tap_code(KC_DOT);
            SEND_STRING("com");
            return false;

        case MC_USER:
            SEND_STRING("tomii1031");
            return false;

        case MC_XL_NOBORDER:
            tap_code(KC_LALT);
            tap_code(KC_H);
            tap_code(KC_M);
            return false;

        case MC_XL_VALIGN:
            tap_code(KC_LALT);
            tap_code(KC_H);
            tap_code(KC_V);
            return false;
    }

    return true;
}

// ==========================================================
// keymaps
// ==========================================================

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT(
KC_ESC,TD(TD_Q_SMART),KC_W,KC_E,KC_R,KC_T,KC_7,KC_8,KC_9,KC_Y,KC_U,KC_I,KC_O,KC_P,
KC_TAB,KC_A,KC_S,KC_D,LT(5,KC_F),KC_G,KC_4,KC_5,KC_6,KC_H,LT(5,KC_J),KC_K,KC_L,KC_MINS,
KC_LSFT,KC_Z,KC_X,KC_C,KC_V,KC_B,KC_1,KC_2,KC_3,KC_N,KC_M,KC_COMM,KC_UP,MT(MOD_LSFT,KC_SLSH),
KC_LCTL,TD(TD_LGUI_D),MT(MOD_LALT,KC_INT4),LT(4,KC_CAPS),LT(2,KC_SPC),LT(3,KC_0),KC_DOT,KC_BSPC,LT(1,KC_ENT),KC_LEFT,KC_DOWN,KC_RGHT
),

[1] = LAYOUT(
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,LSFT(KC_7),LSFT(KC_8),LSFT(KC_9),KC_TRNS,LSFT(KC_7),LSFT(KC_2),JP_AT,KC_TRNS,
KC_TRNS,KC_PSLS,KC_PAST,KC_PMNS,KC_PPLS,KC_TRNS,LSFT(KC_4),LSFT(KC_5),LSFT(KC_6),KC_TRNS,LSFT(KC_8),LSFT(KC_9),JP_CIRC,JP_UNDS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,LSFT(KC_1),LSFT(KC_2),LSFT(KC_3),KC_TRNS,KC_TRNS,KC_SCLN,JP_COLN,KC_NUBS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS
),

[2] = LAYOUT(
KC_TRNS,LCTL(KC_HOME),LCTL(KC_PGUP),KC_PGUP,LCTL(KC_PGDN),LCTL(KC_END),KC_F7,KC_F8,KC_F9,KC_F10,KC_7,KC_8,KC_9,KC_PPLS,
KC_TRNS,LCTL(KC_A),KC_HOME,KC_PGDN,KC_END,KC_TRNS,KC_F4,KC_F5,KC_F6,KC_F11,KC_4,KC_5,KC_6,KC_PMNS,
KC_TRNS,LCTL(KC_Z),LCTL(KC_X),LCTL(KC_C),LCTL(KC_V),KC_TRNS,KC_F1,KC_F2,KC_F3,KC_F12,KC_1,KC_2,KC_3,KC_PAST,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_0,KC_DOT,KC_COMM,KC_PSLS
),

[3] = LAYOUT(
KC_TRNS,KC_TRNS,LCTL(LSFT(KC_TAB)),KC_TRNS,LCTL(KC_TAB),KC_TRNS,LGUI(KC_7),LGUI(KC_8),LGUI(KC_9),KC_TRNS,MS_WHLU,MS_UP,MS_WHLL,MS_WHLR,
KC_TRNS,MS_BTN1,MS_BTN1,MS_BTN3,MS_BTN2,KC_TRNS,LGUI(KC_4),LGUI(KC_5),LGUI(KC_6),KC_TRNS,MS_LEFT,MS_DOWN,MS_RGHT,KC_TRNS,
KC_TRNS,KC_TRNS,MS_BTN4,KC_TRNS,MS_BTN5,KC_TRNS,LGUI(KC_1),LGUI(KC_2),LGUI(KC_3),KC_TRNS,MS_WHLD,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,LGUI(KC_0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS
),

[4] = LAYOUT(
QK_BOOT,QK_REBOOT,KC_F7,KC_F8,KC_F9,KC_F10,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,MC_USER,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_F4,KC_F5,KC_F6,KC_F11,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,MC_PASS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_F1,KC_F2,KC_F3,KC_F12,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,MC_MAIL,KC_TRNS,KC_PGUP,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_HOME,KC_PGDN,KC_END
),

[5] = LAYOUT(
KC_TRNS,KC_TRNS,LCTL(KC_W),LCTL(KC_E),LCTL(KC_R),KC_T,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,GUI_7,GUI_8,GUI_9,KC_TRNS,
KC_TRNS,LCTL(KC_A),LCTL(KC_S),LCTL(KC_D),LCTL(KC_F),LCTL(KC_G),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,GUI_4,GUI_5,GUI_6,MC_XL_NOBORDER,
KC_TRNS,LCTL(KC_Z),LCTL(KC_X),LCTL(KC_C),LCTL(KC_V),LCTL(KC_B),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,GUI_1,GUI_2,GUI_3,MC_XL_VALIGN,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,GUI_0,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS
)

};
