#pragma once

#include "config_common.h"

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER    T.tom
#define PRODUCT         tomtho

#define MATRIX_ROWS 4
#define MATRIX_COLS 14

#define MATRIX_ROW_PINS { GP14, GP23, GP24, GP25 }
#define MATRIX_COL_PINS { GP17, GP16, GP0, GP1, GP2, GP3, GP4, GP5, GP8, GP9, GP10, GP11, GP12, GP22 }
#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

#define DYNAMIC_KEYMAP_LAYER_COUNT 4

#ifdef VIAL_ENABLE
#    define VIAL_KEYBOARD_UID {0x12, 0x34, 0xAB, 0xCD, 0x56, 0x78, 0x90, 0xEF}
#    define VIAL_UNLOCK_COMBO_ROWS { 0, 3 }
#    define VIAL_UNLOCK_COMBO_COLS { 0, 13 }
#endif
