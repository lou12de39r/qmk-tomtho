/* SPDX-License-Identifier: GPL-2.0-or-later */
#include QMK_KEYBOARD_H
#include "keymap_japanese.h" // 日本語配列キーコードを有効化

// Tap Danceのカスタムキーコードを定義
enum custom_keycodes {
    TD_WIND = TD(0),
};

// Tap Danceの動作を定義するenum
enum tap_dance_codes {
    TD_WIN_D_WIN_H,
};

// 関数のプロトタイプ宣言 (新しい型名を使用)
void on_tap_dance(tap_dance_state_t *state, void *user_data);
void on_tap_dance_finished(tap_dance_state_t *state, void *user_data);
void on_tap_dance_reset(tap_dance_state_t *state, void *user_data);


// Tap Danceの動作を処理する関数 (新しい型名を使用)
void on_tap_dance(tap_dance_state_t *state, void *user_data) {
    if (state->keycode == TD_WIN_D_WIN_H) {
        if (state->count == 1) {
            // 単押し (Tap): Win + D (デスクトップ表示)
            unregister_code(KC_LGUI); // 念のためWinキーを離す
            register_code(KC_LGUI);
            register_code(KC_D);
        }
    }
}

void on_tap_dance_finished(tap_dance_state_t *state, void *user_data) {
    if (state->keycode == TD_WIN_D_WIN_H) {
        if (state->count == 0) { // countが0の場合はホールド
            // 長押し (Hold): Winキーをホールド状態にする
            register_code(KC_LGUI);
        }
    }
}

void on_tap_dance_reset(tap_dance_state_t *state, void *user_data) {
    if (state->keycode == TD_WIN_D_WIN_H) {
        // キーが離された時やタイムアウト時に押下状態をリセット
        unregister_code(KC_LGUI);
        unregister_code(KC_D);
    }
}

// tap danceの定義配列 (新しい型名を使用)
tap_dance_action_t tap_dance_actions[] = {
    [TD_WIN_D_WIN_H] = ACTION_TAP_DANCE_FN_ADVANCED(on_tap_dance, on_tap_dance_finished, on_tap_dance_reset),
};

// メインのキーマップ定義
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [0] = LAYOUT(
                KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_7, KC_8, KC_9, KC_Y, KC_U, KC_I, KC_O, KC_P,
                KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_4, KC_5, KC_6, KC_H, KC_J, KC_K, KC_L, JP_MINS, // KC_MINSをJP_MINSに変更
                KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_1, KC_2, KC_3, KC_N, KC_M, JP_COMM, KC_UP, JP_SLSH, // KC_COMM, KC_SLSHをJP_...に変更
                KC_LCTL, TD_WIND, KC_LOPT, LT(2, KC_CAPS), LT(1, KC_SPC), LT(3, KC_0), JP_DOT, KC_BSPC, KC_ENT, KC_LEFT, KC_DOWN, KC_RGHT // TD(0)をTD_WINDに変更, KC_DOTをJP_DOTに変更
        ),
        [1] = LAYOUT(
                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                KC_TRNS, KC_PSLS, KC_PAST, KC_PMNS, KC_PPLS, KC_TRNS, LSFT(KC_4), LSFT(KC_5), LSFT(KC_6), KC_TRNS, LSFT(KC_9), LSFT(KC_0), KC_TRNS, LSFT(JP_MINS), // LSFT(KC_MINS)をLSFT(JP_MINS)に変更
                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), KC_TRNS, KC_TRNS, JP_SCLN, JP_QUOT, KC_TRNS, // KC_SCLN, KC_QUOTをJP_...に変更
                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, KC_TRNS, KC_TRNS, KC_TRNS
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
                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
        )
};
