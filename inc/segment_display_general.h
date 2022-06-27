#ifndef LED_DEVICE_DRIVER_SEGMENT_SHOWER_H
#define LED_DEVICE_DRIVER_SEGMENT_SHOWER_H

#include <errno.h>
#include <string.h>

#include "parsed_arguments_collection.h"
#include "gpio_controller.h"

#define DEFAULT_DELAY_TIME (1000)

#define SHOWED_OPTION_BUFFER_LENGTH (50)

typedef struct argument_existence_pair {
    _Bool has_argument;
    size_t number_in_collection;
} argument_existence_pair;

typedef struct has_parsed_arguments {
    argument_existence_pair display_option;
    argument_existence_pair countdown_option;
    argument_existence_pair countup_option;
    argument_existence_pair delay_option;
} has_parsed_arguments_t;

extern void initialize_segment_driver_general();
extern void argument_segment_driver_general(parsed_collection_t* collection, has_parsed_arguments_t* existing_arguments);
extern void de_initialize_segment_driver_general();

#endif
