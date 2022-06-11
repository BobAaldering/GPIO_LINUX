#include "segment_driver_general.h"

void segment_driver_general_initialize() {
#ifdef WIRINGPI_SETUP
    wiringpi_initialize_segment_driver(0, 1, 2);
#endif
}

void segment_driver_general_arguments(parsed_collection_t *collection) {
    if (collection == NULL)
        return;

    for (size_t single_parsed_option = 0; single_parsed_option < collection->number_of_parsed_arguments; single_parsed_option++) {
        if (strcmp(collection->parsed_arguments_collection[single_parsed_option].long_flag, "--display") == 0) {
            // Display a number, passed as argument.
#ifdef WIRINGPI_SETUP
            wiringpi_display_number_segment_driver(*(int* ) collection->parsed_arguments_collection[single_parsed_option].argument);
#endif
        }
        else if (strcmp(collection->parsed_arguments_collection[single_parsed_option].long_flag, "--countup") == 0) {
            // Count down to zero, start with the number passed as argument.
#ifdef WIRINGPI_SETUP
            int start_number = *(int* ) collection->parsed_arguments_collection[single_parsed_option].argument;

            for (int i = 0; i <= start_number; i++) {
                wiringpi_display_number_segment_driver(i);
                delay(1000);
            }
#endif
        }
        else if (strcmp(collection->parsed_arguments_collection[single_parsed_option].long_flag, "--countdown") == 0) {
            // Count up to nine, start with the number passed as argument.
        }
    }
}
