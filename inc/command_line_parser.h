#ifndef LED_DEVICE_DRIVER_COMMAND_LINE_PARSER_H
#define LED_DEVICE_DRIVER_COMMAND_LINE_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_NUMBER_OF_OPTIONS (2)
#define DEFAULT_GROWTH_FACTOR (2)
#define MAXIMUM_HELP_LENGTH (150)

typedef struct command_line_option {
    char* short_flag;
    char* long_flag;
    char* help_description;
} command_line_option_t;

typedef struct command_line_builder {
    command_line_option_t* options;
    size_t number_of_options;
    size_t size_of_options;
} command_line_builder_t;

extern void initialize_command_line_builder(command_line_builder_t* builder);
extern void resize_command_line_builder(command_line_builder_t* builder);
extern void destruct_command_line_builder(command_line_builder_t* builder);

extern void add_option_to_builder(command_line_builder_t* builder, char* short_flag, char* long_flag, char* description);
extern void create_help_description(command_line_builder_t* builder, char* help_buffer, size_t size_help_buffer);

extern void parse_command_line_arguments(command_line_builder_t* builder, size_t arguments_count, char** arguments_value);

#endif
