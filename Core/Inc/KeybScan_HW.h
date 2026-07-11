#ifndef __KEYBSCAN_HW_H
#define __KEYBSCAN_HW_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "KeybScan_Config.h"
#include "KeybScan.h"

void KB_HW_Init(void);
void KB_HW_SelectManual(KB_ManualId_t manual);
void KB_HW_SelectColumn(uint8_t column);
uint8_t KB_HW_ReadColumn(void);
void KB_HW_Delay(void);

#ifdef __cplusplus
}
#endif

#endif /* __KEYBSCAN_HW_H */
