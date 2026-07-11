/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Aeolus Organ Console Firmware
 *
 * Copyright (c) 2026 Rodolfo De Bastiani
 *
 * Author: Rodolfo De Bastiani
 */

#include "main.h"
#include "pcf8574.h"
#include "aeolus.h"
#include "tusb.h"

extern I2C_HandleTypeDef hi2c1;
static uint8_t key = KEY_NONE;    //keyboard buffer
extern uint32_t LedStatus;

static const uint8_t pcf8574_addr[] =
{
    (0x20 << 1)
};

#define NUM_PCF8574   (sizeof(pcf8574_addr) / sizeof(pcf8574_addr[0]))

static HAL_StatusTypeDef pcf8574_write(uint8_t addr, uint8_t data) {
    return HAL_I2C_Master_Transmit(&hi2c1, addr, &data, 1, HAL_MAX_DELAY);
}

static HAL_StatusTypeDef pcf8574_read(uint8_t addr, uint8_t *value) {
    return HAL_I2C_Master_Receive(&hi2c1, addr, value, 1, HAL_MAX_DELAY);
}

//static HAL_StatusTypeDef pcf8574_write(uint8_t data) {
//    return HAL_I2C_Master_Transmit(&hi2c1,PCF8574_ADDR, &data, 1, HAL_MAX_DELAY);
//}

///* Legge gli 8 bit del PCF8574 */
//static HAL_StatusTypeDef pcf8574_read(uint8_t *value) {
//    return HAL_I2C_Master_Receive(&hi2c1, PCF8574_ADDR, value, 1, HAL_MAX_DELAY);
//}


static uint8_t keypad_read_pcf(uint8_t addr) {
    for (uint8_t col = 0; col < 4; col++) {
        uint8_t col_bit = (1U << col);
        uint8_t out = 0x0F | ((~col_bit & 0x0F) << 4);

        if (pcf8574_write(addr, out) != HAL_OK)
            continue;

        uint8_t row_data;

        if (pcf8574_read(addr, &row_data) != HAL_OK)
            continue;

        row_data &= 0x0F;

        for (uint8_t row = 0; row < 4; row++) {
            if (!(row_data & (1U << row)))
            {
                return (row * 4U) + col;
            }
        }
    }

    return KEY_NONE;
}

static uint8_t keypad_read(void) {

    for (uint8_t i = 0; i < NUM_PCF8574; i++) {
        uint8_t key = keypad_read_pcf(pcf8574_addr[i]);

        if (key != KEY_NONE)
        {
            return key + (i * KEYS_PER_PCF);
        }
    }

    return KEY_NONE;
}

void keypad_task(void) {
    static uint8_t last_key = KEY_NONE;

    if (key != KEY_NONE)
        return;

    uint8_t new_key = keypad_read();

    if ((new_key != KEY_NONE) && (new_key != last_key))
    {
        key = new_key;
    }

    last_key = new_key;
}

uint8_t key_get() {
    uint8_t retval = key;             //prepare return value
    key = KEY_NONE;                   //clear keyboard buffer
    return retval;
}

void key_initialize( void ) {
  key = KEY_NONE;       //flush keyboard buffer
}

//void RegisterScan(void)
//{
//	uint8_t k = key_get();
//
//	if (k == KEY_NONE)
//	    return;
//
//	key_state ^= (1U << k);
//
//	if (key_state & (1U << k))
//	    SetRegisterOn(0x02, k);
//	else
//	    SetRegisterOff(0x02, k);
//
//	LedStatus = key_state;
//}

