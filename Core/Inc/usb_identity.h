#ifndef USB_IDENTITY_H
#define USB_IDENTITY_H

#include <stdint.h>

/**
 * @brief Generate the USB serial number string from the STM32 Unique ID.
 *
 * The serial number is returned as UTF-16, as required by TinyUSB.
 *
 * @param buffer     Pointer to UTF-16 output buffer.
 * @param max_chars  Maximum number of UTF-16 characters writable.
 *
 * @return Number of UTF-16 characters written.
 */
uint8_t usb_get_serial_string(uint16_t *buffer, uint8_t max_chars);

#endif /* USB_IDENTITY_H */
