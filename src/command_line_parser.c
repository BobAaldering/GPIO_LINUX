//
// Copyright © 2022 Bob Aaldering
//

#include "command_line_parser.h"

// This function initializes the command line builder (collection with the existing options).
void initialize_command_line_builder(command_line_builder_t *builder) {
    // Check if there is no NULL pointer passed as argument.
    if (builder == NULL)
        return; // To prevent undefined behavior, return directly.

    command_line_option_t* builder_ptr = (command_line_option_t* ) malloc(sizeof(command_line_option_t) * DEFAULT_NUMBER_OF_OPTIONS); // Allocate memory for the collection.

    // Check if allocating memory succeeded.
    if (builder_ptr) {
        builder->options = builder_ptr; // The pointer to the dynamic memory block.
        builder->number_of_options = 0; // Initial number of options in the collection.
        builder->size_of_options = DEFAULT_NUMBER_OF_OPTIONS; // The default size of the collection.
    }
}

// This function resizes the data structure that holds all the arguments.
void resize_command_line_builder(command_line_builder_t *builder) {
    // Check if there is no NULL pointer passed as argument.
    if (builder == NULL)
        return; // To prevent undefined behavior, return directly.

    command_line_option_t* builder_ptr = (command_line_option_t* ) realloc(builder->options, sizeof(command_line_option_t) * builder->size_of_options * DEFAULT_GROWTH_FACTOR_ARGUMENTS); // Resize the dynamic block of memory, with a growth factor of two.

    // Check if reallocating memory succeeded.
    if (builder_ptr) {
        builder->options = builder_ptr; // The pointer to the dynamic memory block.
        builder->size_of_options *= DEFAULT_GROWTH_FACTOR_ARGUMENTS; // New size of the block.
    }
}

// This function releases all the resources for the collection of options in the program.
void destruct_command_line_builder(command_line_builder_t *builder) {
    // Check if there is no NULL pointer passed as argument.
    if (builder == NULL)
        return; // To prevent undefined behavior, return directly.

    free(builder->options); // Release the allocated memory.

    builder->options = NULL; // New value of for the 'options' field. To prevent dangling pointers.
    builder->number_of_options = 0; // No options are in the collection anymore.
    builder->size_of_options = 0; // Size is also zero.
}

// This function adds a new option to the builder.
void add_option_to_builder(command_line_builder_t *builder, char *short_flag, char *long_flag, char *description, supported_types_t type) {
    // Check if there is no NULL pointer passed as argument.
    if (builder == NULL)
        return; // To prevent undefined behavior, return directly.

    builder->options[builder->number_of_options].short_flag = short_flag; // Assign the value for the short flag.
    builder->options[builder->number_of_options].long_flag = long_flag; // Assign the value for the long flag.
    builder->options[builder->number_of_options].type_of_option = type; // Assign the type of option.

    // Check the maximum length for the help description of an option.
    if (strlen(description) <= MAXIMUM_HELP_LENGTH)
        builder->options[builder->number_of_options].help_description = description; // Length is valid, assign its value.
    else
        builder->options[builder->number_of_options].help_description = "[ERROR] - help description invalid!"; // Invalid length for the help description.

    builder->number_of_options++; // New item added, so increment the number of options.

    // Check the current size of the collection, if you exceed its current size we are resizing the collection of options.
    if (builder->number_of_options >= builder->size_of_options)
        resize_command_line_builder(builder); // Resize the collection.
}

// This function creates a help description.
void create_help_description(command_line_builder_t *builder, char *help_buffer, size_t size_help_buffer) {
    int string_length = 0; // The length of the string.

    // Go through all the number of options for getting their help description.
    for (size_t i = 0; i < builder->number_of_options; i++) {
        // Generate the complete help description.
        string_length += snprintf(help_buffer + string_length, size_help_buffer,
                                  "<%s, %s> - %s\n\t\t",
                                  builder->options[i].short_flag,
                                  builder->options[i].long_flag,
                                  builder->options[i].help_description);
    }
}

