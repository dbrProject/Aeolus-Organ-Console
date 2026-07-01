/*
 * pcf8574.c
 *
 *  Created on: May 4, 2026
 *      Author: rodolfo
 */

#include "main.h"
#include "pcf8574.h"
#include "aeolus.h"
#include "tusb.h"
#include <string.h>

extern I2C_HandleTypeDef hi2c1;
static E_KEY key = KEY_NONE;    //keyboard buffer
static uint16_t key_state = 0;
extern uint8_t cable_num;
extern uint32_t LedStatus;

const char keypad_map[4][4] = {
    { '1', '2', '3', 'A' },
    { '4', '5', '6', 'B' },
    { '7', '8', '9', 'C' },
    { '*', '0', '#', 'D' }
};

const E_KEY KeyMap[4][4] = {
		{INTRO_A, MAIN_A, ENDING_A, SYNCRO},
		{INTRO_B, MAIN_B, ENDING_B, OTS},
		{INTRO_C, MAIN_C, ENDING_C, BREAK},
		{MAIN_D, AUX_1, AUX_2, AUX_3}
};

static void SetRegisterOn(uint8_t group, uint8_t stop);
static void SetRegisterOff(uint8_t group, uint8_t stop);

void RegisterScan(void)
{
    E_KEY k = key_get();

    if (k != KEY_NONE) {
        key_state ^= (1 << k);
        if ((key_state & (1 << k)) != 0)
        	SetRegisterOn(0x02, k);
        else
        	SetRegisterOff(0x02,k);
    }
    LedStatus = key_state;
}

static void SetRegisterOn(uint8_t group, uint8_t stop) {
  uint8_t mode[3] = { 0xB4, 0x62, aeolus_mode_on[group] };
  tud_midi_stream_write(cable_num, mode, 3);

  uint8_t tab[3] = { 0xB4, 0x62, aeolus_buttons[stop]};
  tud_midi_stream_write(cable_num, tab, 3);
}

static void SetRegisterOff(uint8_t group, uint8_t stop) {
  uint8_t mode[3] = { 0xB4, 0x62, aeolus_mode_off[group] };
  tud_midi_stream_write(cable_num, mode, 3);

  uint8_t tab[3] = { 0xB4, 0x62, aeolus_buttons[stop]};
  tud_midi_stream_write(cable_num, tab, 3);
}

//// Invia i 4 bit di colonna, con le righe in input
//static HAL_StatusTypeDef pcf8574_write_col(uint8_t col_mask) {
//    uint8_t data = (~col_mask & 0x0F) | 0xF0; // colonne a 0, righe in input (pull-up)
//    return HAL_I2C_Master_Transmit(&hi2c1, PCF8574_ADDR, &data, 1, HAL_MAX_DELAY);
//}

static HAL_StatusTypeDef pcf8574_write_col(uint8_t col_mask) {
    uint8_t data;

    // P0..P3 = righe in input (1)
    // P4..P7 = colonna attiva a 0

    data = 0x0F | ((~col_mask & 0x0F) << 4);
    return HAL_I2C_Master_Transmit(&hi2c1,PCF8574_ADDR, &data, 1, HAL_MAX_DELAY);
}


// Legge l’intero byte dal PCF8574 (righe attive su 0)
static HAL_StatusTypeDef pcf8574_read_rows(uint8_t *row_val) {
    return HAL_I2C_Master_Receive(&hi2c1, PCF8574_ADDR, row_val, 1, HAL_MAX_DELAY);
}

void keypad_scan( void ) {

    static E_KEY pvs_key = KEY_NONE;
           E_KEY new_key = KEY_NONE;

    if(key == KEY_NONE) {
    	new_key = KEY_NONE;

    for (uint8_t col = 0; col < 4; col++) {
        uint8_t col_mask = (1 << col);  // attiva una colonna alla volta (bit basso)

        if (pcf8574_write_col(col_mask) != HAL_OK)
            continue;

        uint8_t row_data;
        if (pcf8574_read_rows(&row_data) != HAL_OK)
            continue;

        // row_data = (row_data >> 4) & 0x0F; // maschera righe (bit 4..7)
        row_data &= 0x0F;

        for (uint8_t row = 0; row < 4; row++) {
            if (!(row_data & (1 << row))) { // attivo basso
                // verifica che il tasto sia ancora premuto
                pcf8574_write_col(col_mask);

                pcf8574_read_rows(&row_data);
                // row_data = (row_data >> 4) & 0x0F;
                row_data &= 0x0F;
                if (!(row_data & (1 << row))) {
                    // new_key = KeyMap[row][col];
                    new_key = (E_KEY)(row * 4 + col);
                    break;
                }
            }
        }
    }

    if (new_key != pvs_key)          //compare current key with last key
    {                                //to detect any changes
        if (new_key != KEY_NONE)     //change detected, discard key-breaks
        {
            key = new_key;           //key-make found, copy it to key buffer
        }
    }

    pvs_key = new_key;                  //store current input for next round

  }
}

E_KEY key_get()
{
    E_KEY retval = key;             //prepare return value
    key = KEY_NONE;                 //clear keyboard buffer
    return retval;
}

void key_initialize( void )
{
  key = KEY_NONE;       //flush keyboard buffer
}


