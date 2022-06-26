#include "segment_display_general.h"

void initialize_segment_driver_general() {
    shift_register_initialize();
    shift_register_set_outputs();
}

void argument_segment_driver_general(parsed_collection_t *collection, has_parsed_arguments_t *existing_arguments) {
    if (collection == NULL)
        return;

    for (size_t single_parsed_option = 0; single_parsed_option < collection->number_of_parsed_arguments; single_parsed_option++) {
        if (strcmp(collection->parsed_arguments_collection[single_parsed_option].long_flag, "--display") == 0) {
            existing_arguments->display_option.has_argument = true;
            existing_arguments->display_option.number_in_collection = single_parsed_option;
        }
        else if (strcmp(collection->parsed_arguments_collection[single_parsed_option].long_flag, "--countdown") == 0) {
            existing_arguments->countdown_option.has_argument = true;
            existing_arguments->countdown_option.number_in_collection = single_parsed_option;
        }
        else if (strcmp(collection->parsed_arguments_collection[single_parsed_option].long_flag, "--countup") == 0) {
            existing_arguments->countup_option.has_argument = true;
            existing_arguments->countup_option.number_in_collection = single_parsed_option;
        }
        else if (strcmp(collection->parsed_arguments_collection[single_parsed_option].long_flag, "--wait") == 0) {
            existing_arguments->delay_option.has_argument = true;
            existing_arguments->delay_option.number_in_collection = single_parsed_option;
        }
    }

    if (existing_arguments->display_option.has_argument) {
        // Display a number, passed as argument.
        int specific_parsed_digit = *(int* ) collection->parsed_arguments_collection[existing_arguments->display_option.number_in_collection].argument;

        if (specific_parsed_digit >= 0x0 && specific_parsed_digit <= 0xF) {
            shift_register_write_byte(*(int* ) collection->parsed_arguments_collection[existing_arguments->display_option.number_in_collection].argument);
            printf("[INFORMATION - OPTION DIGIT] - Showed the hexadecimal number 0x%X on the segment display!\n", specific_parsed_digit);
        }
        else
            printf("[ERROR MESSAGE - OPTION DIGIT] - Hexadecimal number is too big!\n");
    }
    else if (existing_arguments->countdown_option.has_argument) {
        // Count up till '0xF', start with the number passed as argument.
        int start_number = *(int* ) collection->parsed_arguments_collection[existing_arguments->countdown_option.number_in_collection].argument;

        if (start_number >= 0x0 && start_number <= 0xF) {
            size_t delay_time;

            if (existing_arguments->delay_option.has_argument) {
                delay_time = *(int* ) collection->parsed_arguments_collection[existing_arguments->delay_option.number_in_collection].argument;
                printf("[INFORMATION - OPTION COUNT DOWN] - Using a delay of 0x%X milliseconds between counting!\n", delay_time);
            }
            else {
                delay_time = DEFAULT_DELAY_TIME;
                printf("[INFORMATION - OPTION COUNT DOWN] - Using a default delay of 0x%X milliseconds between counting (no '--wait' argument provided)!\n", delay_time);
            }

            for (int current_digit = start_number; current_digit >= 0x0; current_digit--) {
                printf("[INFORMATION - OPTION COUNT DOWN] - Showing the digit '0x%X' for the counter!\n", current_digit);

                shift_register_write_byte(current_digit);
                shift_register_delay(delay_time);
            }
        }
        else
            printf("[ERROR MESSAGE - OPTION COUNT DOWN] - Hexadecimal number is too big!\n");
    }
    else if (existing_arguments->countup_option.has_argument) {
        // Count down to '0x0', start with the number passed as argument.
        int start_number = *(int* ) collection->parsed_arguments_collection[existing_arguments->countup_option.number_in_collection].argument;

        if (start_number >= 0x0 && start_number <= 0xF) {
            size_t delay_time;

            if (existing_arguments->delay_option.has_argument) {
                delay_time = *(int* ) collection->parsed_arguments_collection[existing_arguments->delay_option.number_in_collection].argument;
                printf("[INFORMATION - OPTION COUNT UP] - Using a delay of 0x%X milliseconds between counting!\n", delay_time);
            }
            else {
                delay_time = DEFAULT_DELAY_TIME;
                printf("[INFORMATION - OPTION COUNT UP] - Using a default delay of 0x%X milliseconds between counting (no '--wait' argument provided)!\n", delay_time);
            }

            for (int current_digit = start_number; current_digit <= 0xF; current_digit++) {
                printf("[INFORMATION - OPTION COUNT DOWN] - Showing the digit '0x%X' for the counter!\n", current_digit);

                shift_register_write_byte(current_digit);
                shift_register_delay(delay_time);
            }
        }
        else
            printf("[ERROR MESSAGE - OPTION COUNT UP] - Hexadecimal number is too big!\n");
    }
}

void de_initialize_segment_driver_general() {
    shift_register_close();
}
