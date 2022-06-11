#include "segment_driver_wiringpi.h"

void wiringpi_initialize_segment_driver(int data_pin, int clock_pin, int latch_pin) {
    if (wiringPiSetup() == -1 || sr595Setup(MIN_PIN_NUMBER, PIN_NUMBERS_LATCH, data_pin, clock_pin, latch_pin) == -1)
        fprintf(stderr, "[ERROR MESSAGE] - An error has happened in the WiringPi setup!\n");
}

void wiringpi_display_number_segment_driver(int digit) {
    for (int bit_number = 0; bit_number < BIT_SIZE; bit_number++)
        digitalWrite(MIN_PIN_NUMBER + bit_number, digit_representation[digit] & (1 << bit_number));

    //delay(DEBOUNCE_TIME);
}
