/*
 * KeybScan.c
 *
 *  Created on: May 13, 2026
 *      Author: rodolfo
 */

#include "main.h"
#include "tusb.h"
#include "KeybScan.h"
#include "dwtDelay.h"

const uint16_t SelectInputPins[]  = {D0_Pin, D1_Pin, D2_Pin, D3_Pin, D4_Pin, D5_Pin, D6_Pin, D7_Pin};
const uint16_t SelectOutputPins[] = {MuxA_Pin, MuxB_Pin, MuxC_Pin};
uint8_t Bank[MAXBANKS];
uint8_t CurrBank = 0xFF;
uint8_t Column = 0;
uint8_t stableState[64];   // stato stabile (0/1)
uint8_t debounceCnt[64];   // contatore
//uint8_t const cable_num = 0;
extern uint8_t cable_num;
//static uint16_t key_state = 0;

static inline void ManageKeyDown(uint8_t Key,uint8_t Col);
static inline void ManageKeyUp(uint8_t Key,uint8_t Col);
static inline void ReadBank(void);
static inline void selectMuxPin(uint8_t pin);
static inline uint8_t IsBitSet(uint8_t b, uint8_t pos);
static inline uint8_t IsBitClear(uint8_t b, uint8_t pos);
static void SendNoteOn(uint8_t Key);
static void SendNoteOff(uint8_t key);

void KeyScanInit(void) {
  for (uint8_t i=0; i<MAXBANKS; i++) Bank[i]=0xFF;
  for (uint8_t i = 0; i < 64; i++) {
	      stableState[i] = 0;
	      debounceCnt[i] = 0;
  }
}

void KeyScan(void) {

  for (uint8_t col = 0; col < 8; col++)
	{
	    selectMuxPin(col);
	    DWT_Delay_us(10); // puoi ridurre!

	    ReadBank();

	    for (uint8_t row = 0; row < 8; row++)
	    {
	        uint8_t Key = (col << 3) | row;
	        uint8_t raw = IsBitClear(CurrBank, (Key & 0x07)); // 1 = premuto

	        if (raw != stableState[Key])
	        {
	            debounceCnt[Key]++;

	            if (debounceCnt[Key] >= 3)
	            {
	                stableState[Key] = raw;
	                debounceCnt[Key] = 0;

	                if (raw)
	                    ManageKeyDown(Key, col);
	                else
	                    ManageKeyUp(Key, col);
	            }
	        }
	        else
	        {
	            debounceCnt[Key] = 0;
	        }
	    }
	}
}

static inline void ReadBank(void) {
  CurrBank = 0; // reset!

  for(uint8_t i=0; i<8; i++)
  {
	  if (HAL_GPIO_ReadPin(SelectInputPinsPort,SelectInputPins[i]) == GPIO_PIN_SET) CurrBank |= (1 << i);
	  else CurrBank &= ~ (1 << i);
  }
}

static inline void selectMuxPin(uint8_t pin) {
    uint32_t bsrr = 0;

    for (uint8_t i = 0; i < 3; i++)
    {
        if (pin & (1 << i))
            bsrr |= SelectOutputPins[i];
        else
            bsrr |= (SelectOutputPins[i] << 16);
    }

    SelectOutputPinsPort->BSRR = bsrr;
}

uint8_t MaskKey (uint8_t Note) {
 return(1 << (Note & (0x07)));
}

static inline void ManageKeyDown(uint8_t Key,uint8_t Col) {
  if (IsBitSet(Bank[Col],(Key & 0x07)))
   {
     SendNoteOn(Key);
	 Bank[Col] &= ~(1 << (Key & 0x07));
   }
}

static inline void ManageKeyUp(uint8_t Key,uint8_t Col) {
  if (IsBitClear(Bank[Col],(Key & 0x07)))
   {
     SendNoteOff(Key);
	 Bank[Col] |= (1 << (Key & 0x07));
   }
}

static inline uint8_t IsBitSet(uint8_t b, uint8_t pos)
{
	return (b & (1 << pos)) != 0;
}

static inline uint8_t IsBitClear(uint8_t b, uint8_t pos)
{
	return (b & (1 << pos)) == 0;
}

static void SendNoteOn(uint8_t key) {
  uint8_t note_on[3] = { 0x90 | (MIDICHANNEL-1), key+STARTNOTE, VELOCITY };
  tud_midi_stream_write(cable_num, note_on, 3);
}

static void SendNoteOff(uint8_t key) {
  uint8_t note_off[3] = { 0x80 | (MIDICHANNEL-1), key+STARTNOTE, VELOCITY };
  tud_midi_stream_write(cable_num, note_off, 3);
}

