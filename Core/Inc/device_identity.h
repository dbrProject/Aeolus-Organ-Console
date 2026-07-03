#ifndef DEVICE_IDENTITY_H
#define DEVICE_IDENTITY_H

#include <stdint.h>

/*--------------------------------------------------------------------
 * USB identifiers
 *------------------------------------------------------------------*/

#define USB_VID             0x1209
#define USB_PID             0xDEBA
#define USB_BCD_DEVICE      0x0100

/*--------------------------------------------------------------------
 * Device strings
 *------------------------------------------------------------------*/

#define USB_MANUFACTURER    "DBR Project"
#define USB_PRODUCT         "Aeolus Organ Console"
#define USB_HW_REVISION     "Rev A"

/*--------------------------------------------------------------------
 * Firmware version
 *------------------------------------------------------------------*/

#define FW_VERSION_MAJOR    1
#define FW_VERSION_MINOR    0
#define FW_VERSION_PATCH    0

typedef struct
{
    uint16_t vid;
    uint16_t pid;
    uint16_t bcdDevice;

    const char *manufacturer;
    const char *product;
    const char *hardware;

    uint8_t fwMajor;
    uint8_t fwMinor;
    uint8_t fwPatch;

} DeviceIdentity_t;

extern const DeviceIdentity_t DeviceIdentity;

#endif
