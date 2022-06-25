#include "segment_display_general.h"

void initialize_segment_driver_general() {
    shift_register_initialize();
    shift_register_set_outputs();
}

void argument_segment_driver_general(parsed_collection_t *collection) {
    if (collection == NULL)
        return;

    for (size_t single_parsed_option = 0; single_parsed_option < collection->number_of_parsed_arguments; single_parsed_option++) {
        if (strcmp(collection->parsed_arguments_collection[single_parsed_option].long_flag, "--display") == 0) {
            // Display a number, passed as argument.
            shift_register_write_byte(*(int* ) collection->parsed_arguments_collection[single_parsed_option].argument);
        }
        else if (strcmp(collection->parsed_arguments_collection[single_parsed_option].long_flag, "--countup") == 0) {
            // Count up till nine, start with the number passed as argument.
            int start_number = *(int* ) collection->parsed_arguments_collection[single_parsed_option].argument;

            for (int i = 0; i <= start_number; i++) {
                shift_register_write_byte(i);
                shift_register_delay(1000);
            }
        }
        else if (strcmp(collection->parsed_arguments_collection[single_parsed_option].long_flag, "--countdown") == 0) {
            // Count down to zero, start with the number passed as argument.
            int start_number = *(int* ) collection->parsed_arguments_collection[single_parsed_option].argument;

            for (int i = start_number; i >= 0; i--) {
                shift_register_write_byte(i);
                shift_register_delay(1000);
            }
        }
    }
}

void de_initialize_segment_driver_general() {
    shift_register_close();
}
