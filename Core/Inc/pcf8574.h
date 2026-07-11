/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Aeolus Organ Console Firmware
 *
 * Copyright (c) 2026 Rodolfo De Bastiani
 *
 * Author: Rodolfo De Bastiani
 */

#ifndef INC_PCF8574_H_
#define INC_PCF8574_H_

#include "stm32f4xx_hal.h"


//#define PCF8574_ADDR (0x20 << 1)
#define KEYPAD_DELAY_MS 1
#define KEY_NONE	0xFF

#define KEYPAD_ROWS      4U
#define KEYPAD_COLS      4U
#define KEYS_PER_PCF     (KEYPAD_ROWS * KEYPAD_COLS)

void keypad_task(void);
uint8_t key_get( void );
void key_initialize( void );
//void RegisterScan(void);

#endif /* INC_PCF8574_H_ */
