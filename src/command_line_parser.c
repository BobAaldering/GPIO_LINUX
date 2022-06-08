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

    command_line_option_t* builder_ptr = (command_line_option_t* ) realloc(builder->options, sizeof(command_line_option_t) * builder->size_of_options * DEFAULT_GROWTH_FACTOR);

    if (builder_ptr) {
        builder->options = builder_ptr;
        builder->size_of_options *= DEFAULT_GROWTH_FACTOR;
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

void add_option_to_builder(command_line_builder_t *builder, char *short_flag, char *long_flag, char *description) {
    if (builder == NULL)
        return;

    builder->options[builder->number_of_options].short_flag = short_flag;
    builder->options[builder->number_of_options].long_flag = long_flag;

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

void parse_command_line_arguments(command_line_builder_t *builder, size_t arguments_count, char **arguments_value) {
    if (arguments_count <= 1) {
        printf("Usage: ./[PROGRAM_NAME] [FLAGS]\n\tUse '-h' of '--help' for application help.\n");
        return;
    }

    for (size_t i = 0; i < arguments_count; i++) {
        for (size_t j = 0; j < builder->number_of_options; j++) {
            if (strcmp(arguments_value[i], builder->options[j].short_flag) == 0 || strcmp(arguments_value[i], builder->options[j].long_flag) == 0) {
                if (strcmp(arguments_value[i], "-h") == 0 || strcmp(arguments_value[i], "--help") == 0) {
                    char help_print_buffer[MAXIMUM_HELP_LENGTH];
                    create_help_description(builder, help_print_buffer, sizeof(help_print_buffer));

                    printf("Usage: ./[PROGRAM_NAME] [FLAGS]\n"
                           "%s\n",
                           help_print_buffer);
                }
            }
        }
    }
}
