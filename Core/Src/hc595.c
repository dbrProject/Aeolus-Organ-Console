/*
 * HC595.c
 *
 *  Created on: 18 mag 2026
 *      Author: rodolfo
 */

#include "main.h"
#include "hc595.h"

uint8_t shiftReg[4] = {0};

extern SPI_HandleTypeDef hspi2;

void HC595_Update32(void)
{
    HAL_GPIO_WritePin(LATCH_GPIO_Port, LATCH_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi2, shiftReg, 4, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(LATCH_GPIO_Port, LATCH_Pin, GPIO_PIN_SET);
}

void HC595_Update24(void)
{
    HAL_GPIO_WritePin(LATCH_GPIO_Port, LATCH_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi2, shiftReg, 3, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(LATCH_GPIO_Port, LATCH_Pin, GPIO_PIN_SET);
}

void HC595_Write32(uint32_t value)
{
    shiftReg[0] = (value >> 0)  & 0xFF;
    shiftReg[1] = (value >> 8)  & 0xFF;
    shiftReg[2] = (value >> 16) & 0xFF;
    shiftReg[3] = (value >> 24) & 0xFF;

    HC595_Update32();
}

void HC595_Write24(uint32_t value)
{
    shiftReg[2] = (value >> 0)  & 0xFF;
    shiftReg[1] = (value >> 8)  & 0xFF;
    shiftReg[0] = (value >> 16) & 0xFF;

    HC595_Update24();
}
