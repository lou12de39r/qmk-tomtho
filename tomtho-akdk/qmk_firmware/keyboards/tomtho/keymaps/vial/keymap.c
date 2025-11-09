/* SPDX-License-Identifier: GPL-2.0-or-later */
#include QMK_KEYBOARD_H
#include "keymap_japanese.h" // 日本語配列キーコードを有効化

// --------------------------------------------------
// コンボ (Combos) の定義
// --------------------------------------------------

// コンボの名前を定義（enumで管理）
enum combos {
    COMBO_DEL,
    // COMBO_COUNT は VIAL_COMBO_ENTRIES に自動展開される
};

// 1. コンボを構成する物理キーの座標を定義します
const uint16_t PROGMEM combo_del_keys[] = {
    3, 10, // KC_DOWN (↓)
    3, 11, // KC_RGHT (→)
};

// 2. QMK標準のコンボ配列 (key_combos) を extern で宣言（定義はVialに任せる）
// COMBO_COUNT は QMK/Vial によって定義済み
extern combo_t key_combos[COMBO_COUNT];

// QMKのカスタム定義用関数 (COMBO_DELの動作を定義)
const combo_t PROGMEM combo_def_key_combos[] = {
    [COMBO_DEL] = COMBO(combo_del_keys, KC_DEL),
};

// --------------------------------------------------
// タップダンス (Tap Dance) の定義
// --------------------------------------------------

// タップダンスの名前を定義（enumで管理）
enum tap_dances {
    TD_LGUI_D,
    TD_COUNT // タップダンスの総数を定義（Vialが使用しないため、これは維持）
};

// --- 関数の前方宣言 ---
void td_gui_d_finished (tap_dance_state_t *state, void *user_data);
void td_gui_d_reset (tap_dance_state_t *state, void *user_data);


// タップダンスの実行時に呼ばれる関数を定義
void td_gui_d_finished (tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_LGUI);
    } else if (state->count == 2) {
        register_code(KC_LGUI);
        register_code(KC_D);
    }
}

void td_gui_d_reset (tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_LGUI);
    unregister_code(KC_D);
    // Dキーが押されたままにならないように、unregister_code(KC_D) も追加しておくと安全です
}

// タップダンスの定義配列に QMK標準の配列名 (tap_dance_actions) を extern で宣言
// TD_COUNT は enum tap_dances で定義されていることを前提とする
extern tap_dance_action_t tap_dance_actions[TD_COUNT];

// QMKのカスタム定義用配列 (TD_LGUI_Dの動作を定義)
const tap_dance_action_t PROGMEM tap_dance_actions_def[] = {
    [TD_LGUI_D] = ACTION_TAP_DANCE_FN_ADVANCED(td_gui_d_finished, NULL, td_gui_d_reset),
};

// --------------------------------------------------
// キーボードの初期化時にカスタム定義を Vial の配列にコピーする
// --------------------------------------------------

void keyboard_post_init(void) {
    // コンボの定義をコピー
    for (int i = 0; i < sizeof(combo_def_key_combos) / sizeof(combo_t); i++) {
        key_combos[i] = combo_def_key_combos[i];
    }
    
    // タップダンスの定義をコピー
    for (int i = 0; i < TD_COUNT; i++) {
        tap_dance_actions[i] = tap_dance_actions_def[i];
    }
    
    // 既存のキーボード初期化コードがあればここに続く
}


// --------------------------------------------------
// メインのキーマップ定義 (省略 - 変更なし)
// --------------------------------------------------
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_7, KC_8, KC_9, KC_Y, KC_U, KC_I, KC_O, LT(3, KC_P),
        KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_4, KC_5, KC_6, KC_H, KC_J, KC_K, KC_L, KC_MINS,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_1, KC_2, KC_3, KC_N, KC_M, KC_COMM, KC_UP, RSFT(KC_SLSH),
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
