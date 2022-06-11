#ifndef LED_DEVICE_DRIVER_SEGMENT_DRIVER_WIRINGPI_H
#define LED_DEVICE_DRIVER_SEGMENT_DRIVER_WIRINGPI_H

#include <stdint.h>
#include <stdio.h>

#include <wiringPi.h>
#include <sr595.h>

#define MIN_PIN_NUMBER (100)
#define PIN_NUMBERS_LATCH (10)
#define BIT_SIZE (8)

#define DEBOUNCE_TIME (50)

static const uint8_t digit_representation[] = {
        0b01000000,
        0b01111001,
        0b00100100,
        0b00110000,
        0b00011001,
        0b00010010,
        0b00000010,
        0b01111000,
        0b00000000,
        0b00010000
};

extern void wiringpi_initialize_segment_driver(int data_pin, int clock_pin, int latch_pin);
extern void wiringpi_display_number_segment_driver(int digit);

#endif
