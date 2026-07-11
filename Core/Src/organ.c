/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Aeolus Organ Console Firmware
 *
 * Copyright (c) 2026 Rodolfo De Bastiani
 *
 * Author: Rodolfo De Bastiani
 */

#include "organ.h"
#include "aeolus.h"
#include "pcf8574.h"
#include "hc595.h"
#include "tusb.h"

uint8_t stop_state[(NUM_STOPS + 7U)/8U] = {0};

extern uint8_t cable_num;

#define VELOCITY 127

static const uint8_t MidiChannel[KB_MANUAL_COUNT] =
{
    1,      // Upper
    2,      // Lower
    3       // Pedal
};

static const uint8_t StartNote[KB_MANUAL_COUNT] =
{
    33,
    33,
    33
};

void OrganTask(void)
{
	uint8_t key = key_get();

	if(key == KEY_NONE)
	    return;

	uint8_t group = Organ_Group(key);
	uint8_t stop  = Organ_Stop(key);

	Stop_Toggle(key);

	if(Stop_Get(key))
	    SetRegisterOn(group, stop);
	else
	    SetRegisterOff(group, stop);

	HC595_Update();
}



void Organ_KeyDown(KB_ManualId_t manual, uint8_t key)
{
    uint8_t msg[3] =
    {
        0x90 | (MidiChannel[manual]-1),
        StartNote[manual] + key,
        VELOCITY
    };

    tud_midi_stream_write(cable_num, msg, 3);
}

void Organ_KeyUp(KB_ManualId_t manual, uint8_t key)
{
    uint8_t msg[3] =
    {
        0x80 | (MidiChannel[manual]-1),
        StartNote[manual] + key,
        VELOCITY
    };

    tud_midi_stream_write(cable_num, msg, 3);
}
