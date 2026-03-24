/* SPDX-License-Identifier: GPL-2.0-or-later */
#include QMK_KEYBOARD_H
#include "process_tap_dance.h"
#include "quantum/keymap_extras/keymap_japanese.h"
#include "mousekey.h"

// ==========================================================
// タップダンス
// ==========================================================

enum {
    TD_LGUI_D = 0,
    TD_Q_ALT_TAB
};

static bool alt_tab_active = false;

// LGUI+D
void dance_lgui_d_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_LGUI);
    } else if (state->count == 2) {
        register_code(KC_LGUI);
        tap_code(KC_D);
    }
}

void dance_lgui_d_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_LGUI);
}

// AltTab
void dance_q_alt_tab_finished(tap_dance_state_t *state, void *user_data) {

    if (state->count == 1 && !alt_tab_active) {
        tap_code(KC_Q);
        return;
    }

    if (!alt_tab_active) {
        alt_tab_active = true;
        register_code(KC_LALT);
    }

    if (get_mods() & MOD_MASK_SHIFT) {
        register_code(KC_LSFT);
        tap_code(KC_TAB);
        unregister_code(KC_LSFT);
    } else {
        tap_code(KC_TAB);
    }
}

void dance_q_alt_tab_reset(tap_dance_state_t *state, void *user_data) {}

tap_dance_action_t tap_dance_actions[] = {
    [TD_LGUI_D] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_lgui_d_finished, dance_lgui_d_reset),
    [TD_Q_ALT_TAB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_q_alt_tab_finished, dance_q_alt_tab_reset),
};

// ==========================================================
// COMBO
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
const uint16_t PROGMEM screenshot_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM unds_combo[] = {KC_L, KC_MINS, COMBO_END};

const uint16_t PROGMEM coln_combo[] = {KC_9, KC_Y, COMBO_END};
const uint16_t PROGMEM scln_combo[] = {KC_6, KC_H, COMBO_END};
const uint16_t PROGMEM paren_combo[] = {KC_J, KC_K, COMBO_END};

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
// マクロ
// ==========================================================

enum custom_keycodes {
    MC_PASS = SAFE_RANGE,
    MC_MAIL
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (alt_tab_active && record->event.pressed) {
        switch (keycode) {
            case TD(TD_Q_ALT_TAB):
            case KC_LALT:
            case KC_LSFT:
                break;
            default:
                alt_tab_active = false;
                unregister_code(KC_LALT);
        }
    }

    switch (keycode) {

        case MC_PASS:
            if (record->event.pressed) {
                SEND_STRING("Wwhowaito1");
            }
            return false;

        case MC_MAIL:
            if (record->event.pressed) {
                SEND_STRING("lou12de39r@gmail.com");
            }
            return false;
    }

    return true;
}

// ==========================================================
// KEYMAP
// ==========================================================

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT(
KC_ESC,TD(TD_Q_ALT_TAB),KC_W,KC_E,KC_R,KC_T,KC_7,KC_8,KC_9,KC_Y,KC_U,KC_I,KC_O,KC_P,
KC_TAB,KC_A,KC_S,KC_D,KC_F,KC_G,KC_4,KC_5,KC_6,KC_H,KC_J,KC_K,KC_L,KC_MINS,
KC_LSFT,KC_Z,KC_X,KC_C,KC_V,KC_B,KC_1,KC_2,KC_3,KC_N,KC_M,KC_COMM,KC_UP,MT(MOD_LSFT,KC_SLSH),
KC_LCTL,TD(TD_LGUI_D),MT(MOD_LALT,KC_INT4),LT(4,KC_CAPS),LT(2,KC_SPC),LT(3,KC_0),KC_DOT,KC_BSPC,LT(1,KC_ENT),KC_LEFT,KC_DOWN,KC_RGHT
),

// layer4
[4] = LAYOUT(
QK_BOOT,QK_REBOOT,LSFT(KC_PGUP),KC_PGUP,LSFT(KC_PGDN),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_HOME,KC_PGDN,KC_END,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,MC_PASS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,MC_MAIL,KC_TRNS,KC_PGUP,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_HOME,KC_PGDN,KC_END
)

};
