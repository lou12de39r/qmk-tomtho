/* SPDX-License-Identifier: GPL-2.0-or-later */
#include QMK_KEYBOARD_H
#include "keymap_japanese.h" // 日本語配列キーコードを有効化

// カスタムタッピングマクロの定義
enum tap_dance_codes {
    TD_WIN_D = 0,
    TD_Q_F2 = 1,
};

// --- タップダンス関数のプロトタイプ宣言 ---
// QMKの新しいビルドシステムでは、関数定義の前にプロトタイプ宣言が必要です
void td_win_d_finished(tap_dance_state_t *state, void *user_data);
void td_win_d_reset(tap_dance_state_t *state, void *user_data);
void td_q_f2_finished(tap_dance_state_t *state, void *user_data);
void td_q_f2_reset(tap_dance_state_t *state, void *user_data);


// メインのキーマップ定義
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
		KC_ESC, TD(TD_Q_F2), KC_W, KC_E, KC_R, KC_T, KC_7, KC_8, KC_9, KC_Y, KC_U, KC_I, KC_O, LT(3, KC_P),
		KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_4, KC_5, KC_6, KC_H, KC_J, KC_K, KC_L, KC_MINS,
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_1, KC_2, KC_3, KC_N, KC_M, KC_COMM, KC_UP, RSFT(KC_SLSH),
		KC_LCTL, TD(TD_WIN_D), KC_LOPT, LT(1, KC_CAPS), LT(2, KC_SPC), LT(3, KC_0), KC_DOT, KC_BSPC, LT(1, KC_ENT), KC_LEFT, KC_DOWN, KC_RGHT
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

// --- タップダンス関数定義 ---

// TD(TD_WIN_D) の定義: タップで Win、ホールドで Win+D
void td_win_d_finished(tap_dance_state_t *state, void *user_data) {
    if (state->interrupted || state->count == 0) {
        // 何もしない
    } else if (state->pressed) {
        // ホールド: Win + D
        register_code(KC_LGUI);
        register_code(KC_D);
    } else {
        // タップ: Win
        tap_code(KC_LGUI);
    }
}

void td_win_d_reset(tap_dance_state_t *state, void *user_data) {
    // ホールドの場合に押された Win+D をリリース
    if (state->pressed) {
        unregister_code(KC_D);
        unregister_code(KC_LGUI);
    }
}

// TD(TD_Q_F2) の定義: タップで Q、ダブルタップで F2
void td_q_f2_finished(tap_dance_state_t *state, void *user_data) {
    if (state->interrupted || state->count == 0) {
        // 何もしない
    } else if (state->count == 1) {
        // シングルタップ: Q
        tap_code(KC_Q);
    } else if (state->count == 2) {
        // ダブルタップ: F2
        tap_code(KC_F2);
    }
}

void td_q_f2_reset(tap_dance_state_t *state, void *user_data) {
    // 何もしない
}

// --- タップダンスの配列定義 (TD_ACTION形式を使用) ---
// 古い QMK バージョンでも互換性のある TD_ACTION() マクロを使って関数を定義します。
tap_dance_action_t tap_dance_actions[] = {
    // td_win_d_finished (NULL, finished, reset)
    [TD_WIN_D] = TD_ACTION(TD_FN_ADVANCED(NULL, td_win_d_finished, td_win_d_reset)),
    // td_q_f2_finished (NULL, finished, reset)
    [TD_Q_F2] = TD_ACTION(TD_FN_ADVANCED(NULL, td_q_f2_finished, td_q_f2_reset)),
};
