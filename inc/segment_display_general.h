#ifndef LED_DEVICE_DRIVER_SEGMENT_SHOWER_H
#define LED_DEVICE_DRIVER_SEGMENT_SHOWER_H

#include <errno.h> // Include the 'errno.h' facilities.
#include <string.h> // Include the 'string.h' facilities.

#include "parsed_arguments_collection.h" // Include the 'parsed_arguments_collection.h' facilities.
#include "gpio_controller.h" // Include the 'gpio_controller.h' facilities.

#define DEFAULT_DELAY_TIME (1000) // Default delay time for the '--countdown' or '--countup' options.

#define SHOWED_OPTION_BUFFER_LENGTH (50) // Length for a buffer that shows the option showed on the seven segment display.

// This is a pair that indicates if an option is parsed to the program, and the number of that option in its collection.
typedef struct argument_existence_pair {
    _Bool has_argument; // This field indicates that an option is passed to the program.
    size_t number_in_collection; // The number of that option in the 'parsed_collection_t' structure.
} argument_existence_pair;

// This structure has pairs for the various options that can exist.
typedef struct has_parsed_arguments {
    argument_existence_pair display_option; // Pair for the '--display' option.
    argument_existence_pair countdown_option; // Pair for the '--countdown' option.
    argument_existence_pair countup_option; // Pair for the '--countup' option.
    argument_existence_pair delay_option; // Pair for the '--delay' option.
} has_parsed_arguments_t;

extern void initialize_segment_display_general(); // This function initializes the seven segment display.
extern void argument_segment_display_general(parsed_collection_t* collection, has_parsed_arguments_t* existing_arguments); // This function shows the information on the seven segment display, based on the parsed command line arguments.
extern void de_initialize_segment_display_general(); // This function releases the resources for GPIO.

#endif
