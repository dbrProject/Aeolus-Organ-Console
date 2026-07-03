#include "device_identity.h"

const DeviceIdentity_t DeviceIdentity =
{
    .vid = USB_VID,
    .pid = USB_PID,

    .bcdDevice = USB_BCD_DEVICE,

    .manufacturer = USB_MANUFACTURER,
    .product = USB_PRODUCT,

    .hardware = USB_HW_REVISION,

    .fwMajor = FW_VERSION_MAJOR,
    .fwMinor = FW_VERSION_MINOR,
    .fwPatch = FW_VERSION_PATCH
};
