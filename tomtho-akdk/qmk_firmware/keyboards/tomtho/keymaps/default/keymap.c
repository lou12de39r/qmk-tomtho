/* SPDX-License-Identifier: GPL-2.0-or-later */
#include QMK_KEYBOARD_H
#include "process_tap_dance.h"   // ← これを追加
// ==========================================================
// 🔸 タップダンス設定
// ==========================================================

// タップダンス識別ID
enum {
    TD_LGUI_D = 0,   // 既存: LGUI / LGUI+D
    TD_SAMPLE2,       // 追加用（例: A / Ctrl+A などに拡張可能）
};

// タップダンスの動作定義
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

// 他のタップダンスを追加する場合は、以下に関数を増やす
// 例: void dance_sample2_finished(...) { ... }

// 登録一覧
tap_dance_action_t tap_dance_actions[] = {
    [TD_LGUI_D] = TAP_DANCE_FN_ADVANCED(dance_lgui_d_finished, dance_lgui_d_reset),
    [TD_SAMPLE2] = TAP_DANCE_DOUBLE(KC_A, LCTL(KC_A)),  // 例（おまけ）
};

// ==========================================================
// 🔹 コンボ設定
// ==========================================================

// コンボ識別ID
enum combo_events {
    COMBO_DEL,     // 既存: Down + Right = Delete
    COMBO_SAMPLE2, // 追加用
};

// コンボ定義
const uint16_t PROGMEM del_combo[]     = {KC_DOWN, KC_RGHT, COMBO_END};  // 既存
const uint16_t PROGMEM sample2_combo[] = {KC_Q, KC_W, COMBO_END};        // 例: Q + W = ESC

combo_t key_combos[COMBO_COUNT] = {
    [COMBO_DEL]     = COMBO(del_combo, KC_DEL),
    [COMBO_SAMPLE2] = COMBO(sample2_combo, KC_ESC),
};

// ==========================================================
// 🧱 キーマップ定義
// ==========================================================
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
		KC_ESC,  KC_Q, KC_W, KC_E, KC_R, KC_T, KC_7, KC_8, KC_9, KC_Y, KC_U, KC_I, KC_O, KC_P,
		KC_TAB,  KC_A, KC_S, KC_D, KC_F, KC_G, KC_4, KC_5, KC_6, KC_H, KC_J, KC_K, KC_L, KC_MINS,
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_1, KC_2, KC_3, KC_N, KC_M, KC_COMM, KC_UP, KC_SLSH,
		KC_LCTL, TD(TD_LGUI_D), KC_LOPT, LT(2, KC_CAPS), LT(1, KC_SPC), LT(3, KC_0),
        KC_DOT, KC_BSPC, KC_ENT, KC_LEFT, KC_DOWN, KC_RGHT
	),

	[1] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_PSLS, KC_PAST, KC_PMNS, KC_PPLS, KC_TRNS, LSFT(KC_4), LSFT(KC_5), LSFT(KC_6), KC_TRNS, LSFT(KC_9), LSFT(KC_0), KC_TRNS, LSFT(KC_MINS),
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),

	[2] = LAYOUT(
		QK_BOOT, QK_REBOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F4, KC_F5, KC_F6, KC_F11, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F12, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),

	[3] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DOWN, KC_RGHT
	)
};
