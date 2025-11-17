/* SPDX-License-Identifier: GPL-2.0-or-later */
#include QMK_KEYBOARD_H
#include "process_tap_dance.h"
#include "quantum/keymap_extras/keymap_japanese.h"
#include "mousekey.h"

// ==========================================================
// 🔸 タップダンス設定
// ==========================================================
enum {
TD_LGUI_D = 0,
TD_ESC_CAPS,
TD_Q_LAYER3,
TD_DOT_CAPS,
};

// --------------------
// TD_ESC_CAPS
// 🔸 タップ：ESC、ホールド：CAPSLOCK
// --------------------
void dance_esc_caps_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        // ホールド時（押しっぱなし）
        register_code(KC_CAPS);
    } else if (state->count == 1) {
        // 1タップ時
        tap_code(KC_ESC);
    }
}
void dance_esc_caps_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_CAPS);
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
// TD_Q_LAYER3
// 🔸 1回：Q、2回：Layer3トグル、3回：Layer0リセット
// --------------------
void dance_q_layer3_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_Q);
    } else if (state->count == 2) {
        layer_invert(3);
    } else if (state->count >= 3) {
        layer_move(0);
    }
}
void dance_q_layer3_reset(tap_dance_state_t *state, void *user_data) {}

// --------------------
// TD_DOT_CAPS
// 🔸 タップ：DOT、ホールド：CAPSLOCK
// --------------------
void dance_dot_caps_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code(KC_CAPS);
    } else if (state->count == 1) {
        tap_code(KC_DOT);
    }
}
void dance_dot_caps_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_CAPS);
}

// --------------------
// 登録一覧
// --------------------
tap_dance_action_t tap_dance_actions[] = {
    [TD_LGUI_D]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_lgui_d_finished, dance_lgui_d_reset),
    [TD_ESC_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_esc_caps_finished, dance_esc_caps_reset),
    [TD_Q_LAYER3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_q_layer3_finished, dance_q_layer3_reset),
    [TD_DOT_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_dot_caps_finished, dance_dot_caps_reset),
};

// ==========================================================
// 🔹 コンボ設定
// ==========================================================
enum combo_events {
    COMBO_DEL,
    COMBO_JK_ENT,
    COMBO_DOT,
    COMBO_OP_INT4,   // ★ 追加
};

const uint16_t PROGMEM del_combo[] = {KC_DOWN, KC_RGHT, COMBO_END};
const uint16_t PROGMEM jk_ent_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM dot_combo[] = {KC_COMM, KC_UP, COMBO_END};
const uint16_t PROGMEM op_int4_combo[] = {KC_O, KC_P, COMBO_END};  // ★ 追加

combo_t key_combos[COMBO_COUNT] = {
    [COMBO_DEL]    = COMBO(del_combo, KC_DEL),
    [COMBO_JK_ENT] = COMBO(jk_ent_combo, KC_ENT),
    [COMBO_DOT]    = COMBO(dot_combo, KC_DOT),
    [COMBO_OP_INT4] = COMBO(op_int4_combo, KC_INT4),  // ★ 追加
};

// ==========================================================
// 🔸 マクロ設定
// ==========================================================
enum custom_keycodes {
    MC_WHOWAITO = SAFE_RANGE,
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
KC_ESC, TD(TD_Q_LAYER3), KC_W, KC_E, KC_R, KC_T, KC_7, KC_8, KC_9, KC_Y, KC_U, KC_I, KC_O, LT(4,KC_P),
KC_TAB,  KC_A, KC_S, KC_D, KC_F, KC_G, KC_4, KC_5, KC_6, KC_H, KC_J, KC_K, KC_L, KC_MINS,
KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_1, KC_2, KC_3, KC_N, KC_M, KC_COMM, KC_UP, MT(MOD_LSFT, KC_SLSH),
KC_LCTL, TD(TD_LGUI_D), MT(MOD_LALT, KC_INT4), LT(4,KC_CAPS), LT(2, KC_SPC), LT(3,KC_0), KC_DOT, KC_BSPC, LT(1, KC_ENT), KC_LEFT, KC_DOWN, KC_RGHT
),

[1] = LAYOUT(  
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), KC_TRNS, LSFT(KC_7), LSFT(KC_2), JP_AT, KC_TRNS,  
    KC_TRNS, KC_PSLS, KC_PAST, KC_PMNS, KC_PPLS, KC_TRNS, LSFT(KC_4), LSFT(KC_5), LSFT(KC_6), KC_TRNS, LSFT(KC_8), LSFT(KC_9), KC_TRNS, JP_UNDS,  
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), KC_TRNS, KC_TRNS, KC_SCLN, KC_COLN, JP_BSLS,  
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS  
),  

[2] = LAYOUT(  
    KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, KC_7, KC_8, KC_9, KC_PPLS,  
    KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_F4, KC_F5, KC_F6, KC_F11, KC_4, KC_5, KC_6, KC_PMNS,  
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F12, KC_1, KC_2, KC_3, KC_PAST,  
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_0, KC_DOT, KC_COMM, KC_PSLS  
),  

[3] = LAYOUT(  
    KC_TRNS, KC_TRNS, MS_BTN4, KC_TRNS, MS_BTN5, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MS_WHLU, MS_UP, MS_WHLL, MS_WHLR,  
    KC_TRNS, MS_BTN1, MS_BTN1, MS_BTN3, MS_BTN2, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MS_LEFT, MS_DOWN, MS_RGHT, KC_TRNS,  
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MS_WHLD, KC_TRNS, KC_TRNS, KC_TRNS,  
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS  
),  

[4] = LAYOUT(  
    QK_BOOT, QK_REBOOT, LSFT(KC_PGUP), KC_PGUP, LSFT(KC_PGDN), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  
    KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MC_WHOWAITO, KC_TRNS, KC_TRNS, KC_TRNS,  
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS  
)
};
