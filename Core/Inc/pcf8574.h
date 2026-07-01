/*
 * pcf8574.h
 *
 *  Created on: May 4, 2026
 *      Author: rodolfo
 */

#ifndef INC_PCF8574_H_
#define INC_PCF8574_H_

#include "stm32f4xx_hal.h"


#define PCF8574_ADDR (0x20 << 1)
#define KEYPAD_DELAY_MS 1

typedef enum {
	INTRO_A, INTRO_B, INTRO_C, BREAK,
	MAIN_A,  MAIN_B,  MAIN_C,  MAIN_D,
	ENDING_A, ENDING_B, ENDING_C, SYNCRO,
	OTS, AUX_1, AUX_2, AUX_3, KEY_NONE
	} E_KEY;

void keypad_scan(void);
E_KEY key_get( void );
void key_initialize( void );
void RegisterScan(void);

#endif /* INC_PCF8574_H_ */
