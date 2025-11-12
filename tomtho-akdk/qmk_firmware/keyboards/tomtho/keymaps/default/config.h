#pragma once

// Combo と Tap Dance を使用する
#define COMBO_COUNT 32            // 追加予定も考慮して余裕を持たせる
#define TAP_DANCE_ENTRIES 32
#define PICO_FLASH_SIZE_BYTES (1 * 1024 * 1024)
// タップを優先する（キーをすぐ離したとき）
#define TAPPING_FORCE_HOLD
// マウス設定用
#define MOUSEKEY_DELAY             0 //マウスが動き始めるまでの時間
#define MOUSEKEY_INTERVAL         16 //マウスの動きの滑らかさ
#define MOUSEKEY_MAX_SPEED         3 //マウスの最高スピード
#define MOUSEKEY_TIME_TO_MAX      10 //マウスが最高速度に達するまでの時間
#define MOUSEKEY_WHEEL_DELAY       0 //マウスホイールが動き始めるまでの時間
