#include "gpio_controller.h"

// Function to write a value to a pin.
void shift_register_write_pin(int8_t pin_number, _Bool is_output) {
#ifdef WIRINGPI_SETUP
    digitalWrite(pin_number, is_output); // Write a value with WiringPi to a pin.
#else
    bcm2835_gpio_write(pin_number, is_output); // Write a value with bcm2835 to a pin.
#endif
}

// Function for a delay.
void shift_register_delay(size_t wait_time) {
#ifdef WIRINGPI_SETUP
    delay(wait_time); // Delay for WiringPi.
#else
    bcm2835_delay(wait_time); // Delay for bcm2835.
#endif
}

// Function for a delay in milliseconds.
void shift_register_delay_ms(size_t wait_time) {
#ifdef WIRINGPI_SETUP
    delayMicroseconds(wait_time); // Delay in microseconds for WiringPi.
#else
    bcm2835_delayMicroseconds(wait_time); // Delay in microseconds for bcm2835.
#endif
}

// Function for setting a pin as an input or output.
void shift_register_pin_as_output(int8_t pin_number) {
#ifdef WIRINGPI_SETUP
    pinMode(pin_number, OUTPUT); // Set a pin for WiringPi as output.
#else
    bcm2835_gpio_fsel(pin_number, BCM2835_GPIO_FSEL_OUTP); // Set a pin for bcm2835 as output.
#endif
}

// Function for initializing all the GPIO for the shift register.
void shift_register_initialize() {
#ifdef WIRINGPI_SETUP
    // Set up WiringPi, check if initializing has succeeded.
    if (wiringPiSetup() == -1)
        printf("[ERROR MESSAGE '%s']\n\t - WIRINGPI - An error has happened in the WiringPi setup!\n", program_invocation_short_name); // Error message.
#else
    // Set up BCM2835, check if initializing has succeeded.
    if (bcm2835_init() != 1)
        printf("[ERROR MESSAGE '%s']\n\t - BCM2835 - An error has happened in the BCM2835 setup!\n", program_invocation_short_name); // Error message.
#endif
}

// Function for closing the GPIO for the shift register.
void shift_register_close() {
#ifndef WIRINGPI_SETUP
    bcm2835_close(); // Close the BCM2835 functions.
#endif
}

// This function sets all the pins for the communication between the Raspberry Pi and shift register as outputs.
void shift_register_set_outputs() {
    shift_register_pin_as_output(SHIFT_REG_DATA_PIN); // Set this pin as an output, for the data pin of the shift register.
    shift_register_pin_as_output(SHIFT_REG_CLOCK_PIN); // Set this pin as an output, for the clock pin of the shift register.
    shift_register_pin_as_output(SHIFT_REG_LATCH_PIN); // Set this pin as an output, for the latch pin of the shift register.
}

// This function updates the output of the shift register (latches it) the values send to it.
void shift_register_update_output() {
    shift_register_delay_ms(1); // Wait a short time.
    shift_register_write_pin(SHIFT_REG_LATCH_PIN, HIGH_OUTPUT); // Pull the latch pin high, to output the new result on the shift register.

    shift_register_delay_ms(1); // Wait a short time.
    shift_register_write_pin(SHIFT_REG_LATCH_PIN, LOW_OUTPUT); // Pull the latch pin low, a new output is visible on the seven segment display.
}

// This function writes a bit to the data port of the shift register.
void shift_register_write_bit(_Bool bit_value) {
    shift_register_write_pin(SHIFT_REG_DATA_PIN, bit_value ? HIGH_OUTPUT : LOW_OUTPUT); // Write the data.
    shift_register_delay_ms(1); // Wait a short time.

    shift_register_write_pin(SHIFT_REG_CLOCK_PIN, HIGH_OUTPUT); // Drive the pin for the clock high, the shift register will cap the value on its data pin.
    shift_register_delay_ms(1); // Wait a short time.
    shift_register_write_pin(SHIFT_REG_CLOCK_PIN, LOW_OUTPUT); // Drive the pin for the clock low again.
}

// This function writes a complete byte to the shift register.
void shift_register_write_byte(int specific_digit) {
    // Go through all the bits, specified with 'specific_digit' and the 'digit_representation_seven_segment'.
    for (int bit_number = 0; bit_number < BIT_SIZE; bit_number++) {
        shift_register_write_bit(digit_representation_seven_segment[specific_digit] & (1 << bit_number)); // Send a single bit to the shift register.
        shift_register_delay_ms(1); // Wait a short time.
    }

    shift_register_update_output(); // Latch the output, everything must be visible on the seven segment display.
}
