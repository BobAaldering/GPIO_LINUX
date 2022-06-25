#ifndef GPIO_HEX_DRIVER_GPIO_CONTROLLER_H
#define GPIO_HEX_DRIVER_GPIO_CONTROLLER_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef WIRINGPI_SETUP
    #include <wiringPi.h>
    #define SHIFT_REG_DATA_PIN (0)
    #define SHIFT_REG_CLOCK_PIN (1)
    #define SHIFT_REG_LATCH_PIN (2)

    #define HIGH_OUTPUT (1)
    #define LOW_OUTPUT (0)
#else
    #include <bcm2835.h>
    #define SHIFT_REG_DATA_PIN (17)
    #define SHIFT_REG_CLOCK_PIN (18)
    #define SHIFT_REG_LATCH_PIN (27)

    #define HIGH_OUTPUT (1)
    #define LOW_OUTPUT (0)
#endif

#define BIT_SIZE (8)

// It is possible to show hexadecimal numbers on the segment display.
static const uint8_t digit_representation_seven_segment[] = {
        0b00000010, // The digit '0'.
        0b10011110, // The digit '1'.
        0b00100100, // The digit '2'.
        0b00001100, // The digit '3'.
        0b10011000, // The digit '4'.
        0b01001000, // The digit '5'.
        0b01000000, // The digit '6'.
        0b00011110, // The digit '7'.
        0b00000000, // The digit '8'.
        0b00001000, // The digit '9'.
        0b00010000, // The digit 'A'.
        0b11000000, // The digit 'B'.
        0b01100010, // The digit 'C'.
        0b10000100, // The digit 'D'.
        0b01100000, // The digit 'E'.
        0b01110000 // The digit 'F'.
};

extern void shift_register_write_pin(int8_t pin_number, _Bool is_output);
extern void shift_register_delay(int32_t wait_time);
extern void shift_register_delay_ms(int32_t wait_time);
extern void shift_register_pin_as_output(int8_t pin_number);

extern void shift_register_initialize();
extern void shift_register_close();

extern void shift_register_set_outputs();
extern void shift_register_update_output();
extern void shift_register_write_bit(_Bool bit_value);

extern void shift_register_write_byte(int specific_digit);

#endif
