#include "segment_display_general.h"

// This function initializes the seven segment display.
void initialize_segment_display_general() {
    shift_register_initialize(); // Initialize the shift register.
    shift_register_set_outputs(); // Set the specific ports of the Raspberry Pi to an output.
}

// This function shows the information on the seven segment display, based on the parsed command line arguments.
void argument_segment_display_general(parsed_collection_t *collection, has_parsed_arguments_t *existing_arguments) {
    // Check if there is no NULL pointer passed as argument.
    if (collection == NULL)
        return; // To prevent undefined behavior, return directly.

    char showed_option[SHOWED_OPTION_BUFFER_LENGTH] = "NO OPTION PROVIDED"; // String that holds the options handled on the seven segment display.

    // Go through all the options, and check if they are in the parsed collection of options.
    for (size_t single_parsed_option = 0; single_parsed_option < collection->number_of_parsed_arguments; single_parsed_option++) {
        // For the case that we have an '--display' option.
        if (strcmp(collection->parsed_arguments_collection[single_parsed_option].long_flag, "--display") == 0) {
            existing_arguments->display_option.has_argument = true;
            existing_arguments->display_option.number_in_collection = single_parsed_option;
        }
        // For the case that we have an '--countdown' option.
        else if (strcmp(collection->parsed_arguments_collection[single_parsed_option].long_flag, "--countdown") == 0) {
            existing_arguments->countdown_option.has_argument = true;
            existing_arguments->countdown_option.number_in_collection = single_parsed_option;
        }
        // For the case that we have an '--countup' option.
        else if (strcmp(collection->parsed_arguments_collection[single_parsed_option].long_flag, "--countup") == 0) {
            existing_arguments->countup_option.has_argument = true;
            existing_arguments->countup_option.number_in_collection = single_parsed_option;
        }
        // For the case that we have an '--wait' option.
        else if (strcmp(collection->parsed_arguments_collection[single_parsed_option].long_flag, "--wait") == 0) {
            existing_arguments->delay_option.has_argument = true;
            existing_arguments->delay_option.number_in_collection = single_parsed_option;
        }
    }

    // Now we take an appropriate action on the existing options. It is my design choice to show only one option, to keep the program convenient.
    if (existing_arguments->display_option.has_argument) {
        // Display a number, passed as argument.
        int specific_parsed_digit = *(int* ) collection->parsed_arguments_collection[existing_arguments->display_option.number_in_collection].argument; // Cast the argument to an integer.

        // Check if the argument is within the range.
        if (specific_parsed_digit >= 0x0 && specific_parsed_digit <= 0xF) {
            shift_register_write_byte(specific_parsed_digit); // Show the digit on the seven segment display.
            printf("[INFORMATION '%s']\n\t - OPTION DIGIT - Showed the hexadecimal number 0x%X on the segment display!\n", program_invocation_short_name, specific_parsed_digit); // Show a message to the user of the program.
        }
        else
            printf("[ERROR MESSAGE '%s']\n\t - OPTION DIGIT - Hexadecimal number is too big!\n", program_invocation_short_name); // Error, the hexadecimal number is too big to show it on the seven segment display.

        strcpy(showed_option, collection->parsed_arguments_collection[existing_arguments->display_option.number_in_collection].long_flag); // Message for the user to get the current option.
    }
    else if (existing_arguments->countdown_option.has_argument) {
        // Count up till '0xF', start with the number passed as argument.
        int start_number = *(int* ) collection->parsed_arguments_collection[existing_arguments->countdown_option.number_in_collection].argument; // Cast the argument to an integer.

        // Check if the argument is within the range.
        if (start_number >= 0x0 && start_number <= 0xF) {
            size_t delay_time; // The delay time.

            // Check if we have a delay option.
            if (existing_arguments->delay_option.has_argument) {
                delay_time = *(int* ) collection->parsed_arguments_collection[existing_arguments->delay_option.number_in_collection].argument; // Cast your time to an integer.
                printf("[INFORMATION '%s']\n\t - OPTION COUNT DOWN - Using a delay of 0x%X milliseconds between counting!\n", program_invocation_short_name, delay_time); // Message for the user.
            }
            else {
                delay_time = DEFAULT_DELAY_TIME; // The '--wait' option was not provided, use a default delay time between counting.
                printf("[INFORMATION '%s']\n\t - OPTION COUNT DOWN - Using a default delay of 0x%X milliseconds between counting (no '--wait' argument provided)!\n", program_invocation_short_name, delay_time); // Message to the user that no argument is provided.
            }

            printf("[INFORMATION '%s']\n\t - OPTION COUNT DOWN - Counting down till '0x0' from value '0x%X'...\n", program_invocation_short_name, start_number); // Message of the current option and counting down.

            // This is the actual counter.
            for (int current_digit = start_number; current_digit >= 0x0; current_digit--) {
                shift_register_write_byte(current_digit); // Show the current digit.
                shift_register_delay(delay_time); // Wait some time.
            }
        }
        else
            printf("[ERROR MESSAGE '%s']\n\t - OPTION COUNT DOWN - Hexadecimal number is too big!\n", program_invocation_short_name); // Error, the hexadecimal number is too big to show it on the seven segment display.

        strcpy(showed_option, collection->parsed_arguments_collection[existing_arguments->countdown_option.number_in_collection].long_flag); // Message for the user to get the current option.
    }
    else if (existing_arguments->countup_option.has_argument) {
        // Count down to '0x0', start with the number passed as argument.
        int start_number = *(int* ) collection->parsed_arguments_collection[existing_arguments->countup_option.number_in_collection].argument; // Cast the argument to an integer.

        // Check if the argument is within the range.
        if (start_number >= 0x0 && start_number <= 0xF) {
            size_t delay_time; // The delay time.

            // Check if we have a delay option.
            if (existing_arguments->delay_option.has_argument) {
                delay_time = *(int* ) collection->parsed_arguments_collection[existing_arguments->delay_option.number_in_collection].argument; // Cast your time to an integer.
                printf("[INFORMATION '%s']\n\t - OPTION COUNT UP - Using a delay of 0x%X milliseconds between counting!\n", program_invocation_short_name, delay_time); // Message for the user.
            }
            else {
                delay_time = DEFAULT_DELAY_TIME; // The '--wait' option was not provided, use a default delay time between counting.
                printf("[INFORMATION '%s']\n\t - OPTION COUNT UP - Using a default delay of 0x%X milliseconds between counting (no '--wait' argument provided)!\n", program_invocation_short_name, delay_time); // Message to the user that no argument is provided.
            }

            printf("[INFORMATION '%s']\n\t - OPTION COUNT UP - Counting up till '0xF' from value '0x%X'...\n", program_invocation_short_name, start_number); // Message of the current option and counting down.

            // This is the actual counter.
            for (int current_digit = start_number; current_digit <= 0xF; current_digit++) {
                shift_register_write_byte(current_digit); // Show the current digit.
                shift_register_delay(delay_time); // Wait some time.
            }
        }
        else
            printf("[ERROR MESSAGE '%s']\n\t - OPTION COUNT UP - Hexadecimal number is too big!\n", program_invocation_short_name); // Error, the hexadecimal number is too big to show it on the seven segment display.

        strcpy(showed_option, collection->parsed_arguments_collection[existing_arguments->countup_option.number_in_collection].long_flag); // Message for the user to get the current option.
    }
    else if (existing_arguments->delay_option.has_argument)
        // Only a '--wait' option is passed to the program.
        printf("[ERROR MESSAGE '%s']\n\t - WAIT ARGUMENT - Only the '--wait' option is provided without the '--countup' of '--countdown' options!\n", program_invocation_short_name);

    // Show to the user that we are quitting the 'most important' part of the application.
    printf("\n[GENERAL INFORMATION '%s']\n\t"
           " - QUITTING - Showed your specified option '%s' on the seven segment display! Call the program again to show other options.\n",
           program_invocation_short_name,
           showed_option);
}

// This function releases the resources for GPIO.
void de_initialize_segment_display_general() {
    shift_register_close(); // Close the resources for GPIO (the shift register).
}
