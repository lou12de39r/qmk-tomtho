/* SPDX-License-Identifier: GPL-2.0-or-later */
#include QMK_KEYBOARD_H
#include "keymap_japanese.h" // 日本語配列キーコードを有効化

// カスタムキーコードの定義
enum custom_keycodes {
    TD_WIN_D_MACRO = SAFE_RANGE, // SAFE_RANGE以降でカスタムキーコードを定義
};

// メインのキーマップ定義
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [0] = LAYOUT(
                KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_7, KC_8, KC_9, KC_Y, KC_U, KC_I, KC_O, KC_P,
                KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_4, KC_5, KC_6, KC_H, KC_J, KC_K, KC_L, JP_MINS,
                KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_1, KC_2, KC_3, KC_N, KC_M, JP_COMM, KC_UP, JP_SLSH,
                KC_LCTL, TD_WIN_D_MACRO, KC_LOPT, LT(2, KC_CAPS), LT(1, KC_SPC), LT(3, KC_0), JP_DOT, KC_BSPC, KC_ENT, KC_LEFT, KC_DOWN, KC_RGHT // ここをカスタムキーコードに変更
        ),
        [1] = LAYOUT(
                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                KC_TRNS, KC_PSLS, KC_PAST, KC_PMNS, KC_PPLS, KC_TRNS, LSFT(KC_4), LSFT(KC_5), LSFT(KC_6), KC_TRNS, LSFT(KC_9), LSFT(KC_0), KC_TRNS, LSFT(JP_MINS),
                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), KC_TRNS, KC_TRNS, JP_SCLN, JP_QUOT, KC_TRNS,
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

// ホールド状態を追跡するための変数
static bool win_d_pressed = false;

// キー押下イベントを処理するメイン関数
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD_WIN_D_MACRO:
            if (record->event.pressed) {
                // キーが押されたとき:
                // Win+D のホールド状態を開始
                register_code(KC_LGUI);
                register_code(KC_D);
                win_d_pressed = true;
            } else {
                // キーが離されたとき:
                if (win_d_pressed) {
                    // ホールド状態が続いていたなら、キーを解放する
                    unregister_code(KC_D);
                    unregister_code(KC_LGUI);
                    win_d_pressed = false;
                    // ここではタップとホールドの区別は特にしていません。
                    // 押している間Win+D、離したら終了、という動作になります。
                }
            }
            return false; // QMKにデフォルトの処理をさせない
    }
    return true; // 他のキーはQMKに処理させる
}
