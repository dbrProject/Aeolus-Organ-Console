/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Aeolus Organ Console Firmware
 *
 * Copyright (c) 2026 Rodolfo De Bastiani
 *
 * Author: Rodolfo De Bastiani
 */

#include "aeolus.h"
#include "tusb.h"

#define MIDI_STATUS  0xB4   // CC su canale 5
#define AEOLUS_CC    0x62   // controller 98

uint8_t const cable_num = 0;

const uint8_t aeolus_mode_on[8] = {
    0x60, // group 0
    0x61, // group 1
    0x62, // group 2
    0x63, // group 3
    0x64, // group 4
    0x65, // group 5
    0x66, // group 6
    0x67  // group 7
};

const uint8_t aeolus_mode_off[8] = {
    0x50, // group 0
    0x51,
    0x52,
    0x53,
    0x54,
    0x55,
    0x56,
    0x57
};

const uint8_t aeolus_mode_reset[8] = {
    0x40, // group 0
    0x41,
    0x42,
    0x43,
    0x44,
    0x45,
    0x46,
    0x47
};

const uint8_t aeolus_mode_toggle[8] = {
    0x70, // group 0
    0x71,
    0x72,
    0x73,
    0x74,
    0x75,
    0x76,
    0x77
};

const uint8_t aeolus_buttons[32] = {
    0x00, 0x01, 0x02, 0x03,
    0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B,
    0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13,
    0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1A, 0x1B,
    0x1C, 0x1D, 0x1E, 0x1F
};

void SetRegisterOn(uint8_t group, uint8_t stop) {
  uint8_t mode[3] = { 0xB4, 0x62, aeolus_mode_on[group]};
  tud_midi_stream_write(cable_num, mode, 3);

  uint8_t tab[3] = { 0xB4, 0x62, aeolus_buttons[stop]};
  tud_midi_stream_write(cable_num, tab, 3);
}

void SetRegisterOff(uint8_t group, uint8_t stop) {
  uint8_t mode[3] = { 0xB4, 0x62, aeolus_mode_off[group]};
  tud_midi_stream_write(cable_num, mode, 3);

  uint8_t tab[3] = { 0xB4, 0x62, aeolus_buttons[stop]};
  tud_midi_stream_write(cable_num, tab, 3);
}
