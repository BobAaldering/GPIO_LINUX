//
// Copyright © 2022 Bob Aaldering
//

#ifndef GPIO_HEX_DRIVER_GPIO_CONTROLLER_H
#define GPIO_HEX_DRIVER_GPIO_CONTROLLER_H

#include <stdio.h> // Include the 'stdio.h' facilities.
#include <stdint.h> // Include the 'stdint.h' facilities.
#include <stdbool.h> // Include the 'stdbool.h' facilities.
#include <errno.h> // Include the 'errno.h' facilities.

// Note: this is an implementation of GPIO in combination with a 74HC595 shift register.

// Check if we are using 'WIRINGPI' of 'BCM2835' - used as a macro.
#ifdef WIRINGPI_SETUP
    #include <wiringPi.h> // Include the 'wiringPi.h' facilities.
    #define SHIFT_REG_DATA_PIN (0) // Pin configuration for the data (WiringPi -> 74HC595).
    #define SHIFT_REG_CLOCK_PIN (1) // Pin configuration for the clock (WiringPi -> 74HC595).
    #define SHIFT_REG_LATCH_PIN (2) // Pin configuration for the latch (WiringPi -> 74HC595).

    #define HIGH_OUTPUT (1) // High output on a pin.
    #define LOW_OUTPUT (0) // Low output on a pin.
#else
    #include <bcm2835.h> // Include the 'bcm2835.h' facilities.
    #define SHIFT_REG_DATA_PIN (17) // Pin configuration for the data (bcm2835 -> 74HC595).
    #define SHIFT_REG_CLOCK_PIN (18) // Pin configuration for the data (bcm2835 -> 74HC595).
    #define SHIFT_REG_LATCH_PIN (27) // Pin configuration for the data (bcm2835 -> 74HC595).

    #define HIGH_OUTPUT (1) // High output on a pin.
    #define LOW_OUTPUT (0) // Low output on a pin.
#endif

#define BIT_SIZE (8) // The size of one byte (in bit).

// Representation of all the values that can be showed on the seven segment display. The index for every item is the same as its value.
// It is possible to show hexadecimal numbers on the segment display.
// Configuration for a byte on the seven segment display 0b11111111 ->
//                                                         ABCDEFG-.
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

extern void shift_register_write_pin(int8_t pin_number, _Bool is_output); // Function to write a value to a pin.
extern void shift_register_delay(size_t wait_time); // Function for a delay.
extern void shift_register_delay_ms(size_t wait_time); // Function for a delay in milliseconds.
extern void shift_register_pin_as_output(int8_t pin_number); // Function for setting a pin as an input or output.

extern void shift_register_initialize(); // Function for initializing all the GPIO for the shift register.
extern void shift_register_close(); // Function for closing the GPIO for the shift register.

extern void shift_register_set_outputs(); // This function sets all the pins for the communication between the Raspberry Pi and shift register as outputs.
extern void shift_register_update_output(); // This function updates the output of the shift register (latches it) the values send to it.
extern void shift_register_write_bit(_Bool bit_value); // This function writes a bit to the data port of the shift register.

extern void shift_register_write_byte(int specific_digit); // This function writes a complete byte to the shift register.

#endif
