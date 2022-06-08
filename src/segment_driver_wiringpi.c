#include "segment_driver_wiringpi.h"

void initialize_segment_driver_wiringpi(display_configuration_wiringpi_t *configuration, int pin_number, int clock_number, int latch_number) {
    if (configuration == NULL)
        return;

    configuration->data_pin_configuration = pin_number;
    configuration->clock_pin_configuration = clock_number;
    configuration->latch_pin_configuration = latch_number;
}

void display_number(display_configuration_wiringpi_t *configuration, int digit) {
    if (wiringPiSetup() == -1 || sr595Setup(MIN_PIN_NUMBER, PIN_NUMBERS_LATCH, configuration->data_pin_configuration, configuration->clock_pin_configuration, configuration->latch_pin_configuration) == -1)
        return;

    for (int i = 0; i < BIT_SIZE; i++)
        digitalWrite(MIN_PIN_NUMBER + i, digit_representation[digit] & (1 << i));

    delay(250);
}
