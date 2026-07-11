#ifndef __KEYBSCAN_CONFIG_H
#define __KEYBSCAN_CONFIG_H

#ifdef __cplusplus
extern "C"
{
#endif

#define KB_VERSION_MAJOR               2
#define KB_VERSION_MINOR               0
#define KB_VERSION_PATCH               0

#define KB_NUM_KEYBOARDS               3
#define KB_NUM_COLUMNS                 8
#define KB_NUM_ROWS                    8
#define KB_NUM_KEYS                    (KB_NUM_COLUMNS * KB_NUM_ROWS)
#define KB_DEBOUNCE_COUNT              3

/*=============================================================================
    Reserved for future versions
=============================================================================*/

/*
 * Examples:
 *
 *  KB_MATRIX_ACTIVE_LOW
 *  KB_DEFAULT_VELOCITY
 *  KB_ENABLE_SPLIT
 *  KB_ENABLE_COUPLERS
 *  KB_ENABLE_DYNAMIC_KEYBOARD
 *  KB_SCAN_PERIOD_US
 *
 */

#ifdef __cplusplus
}
#endif

#endif /* __KEYBSCAN_CONFIG_H */

