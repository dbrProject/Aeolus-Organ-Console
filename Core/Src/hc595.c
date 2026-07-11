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
#include "hc595.h"
#include "organ.h"
#include <string.h>

extern SPI_HandleTypeDef hspi2;


void HC595_Init(void)
{
	memset(stop_state, 0, sizeof(stop_state));
    HC595_Update();
}

/*  I 74HC595 sono collegati in cascata.
 *  Il primo byte trasmesso raggiunge l'ultimo integrato della catena.
 *  Per mantenere stop_state[] nell'ordine logico dei registri
 *  è necessario invertire l'ordine dei byte trasmessi.
 */
void HC595_Update(void)
{
    uint8_t spi_buffer[STOP_STATE_BYTES];

    /* Inverte l'ordine dei byte per la catena degli HC595 */
    for (uint8_t i = 0; i < STOP_STATE_BYTES; i++)
    {
        spi_buffer[i] = stop_state[STOP_STATE_BYTES - 1U - i];
    }

    HAL_GPIO_WritePin(LATCH_GPIO_Port, LATCH_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi2, spi_buffer, STOP_STATE_BYTES, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(LATCH_GPIO_Port, LATCH_Pin, GPIO_PIN_SET);
}
