#ifndef LED_DEVICE_DRIVER_SEGMENT_DRIVER_WIRINGPI_H
#define LED_DEVICE_DRIVER_SEGMENT_DRIVER_WIRINGPI_H

#include <stdint.h>
#include <stdio.h>

#include <wiringPi.h>
#include <sr595.h>

#define MIN_PIN_NUMBER (100)
#define PIN_NUMBERS_LATCH (10)
#define BIT_SIZE (8)

// It is possible to show hexadecimal numbers on the segment display.
static const uint8_t digit_representation_wiringpi[] = {
        0b01000000, // The digit '0'.
        0b01111001, // The digit '1'.
        0b00100100, // The digit '2'.
        0b00110000, // The digit '3'.
        0b00011001, // The digit '4'.
        0b00010010, // The digit '5'.
        0b00000010, // The digit '6'.
        0b01111000, // The digit '7'.
        0b00000000, // The digit '8'.
        0b00010000, // The digit '9'.
        0b00001000,
        0b00000011,
        0b01000110,
        0b00100001,
        0b00000110,
        0b00001110
};

extern void wiringpi_initialize_segment_driver(int data_pin, int clock_pin, int latch_pin);
extern void wiringpi_display_number_segment_driver(int digit);

#endif