// This function parses all the arguments passed to the program (main function).
void parse_command_line_arguments(command_line_builder_t *builder, parsed_collection_t *collection_to_parse, size_t arguments_count, char **arguments_value) {
    // If no program arguments are provided, show its usage.
    if (arguments_count <= 1) {
        // Show the basic usage of the program.
        printf("[GENERAL INFORMATION '%s']\n\t"
               "Usage: ./%s [FLAGS - OPTIONS]\n\t\t"
               "Use '-h' or '--help' for application help.\n\n",
               program_invocation_short_name,
               program_invocation_short_name);

        return; // Return directly.
    }

    _Bool has_shown_help = false; // Variable for indicating that the help description is showed once.
    char** end_command_arguments = arguments_value + arguments_count; // End of the passed argument to the program with 'argv' and 'argc'.

    do {
        char* argument = *(arguments_value)++; // Get the current argument, and increment it for the next time.

        // You have to check if 'argument' is an option, as defined in the collection with options.
        for (size_t single_argument = 0; single_argument < builder->number_of_options; single_argument++) {
            // Check if it is a short or long flag.
            if (strcmp(argument, builder->options[single_argument].short_flag) == 0 || strcmp(argument, builder->options[single_argument].long_flag) == 0) {
                // Specific option found, check if it has an argument.
                if (builder->options[single_argument].type_of_option != NONE && builder->options[single_argument].type_of_option != HELP) {
                    // We have an argument for the current option.

                    if (builder->options[single_argument].type_of_option == INT) {
                        // For the case of an integer argument.

                        char* argument_to_parse = *(arguments_value)++; // Get the value for the found option

                        // Check if 'argument_to_parse' is not a null pointer (no argument provided for the last option).
                        if (argument_to_parse != NULL) {
                            char* end_ptr = NULL; // Pointer for the end value (error handling).

                            // Check if your argument is valid.
                            if (check_command_line_argument(argument_to_parse)) {
                                int argument_to_int = strtol(argument_to_parse, &end_ptr, HEX_BASE_NUMBER); // Parse the character to an integer. Important, hex uses a base of 16!

                                // Error checking.
                                if (argument_to_parse != end_ptr)
                                    add_parsed_collection_int(collection_to_parse, builder->options[single_argument].long_flag, argument_to_int); // Add the parsed argument to its corresponding collection.
                            }
                            else
                                printf("[ERROR MESSAGE '%s']\n\t - PARSING ARGUMENTS - Invalid argument for option: '%s', with value '%s'!\n\n", program_invocation_short_name, builder->options[single_argument].long_flag, argument_to_parse); // An error has happened, show it to the user of the program.
                        }
                        else {
                            printf("[ERROR MESSAGE '%s']\n\t - PARSING ARGUMENTS - No argument provided by option '%s'!\n\n", program_invocation_short_name, builder->options[single_argument].long_flag); // An error has happened, no argument provided for your option. Show this to the user.
                            arguments_value = end_command_arguments; // Indicate the end of the collection.
                        }
                    }
                }
                else if (builder->options[single_argument].type_of_option == HELP) {
                    // We have a help option, so print the help facilities.

                    // Check if the help description is not previously shown.
                    if (!has_shown_help) {
                        char help_print_buffer[MAXIMUM_HELP_LENGTH]; // Array for holding the description.
                        create_help_description(builder, help_print_buffer, sizeof(help_print_buffer)); // Create the help description.

                        // Print the help description.
                        printf("[GENERAL INFORMATION '%s']\n\t"
                                "Usage: ./%s [FLAGS - OPTIONS]\n\t\t"
                               "This program displays hexadecimal numbers on a 'seven segment display', for example the number '0xA'.\n\t\t"
                               "%s\n",
                               program_invocation_short_name,
                               program_invocation_short_name,
                               help_print_buffer);

                        has_shown_help = true; // Showed the help description once.
                    }
                }
                else {
                    // We don't have an argument for this option.
                    add_parsed_collection_none(collection_to_parse, builder->options[single_argument].long_flag); // Add only a flag to the collection of parsed arguments.
                }
            }
        }
    }
    while (arguments_value != end_command_arguments); // Loop till there are no arguments anymore.
}

// This function checks if its value ('argument_value' parameter) is a flag or valid argument for an option.
_Bool check_command_line_argument(char *argument_value) {
    _Bool is_flag = (strlen(argument_value) == 2 && argument_value[0] == '-' && argument_value[1] != '-') ||
                      (strlen(argument_value) >= 4 && argument_value[0] == '-' && argument_value[1] == '-'); // Check if the argument is a flag.

    _Bool check_hex_digit = false; // Boolean for indicating is the argument is a valid hexadecimal digit.

    // For the case the argument passed to this function is no flag, check if it is a valid hexadecimal argument.
    if (!is_flag && strstr(argument_value, "0x") != NULL && strlen(argument_value) >= 3) {
        char* only_hex_digits = strchr(argument_value, 'x') + 1; // Get all the information after '0x...'.

        while (*only_hex_digits != '\0') {
            isxdigit(*only_hex_digits) ? (check_hex_digit = true) : (check_hex_digit = false); // Check if the current character is hexadecimal.
            only_hex_digits++; // Increment the value, for the next execution within this while loop.
        }
    }

    return check_hex_digit; // Return the value.
}
