#include "command_line_parser.h"

void initialize_command_line_builder(command_line_builder_t *builder) {
    if (builder == NULL)
        return;

    command_line_option_t* builder_ptr = (command_line_option_t* ) malloc(sizeof(command_line_option_t) * DEFAULT_NUMBER_OF_OPTIONS);

    if (builder_ptr) {
        builder->options = builder_ptr;
        builder->number_of_options = 0;
        builder->size_of_options = DEFAULT_NUMBER_OF_OPTIONS;
    }
}

void resize_command_line_builder(command_line_builder_t *builder) {
    if (builder == NULL)
        return;

    command_line_option_t* builder_ptr = (command_line_option_t* ) realloc(builder->options, sizeof(command_line_option_t) * builder->size_of_options * DEFAULT_GROWTH_FACTOR_ARGUMENTS);

    if (builder_ptr) {
        builder->options = builder_ptr;
        builder->size_of_options *= DEFAULT_GROWTH_FACTOR_ARGUMENTS;
    }
}

void destruct_command_line_builder(command_line_builder_t *builder) {
    if (builder == NULL)
        return;

    free(builder->options);

    builder->options = NULL;
    builder->number_of_options = 0;
    builder->size_of_options = 0;
}

void add_option_to_builder(command_line_builder_t *builder, char *short_flag, char *long_flag, char *description, supported_types_t type) {
    if (builder == NULL)
        return;

    builder->options[builder->number_of_options].short_flag = short_flag;
    builder->options[builder->number_of_options].long_flag = long_flag;
    builder->options[builder->number_of_options].type_of_option = type;

    if (strlen(description) <= MAXIMUM_HELP_LENGTH)
        builder->options[builder->number_of_options].help_description = description;
    else
        builder->options[builder->number_of_options].help_description = "[ERROR] - help description invalid!";

    builder->number_of_options++;

    if (builder->number_of_options >= builder->size_of_options)
        resize_command_line_builder(builder);
}

void create_help_description(command_line_builder_t *builder, char *help_buffer, size_t size_help_buffer) {
    int string_length = 0;

    for (size_t i = 0; i < builder->number_of_options; i++) {
        string_length += snprintf(help_buffer + string_length, size_help_buffer,
                                  "\t<%s, %s> - %s\n",
                                  builder->options[i].short_flag,
                                  builder->options[i].long_flag,
                                  builder->options[i].help_description);
    }
}

void parse_command_line_arguments(command_line_builder_t *builder, parsed_collection_t *collection_to_parse, size_t arguments_count, char **arguments_value) {
    if (arguments_count <= 1) {
        printf("Usage: ./[PROGRAM_NAME] [FLAGS - OPTIONS]\n\tUse '-h' or '--help' for application help.\n");
        return;
    }

    _Bool has_shown_help = false;
    char** end_command_arguments = arguments_value + arguments_count;

    do {
        char* argument = *(arguments_value)++;

        for (size_t single_argument = 0; single_argument < builder->number_of_options; single_argument++) {
            if (strcmp(argument, builder->options[single_argument].short_flag) == 0 || strcmp(argument, builder->options[single_argument].long_flag) == 0) {
                // Specific option found, check if it has an argument.
                if (builder->options[single_argument].type_of_option != NONE && builder->options[single_argument].type_of_option != HELP) {
                    // We have an argument for the current option.
                    if (builder->options[single_argument].type_of_option == INT) {
                        char* argument_to_parse = *(arguments_value)++;
                        char* end_ptr = NULL;

                        if (check_if_hex_command_line_argument(argument_to_parse)) {
                            int argument_to_int = strtol(argument_to_parse, &end_ptr, HEX_BASE_NUMBER); // Important, hex uses an base of 16!

                            if (argument_to_parse != end_ptr)
                                add_parsed_collection_int(collection_to_parse, builder->options[single_argument].long_flag, argument_to_int);
                        }
                        else
                            fprintf(stderr, "[ERROR MESSAGE] - Invalid hexadecimal argument!\n");
                    }
                }
                else if (builder->options[single_argument].type_of_option == HELP) {
                    // We have a help option, so print the help facilities.
                    if (!has_shown_help) {
                        char help_print_buffer[MAXIMUM_HELP_LENGTH];
                        create_help_description(builder, help_print_buffer, sizeof(help_print_buffer));

                        printf("Usage: ./[PROGRAM_NAME] [FLAGS - OPTIONS]\n"
                               "\tThis program displays hexadecimal numbers on a 'seven segment display', for example the number '0xA'.\n"
                               "%s\n",
                               help_print_buffer);

                        has_shown_help = true;
                    }
                }
                else {
                    // We don't have an argument for this option.
                    add_parsed_collection_none(collection_to_parse, builder->options[single_argument].long_flag);
                }
            }
        }
    }
    while (arguments_value != end_command_arguments);
}

_Bool check_if_hex_command_line_argument(const char *hex_representation) {
    if (strlen(hex_representation) == 3)
        return ((strstr(hex_representation, "0x") != NULL) && isxdigit(hex_representation[2])) ? true : false;
    else
        return false;
}
