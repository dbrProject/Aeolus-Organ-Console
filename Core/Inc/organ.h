/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Aeolus Organ Console Firmware
 *
 * Copyright (c) 2026 Rodolfo De Bastiani
 *
 * Author: Rodolfo De Bastiani
 */

#ifndef INC_ORGAN_H_
#define INC_ORGAN_H_

#include <stdint.h>
#include <stdbool.h>

#include "KeybScan.h"

#define LED_PER_MODULE     16U
#define NUM_MODULES        1U
#define NUM_STOPS (LED_PER_MODULE * NUM_MODULES)
#define STOP_STATE_BYTES ((NUM_STOPS + 7U) / 8U)

extern uint8_t stop_state[STOP_STATE_BYTES];

/*--------------------------------------------------------------------
 * Gestione singolo LED
 *-------------------------------------------------------------------*/
void OrganTask(void);

static inline void Stop_On(uint8_t stop)
{
    stop_state[stop / 8U] |= (1U << (stop % 8U));
}

static inline void Stop_Off(uint8_t stop)
{
    stop_state[stop / 8U] &= ~(1U << (stop % 8U));
}

static inline void Stop_Toggle(uint8_t stop)
{
    stop_state[stop / 8U] ^= (1U << (stop % 8U));
}

static inline bool Stop_Get(uint8_t stop)
{
    return (stop_state[stop / 8U] >> (stop % 8U)) & 1U;
}

static inline uint8_t Organ_Group(uint8_t key)
{
    return key / LED_PER_MODULE;
}

static inline uint8_t Organ_Stop(uint8_t key)
{
    return key % LED_PER_MODULE;
}

void Organ_KeyDown(KB_ManualId_t manual, uint8_t key);
void Organ_KeyUp(KB_ManualId_t manual, uint8_t key);

#endif /* INC_ORGAN_H_ */
