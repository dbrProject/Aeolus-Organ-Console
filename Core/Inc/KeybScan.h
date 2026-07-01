/*
 * KeybScan.h
 *
 *  Created on: May 13, 2026
 *      Author: rodolfo
 */

#ifndef INC_KEYBSCAN_H_
#define INC_KEYBSCAN_H_

#include "stm32f4xx_hal.h"

#define SelectInputPinsPort  GPIOA
#define SelectOutputPinsPort GPIOB
#define MAXBANKS 8
#define STARTNOTE 36-3
#define MIDICHANNEL 1
#define VELOCITY 127

void KeyScan(void);
void KeyScanInit(void);

#endif /* INC_KEYBSCAN_H_ */
