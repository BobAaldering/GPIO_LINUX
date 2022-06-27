#include "gpio_controller.h"

void shift_register_write_pin(int8_t pin_number, _Bool is_output) {
#ifdef WIRINGPI_SETUP
    digitalWrite(pin_number, is_output);
#else
    bcm2835_gpio_write(pin_number, is_output);
#endif
}

void shift_register_delay(size_t wait_time) {
#ifdef WIRINGPI_SETUP
    delay(wait_time);
#else
    bcm2835_delay(wait_time);
#endif
}

void shift_register_delay_ms(size_t wait_time) {
#ifdef WIRINGPI_SETUP
    delayMicroseconds(wait_time);
#else
    bcm2835_delayMicroseconds(wait_time);
#endif
}

void shift_register_pin_as_output(int8_t pin_number) {
#ifdef WIRINGPI_SETUP
    pinMode(pin_number, OUTPUT);
#else
    bcm2835_gpio_fsel(pin_number, BCM2835_GPIO_FSEL_OUTP);
#endif
}

void shift_register_initialize() {
#ifdef WIRINGPI_SETUP
    if (wiringPiSetup() == -1)
        fprintf(stderr, "[ERROR MESSAGE] - An error has happened in the WiringPi setup!\n");
#else
    if (bcm2835_init() != 1)
        fprintf(stderr, "[ERROR MESSAGE] - An error has happened in the WiringPi setup!\n");
#endif
}

void shift_register_close() {
#ifndef WIRINGPI_SETUP
    bcm2835_close();
#endif
}

void shift_register_set_outputs() {
    shift_register_pin_as_output(SHIFT_REG_DATA_PIN);
    shift_register_pin_as_output(SHIFT_REG_CLOCK_PIN);
    shift_register_pin_as_output(SHIFT_REG_LATCH_PIN);
}

void shift_register_update_output() {
    shift_register_delay_ms(1);
    shift_register_write_pin(SHIFT_REG_LATCH_PIN, HIGH_OUTPUT);

    shift_register_delay_ms(1);
    shift_register_write_pin(SHIFT_REG_LATCH_PIN, LOW_OUTPUT);
}

void shift_register_write_bit(_Bool bit_value) {
    shift_register_write_pin(SHIFT_REG_DATA_PIN, bit_value ? HIGH_OUTPUT : LOW_OUTPUT);
    shift_register_delay_ms(1);

    shift_register_write_pin(SHIFT_REG_CLOCK_PIN, HIGH_OUTPUT);
    shift_register_delay_ms(1);
    shift_register_write_pin(SHIFT_REG_CLOCK_PIN, LOW_OUTPUT);
}

void shift_register_write_byte(int specific_digit) {
    for (int bit_number = 0; bit_number < BIT_SIZE; bit_number++) {
        shift_register_write_bit(digit_representation_seven_segment[specific_digit] & (1 << bit_number));
        shift_register_delay_ms(1);
    }

    shift_register_update_output();
}
