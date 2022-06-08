#ifndef LED_DEVICE_DRIVER_SEGMENT_DRIVER_WIRINGPI_H
#define LED_DEVICE_DRIVER_SEGMENT_DRIVER_WIRINGPI_H

#include <stddef.h>
#include <stdint.h>

#include <wiringPi.h>
#include <sr595.h>

#define MIN_PIN_NUMBER (100)
#define PIN_NUMBERS_LATCH (10)
#define BIT_SIZE (8)

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

typedef struct display_configuration_wiringpi {
    int data_pin_configuration;
    int clock_pin_configuration;
    int latch_pin_configuration;
} display_configuration_wiringpi_t;

extern void initialize_segment_driver_wiringpi(display_configuration_wiringpi_t* configuration, int pin_number, int clock_number, int latch_number);
extern void display_number(display_configuration_wiringpi_t* configuration, int digit);

#endif
