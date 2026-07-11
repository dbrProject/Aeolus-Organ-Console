/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Aeolus Organ Console Firmware
 *
 * Copyright (c) 2026 Rodolfo De Bastiani
 *
 * Author: Rodolfo De Bastiani
 */

#ifndef INC_AEOLUS_H_
#define INC_AEOLUS_H_

#include <stdint.h>

void SetRegisterOn(uint8_t group, uint8_t stop);
void SetRegisterOff(uint8_t group, uint8_t stop);

#endif /* INC_AEOLUS_H_ */
