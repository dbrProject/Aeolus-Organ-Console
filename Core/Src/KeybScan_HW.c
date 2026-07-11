#include "KeybScan_HW.h"

#include "main.h"
#include "dwtDelay.h"

/*----------------------------------------------------------------------------
 * Private definitions
 *---------------------------------------------------------------------------*/

/*
 * Matrix column selector (74HC138 A,B,C)
 */
static const uint16_t s_MuxPins[3] =
{
    MuxA_Pin,
    MuxB_Pin,
    MuxC_Pin
};

/*
 * Manual selection truth table.
 *
 * BSRR format:
 *
 * bits  0..15 : SET
 * bits 16..31 : RESET
 *
 * Upper : S1=0 S2=0
 * Lower : S1=1 S2=0
 * Pedal : S1=0 S2=1
 */
static const uint32_t s_ManualBSRR[KB_MANUAL_COUNT] =
{
    (S1_Pin << 16) | (S2_Pin << 16),

    (S1_Pin)       | (S2_Pin << 16),

    (S1_Pin << 16) | (S2_Pin)
};


static const uint32_t s_ColumnBSRR[8] =
{
    (MuxA_Pin<<16) | (MuxB_Pin<<16) | (MuxC_Pin<<16), // 000

    (MuxA_Pin)     | (MuxB_Pin<<16) | (MuxC_Pin<<16), // 001

    (MuxA_Pin<<16) | (MuxB_Pin)     | (MuxC_Pin<<16), // 010

    (MuxA_Pin)     | (MuxB_Pin)     | (MuxC_Pin<<16), // 011

    (MuxA_Pin<<16) | (MuxB_Pin<<16) | (MuxC_Pin),     // 100

    (MuxA_Pin)     | (MuxB_Pin<<16) | (MuxC_Pin),     // 101

    (MuxA_Pin<<16) | (MuxB_Pin)     | (MuxC_Pin),     // 110

    (MuxA_Pin)     | (MuxB_Pin)     | (MuxC_Pin)      // 111
};

/*----------------------------------------------------------------------------
 * Public functions
 *---------------------------------------------------------------------------*/

void KB_HW_Init(void)
{
    /* Nothing to do.
       GPIOs are initialized by CubeMX. */
}

void KB_HW_SelectManual(KB_ManualId_t manual)
{
    S1_GPIO_Port->BSRR = s_ManualBSRR[manual];
}

void KB_HW_SelectColumn(uint8_t column)
{
	MuxA_GPIO_Port->BSRR = s_ColumnBSRR[column];
}

uint8_t KB_HW_ReadColumn(void)
{
	 return (uint8_t)(GPIOA->IDR & 0x00FFU);
}

void KB_HW_Delay(void)
{
    DWT_Delay_us(10);
}
