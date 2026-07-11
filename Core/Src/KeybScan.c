#include <string.h>
#include "KeybScan.h"
#include "KeybScan_HW.h"
#include "organ.h"

static KB_Keyboard_t s_Manuals[KB_NUM_KEYBOARDS];

static void KB_KeyPressed(KB_ManualId_t manual, uint8_t column, uint8_t row);
static void KB_KeyReleased(KB_ManualId_t manual, uint8_t column, uint8_t row);
static inline bool KB_IsBitSet(uint8_t value, uint8_t bit);
static inline bool KB_IsBitClear(uint8_t value, uint8_t bit);

void KB_Init(void)
{
    memset(s_Manuals, 0, sizeof(s_Manuals));

    for (uint8_t manual = 0; manual < KB_NUM_KEYBOARDS; manual++)
    {
        for (uint8_t column = 0; column < KB_NUM_COLUMNS; column++)
        {
            //Keyboard[manual].MidiState[column] = 0xFF;
            s_Manuals[manual].MidiState[column] = 0xFF;
        }
    }

    KB_HW_Init();
}

void KB_Task(void)
{
    uint8_t columnState;
    bool pressed;

    for (KB_ManualId_t manual = KB_UPPER; manual < KB_MANUAL_COUNT; manual++)
    {
        KB_HW_SelectManual(manual);

        for (uint8_t column = 0; column < KB_NUM_COLUMNS; column++)
        {
            KB_HW_SelectColumn(column);
            KB_HW_Delay();
            columnState = KB_HW_ReadColumn();

            for (uint8_t row = 0; row < KB_NUM_ROWS; row++)
            {
                uint8_t key = KB_KEY_INDEX(column, row);
                pressed = KB_IsBitClear(columnState, row);

                if (pressed != s_Manuals[manual].StableState[key])
                {
                    if (++s_Manuals[manual].DebounceCounter[key] >= KB_DEBOUNCE_COUNT)
                    {
                        s_Manuals[manual].DebounceCounter[key] = 0;
                        s_Manuals[manual].StableState[key] = pressed;

                        if (pressed)
                        {
                            KB_KeyPressed(manual, column, row);
                        }
                        else
                        {
                            KB_KeyReleased(manual, column, row);
                        }
                    }
                }
                else
                {
                    s_Manuals[manual].DebounceCounter[key] = 0;
                }
            }
        }
    }
}

static void KB_KeyPressed(KB_ManualId_t manual, uint8_t column, uint8_t row)
{
    uint8_t mask = (1U << row);

    if (s_Manuals[manual].MidiState[column] & mask)
    {
        Organ_KeyDown(manual, KB_KEY_INDEX(column, row));
        s_Manuals[manual].MidiState[column] &= ~mask;
    }
}

static void KB_KeyReleased(KB_ManualId_t manual, uint8_t column, uint8_t row)
{
    uint8_t mask = (1U << row);

    if ((s_Manuals[manual].MidiState[column] & mask) == 0)
    {
        Organ_KeyUp(manual, KB_KEY_INDEX(column, row));
        s_Manuals[manual].MidiState[column] |= mask;
    }
}

static inline bool KB_IsBitSet(uint8_t value, uint8_t bit)
{
    return (value & (1U << bit)) != 0U;
}

static inline bool KB_IsBitClear(uint8_t value, uint8_t bit)
{
    return (value & (1U << bit)) == 0U;
}
