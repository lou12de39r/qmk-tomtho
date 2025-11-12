#pragma once

// Combo と Tap Dance を使用する
#define COMBO_COUNT 32            // 追加予定も考慮して余裕を持たせる
#define TAP_DANCE_ENTRIES 32
#define PICO_FLASH_SIZE_BYTES (1 * 1024 * 1024)
// タップを優先する（キーをすぐ離したとき）
#define TAPPING_FORCE_HOLD
