#pragma once

// https://docs.qmk.fm/drivers/spi
// SPI Pins for PMW3360 - STM32F072

// https://www.st.com/resource/en/datasheet/stm32f072cb.pdf
// 38 page

//  PA4 - GPIO (CS)
//  PA6 - SPI1_MISO
//  PA7 - SPI1_MOSI
//  PA5 - SPI1_SCK

#define SPI_SCK_PAL_MODE 0
#define SPI_MISO_PAL_MODE 0
#define SPI_MOSI_PAL_MODE 0

#define PMW33XX_CS_PIN A4 // SPI CS pin.
#define SPI_SCK_PIN A5
#define SPI_MISO_PIN A6
#define SPI_MOSI_PIN A7

#define POINTING_DEVICE_INVERT_Y

#define DYNAMIC_KEYMAP_LAYER_COUNT 6

/* Optional. */
#define PMW33XX_CPI 800             // The CPI range is 100-12000, in increments of 100. Defaults to 1600 CPI.
#define PMW33XX_CLOCK_SPEED 2000000 // Sets the clock speed that the sensor runs at. Defaults to 2000000
#define MOUSE_EXTENDED_REPORT       // Use -32767 to 32767, instead of just -127 to 127.
#define WHEEL_EXTENDED_REPORT       // Use -32767 to 32767, instead of just -127 to 127.

#define USB_POLLING_INTERVAL_MS 2

#define PMW33XX_SPI_DIVISOR 64
#define POINTING_DEVICE_TASK_THROTTLE_MS 2
#define FORCE_NKRO

// https://docs.qmk.fm/features/pointing_device

// Addintion GPIO Pins for keyboard

// ADD0 - F1
// ADD1 - F0
// ADD2 - A0
// ADD3 - C15
// ADD4 - A1
// ADD5 - C14
// ADD6 - A2
// ADD7 - C13

