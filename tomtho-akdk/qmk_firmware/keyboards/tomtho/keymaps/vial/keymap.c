/* SPDX-License-Identifier: GPL-2.0-or-later */
#include QMK_KEYBOARD_H
#include "keymap_japanese.h" // 日本語配列キーコードを有効化

// カスタムタッピングマクロの定義
enum tap_dance_codes {
    TD_WIN_D = 0,
    TD_Q_F2 = 1,
};

// --- タップダンス関数のプロトタイプ宣言 ---
void td_win_d_finished(tap_dance_state_t *state, void *user_data);
void td_win_d_reset(tap_dance_state_t *state, void *user_data);
void td_q_f2_finished(tap_dance_state_t *state, void *user_data);
void td_q_f2_reset(tap_dance_state_t *state, void *user_data);


// --- 【修正】コンボのトリガーキー配列の定義 ---
const uint16_t PROGMEM arrow_del_combo[] = {KC_RGHT, KC_DOWN, COMBO_END};


// メインのキーマップ定義 (変更なし)
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


// --- タップダンス関数定義 (省略せず記載) ---
void td_win_d_finished(tap_dance_state_t *state, void *user_data) {
    if (state->interrupted || state->count == 0) {
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
    if (state->pressed) {
        unregister_code(KC_D);
        unregister_code(KC_LGUI);
    }
}

void td_q_f2_finished(tap_dance_state_t *state, void *user_data) {
    if (state->interrupted || state->count == 0) {
    } else if (state->count == 1) {
        // シングルタップ: Q
        tap_code(KC_Q);
    } else if (state->count == 2) {
        // ダブルタップ: F2
        tap_code(KC_F2);
    }
}

void td_q_f2_reset(tap_dance_state_t *state, void *user_data) {
}

// --- タップダンスの配列定義 (変更なし) ---
const tap_dance_action_t tap_dance_actions[] __attribute__ ((weak)) = {
    // .fn = {on_each_tap, on_dance_finished, on_dance_reset, NULL}
    [TD_WIN_D] = {
        .fn = {NULL, td_win_d_finished, td_win_d_reset, NULL},
        .user_data = NULL
    },
    [TD_Q_F2] = {
        .fn = {NULL, td_q_f2_finished, td_q_f2_reset, NULL},
        .user_data = NULL
    },
};


// コンボ配列の定義 (weak属性を削除、標準的な書き方へ)
combo_t key_combos[] = {
    // KC_RGHT と KC_DOWN の同時押しで KC_DEL を実行
    COMBO(arrow_del_combo, KC_DEL)
};
