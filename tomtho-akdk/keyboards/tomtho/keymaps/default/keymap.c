/* SPDX-License-Identifier: GPL-2.0-or-later */
#include QMK_KEYBOARD_H
#include "keymap_japanese.h" // 日本語配列キーコードを使用する場合

// --------------------------------------------------
// Combo定義（↓＋→ = Delete）
// --------------------------------------------------

enum combos {
    COMBO_DEL,   // コンボ名
};

const uint16_t PROGMEM combo_del_keys[] = { KC_DOWN, KC_RGHT, COMBO_END };

combo_t key_combos[] = {
    [COMBO_DEL] = COMBO(combo_del_keys, KC_DEL),
};

// --------------------------------------------------
// Tap Dance定義（LGUI単押し or LGUI+Dダブルタップ）
// --------------------------------------------------

enum {
    TD_LGUI_D,
};

void td_gui_d_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        // 単押し → Winキー (LGUI)
        register_code(KC_LGUI);
    } else if (state->count == 2) {
        // ダブルタップ → Win+D（デスクトップ表示）
        register_code(KC_LGUI);
        register_code(KC_D);
    }
}

void td_gui_d_reset(tap_dance_state_t *state, void *user_data) {
    // 押しっぱなし防止
    unregister_code(KC_LGUI);
    unregister_code(KC_D);
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_LGUI_D] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_gui_d_finished, td_gui_d_reset),
};

// --------------------------------------------------
// キーマップ本体
// --------------------------------------------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_7,   KC_8,   KC_9,   KC_Y,   KC_U,   KC_I,   KC_O,   LT(3, KC_P),
        KC_TAB,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_4,   KC_5,   KC_6,   KC_H,   KC_J,   KC_K,   KC_L,   KC_MINS,
        KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_1,   KC_2,   KC_3,   KC_N,   KC_M,   KC_COMM,KC_UP,  RSFT(KC_SLSH),
        KC_LCTL, TD(TD_LGUI_D), KC_LOPT, LT(1, KC_CAPS), LT(2, KC_SPC), LT(3, KC_0), KC_DOT, KC_BSPC, LT(1, KC_ENT), KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), KC_TRNS, KC_SCLN, KC_QUOT, KC_LBRC, KC_INT3,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LSFT(KC_4), LSFT(KC_5), LSFT(KC_6), KC_TRNS, LSFT(KC_8), LSFT(KC_9), KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [2] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, KC_7, KC_8, KC_9, KC_PPLS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F4, KC_F5, KC_F6, KC_F11, KC_4, KC_5, KC_6, KC_PMNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F12, KC_1, KC_2, KC_3, KC_PSLS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_0, KC_0, KC_PDOT, KC_PAST
    ),
    [3] = LAYOUT(
        QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_TRNS, KC_END, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RCTL(KC_PGUP), KC_HOME, KC_TRNS, KC_END, RCTL(KC_PGDN),
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RCTL(KC_PGUP), KC_TRNS, RCTL(KC_PGDN)
    )
};
