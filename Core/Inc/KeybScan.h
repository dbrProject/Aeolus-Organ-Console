#ifndef __KEYBSCAN_H
#define __KEYBSCAN_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>
#include "KeybScan_Config.h"

#define KB_KEY_INDEX(col,row)      (((col) << 3) | (row))
#define KB_KEY_ROW(key)            ((key) & 0x07)
#define KB_KEY_COLUMN(key)         ((key) >> 3)


typedef enum
{
    KB_UPPER = 0,
    KB_LOWER,
    KB_PEDAL,
    KB_MANUAL_COUNT
} KB_ManualId_t;


typedef struct
{
    KB_ManualId_t Manual;
    uint8_t Key;
    bool Pressed;
} KB_Event_t;


typedef struct
{
    uint8_t StableState[KB_NUM_KEYS];
    uint8_t DebounceCounter[KB_NUM_KEYS];
    uint8_t MidiState[KB_NUM_COLUMNS];
} KB_Keyboard_t;


void KB_Init(void);
void KB_Task(void);

#ifdef __cplusplus
}
#endif

#endif /* __KEYBSCAN_H */
