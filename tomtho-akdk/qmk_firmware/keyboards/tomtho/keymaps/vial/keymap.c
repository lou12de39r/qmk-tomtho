/* SPDX-License-Identifier: GPL-2.0-or-later */
#include QMK_KEYBOARD_H
#include "keymap_japanese.h" // 日本語配列キーコードを有効化

// カスタムキーコードを定義 (TD(0) の代わりに KC_WIND を使用)
enum custom_keycodes {
    KC_WIND = SAFE_RANGE, // SAFE_RANGE 以降の領域を使用
};

// メインのキーマップ定義
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [0] = LAYOUT(
                KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_7, KC_8, KC_9, KC_Y, KC_U, KC_I, KC_O, KC_P,
                KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_4, KC_5, KC_6, KC_H, KC_J, KC_K, KC_L, JP_MINS, // KC_MINSをJP_MINSに変更
                KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_1, KC_2, KC_3, KC_N, KC_M, JP_COMM, KC_UP, JP_SLSH, // KC_COMM, KC_SLSHをJP_...に変更
                KC_LCTL, KC_WIND, KC_LOPT, LT(2, KC_CAPS), LT(1, KC_SPC), LT(3, KC_0), JP_DOT, KC_BSPC, KC_ENT, KC_LEFT, KC_DOWN, KC_RGHT // TD(0)をKC_WINDに変更, KC_DOTをJP_DOTに変更
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

// タップとホールドの状態を追跡する変数
static bool wind_is_pressed = false;
static bool wind_is_tapped = false;
static uint16_t wind_timer = 0;
#define TAPPING_TERM 200 // config.h に定義がない場合、ここで定義

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_WIND:
            if (record->event.pressed) {
                // キーが押された時
                if (!wind_is_pressed) {
                    wind_is_pressed = true;
                    wind_timer = timer_read();
                    wind_is_tapped = true; // とりあえずタップ状態に設定
                }
            } else {
                // キーが離された時
                wind_is_pressed = false;
                if (wind_is_tapped) {
                    // タップ処理 (Win+D)
                    register_code(KC_LGUI);
                    register_code(KC_D);
                    unregister_code(KC_D);
                    unregister_code(KC_LGUI);
                } else {
                    // ホールド解除
                    unregister_code(KC_LGUI);
                }
            }
            return false; // 他の処理をブロック
            break;
    }
    return true; // 他のキーは通常通り処理
}

// Tap/Holdの判定のためにこの関数が必要
void matrix_scan_user(void) {
    if (wind_is_pressed && wind_is_tapped && timer_elapsed(wind_timer) > TAPPING_TERM) {
        // Tapping Termを超えたのでホールドと判定
        wind_is_tapped = false;
        register_code(KC_LGUI);
    }
}
