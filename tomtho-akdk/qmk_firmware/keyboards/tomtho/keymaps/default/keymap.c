/* SPDX-License-Identifier: GPL-2.0-or-later */
#include QMK_KEYBOARD_H
#include "process_tap_dance.h"
#include "keymap_japanese.h"

// ==========================================================
// 🔸 タップダンス設定
// ==========================================================

// タップダンス識別ID
enum {
    TD_LGUI_D = 0,    // LGUI / LGUI+D
    TD_ESC_CAPS,      // 1回ESC / 2回CapsLock
    TD_DOT_CAPS,      // タップ=DOT / ダブルタップ=CAPS
};

// --------------------
// TD_ESC_CAPS
// --------------------
void dance_esc_caps_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_ESC);
    } else if (state->count == 2) {
        tap_code(KC_CAPS);
    }
}
void dance_esc_caps_reset(tap_dance_state_t *state, void *user_data) {
    // 特に解除処理不要
}

// --------------------
// TD_LGUI_D
// --------------------
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

// --------------------
// TD_DOT_CAPS
// 🔸 変更箇所：タップ=DOT / ダブルタップ=CAPS
// --------------------
void dance_dot_caps_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_DOT);
    } else if (state->count == 2) {
        tap_code(KC_CAPS);
    }
}
void dance_dot_caps_reset(tap_dance_state_t *state, void *user_data) {
    // 解除処理不要
}

// --------------------
// 登録一覧
// --------------------
tap_dance_action_t tap_dance_actions[] = {
    [TD_LGUI_D]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_lgui_d_finished, dance_lgui_d_reset),
    [TD_ESC_CAPS]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_esc_caps_finished, dance_esc_caps_reset),
    [TD_DOT_CAPS]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_dot_caps_finished, dance_dot_caps_reset),
};

// ==========================================================
// 🔹 コンボ設定
// ==========================================================
enum combo_events {
    COMBO_DEL,      // Down + Right = Delete
    COMBO_JK_ENT,   // J + K = Enter
};

const uint16_t PROGMEM del_combo[] = {KC_DOWN, KC_RGHT, COMBO_END};
const uint16_t PROGMEM jk_ent_combo[] = {KC_J, KC_K, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [COMBO_DEL]    = COMBO(del_combo, KC_DEL),
    [COMBO_JK_ENT] = COMBO(jk_ent_combo, KC_ENT),
};

// ==========================================================
// 🔸 マクロ設定
// ==========================================================
enum custom_keycodes {
    MC_WHOWAITO = SAFE_RANGE,  // "Wwhowaito1"を出力
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MC_WHOWAITO:
            if (record->event.pressed) {
                SEND_STRING("Wwhowaito1");
            }
            return false;
    }
    return true;
}

// ==========================================================
// 🧱 キーマップ定義
// ==========================================================
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        TD(TD_ESC_CAPS), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_7, KC_8, KC_9, KC_Y, KC_U, KC_I, KC_O, KC_P,
        KC_TAB,  KC_A, KC_S, KC_D, KC_F, KC_G, KC_4, KC_5, KC_6, KC_H, KC_J, KC_K, KC_L, KC_MINS,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_1, KC_2, KC_3, KC_N, KC_M, KC_COMM, KC_UP, MT(MOD_LSFT, KC_SLSH),
        KC_LCTL, TD(TD_LGUI_D), KC_LOPT, LT(3, TD(TD_DOT_CAPS)), LT(2, KC_SPC), KC_0, KC_DOT, KC_BSPC, LT(1, KC_ENT), KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), KC_TRNS, LSFT(KC_7), LSFT(KC_2), JP_AT, KC_TRNS,
        KC_TRNS, KC_PSLS, KC_PAST, KC_PMNS, KC_PPLS, KC_TRNS, LSFT(KC_4), LSFT(KC_5), LSFT(KC_6), KC_TRNS, LSFT(KC_8), LSFT(KC_9), KC_TRNS, JP_UNDS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), KC_TRNS, KC_TRNS, KC_SCLN, KC_COLN, JP_BSLS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [2] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_7, KC_8, KC_9, KC_PPLS,
        KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_4, KC_5, KC_6, KC_PMNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_1, KC_2, KC_3, KC_PAST,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_0, KC_DOT, KC_COMM, KC_PSLS
    ),

    [3] = LAYOUT(
        QK_BOOT, QK_REBOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, KC_TRNS, KC_MS_UP, KC_TRNS, MC_WHOWAITO,
        KC_TRNS, KC_TRNS, KC_MS_BTN1, KC_MS_BTN3, KC_MS_BTN2, KC_TRNS, KC_F4, KC_F5, KC_F6, KC_F11, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F12, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};
