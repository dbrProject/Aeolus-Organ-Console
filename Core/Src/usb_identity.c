/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Aeolus Organ Console Firmware
 *
 * Copyright (c) 2026 Rodolfo De Bastiani
 *
 * Author: Rodolfo De Bastiani
 */

#include "usb_identity.h"
#include "stm32f401xc.h"
#include <stddef.h>

/*--------------------------------------------------------------------
 * Private functions
 *------------------------------------------------------------------*/

/**
 * @brief Convert a nibble (0...15) to an hexadecimal ASCII character.
 */
static char nibble_to_hex(uint8_t value)
{
    value &= 0x0F;

    if (value < 10)
    {
        return (char)('0' + value);
    }

    return (char)('A' + (value - 10));
}

/**
 * @brief Convert a 32-bit value to 8 UTF-16 hexadecimal characters.
 */
static void word_to_utf16(uint32_t value, uint16_t *buffer)
{
    for (int i = 0; i < 8; i++)
    {
        uint8_t nibble = (value >> (28 - (i * 4))) & 0x0F;

        buffer[i] = (uint16_t)nibble_to_hex(nibble);
    }
}

/*--------------------------------------------------------------------
 * Public functions
 *------------------------------------------------------------------*/

uint8_t usb_get_serial_string(uint16_t *buffer, uint8_t max_chars)
{
    if ((buffer == NULL) || (max_chars < 24))
    {
        return 0;
    }

    const volatile uint32_t * const uid = (const volatile uint32_t *)UID_BASE;

    /* UID consists of three 32-bit words.
       Each word becomes 8 hexadecimal characters.
       Total = 24 UTF-16 characters.
    */

    word_to_utf16(uid[0], &buffer[0]);
    word_to_utf16(uid[1], &buffer[8]);
    word_to_utf16(uid[2], &buffer[16]);

    return 24;
}
