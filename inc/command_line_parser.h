#ifndef LED_DEVICE_DRIVER_COMMAND_LINE_PARSER_H
#define LED_DEVICE_DRIVER_COMMAND_LINE_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#include "parsed_arguments_collection.h"

#define HEX_BASE_NUMBER (16)

#define DEFAULT_NUMBER_OF_OPTIONS (10)
#define DEFAULT_GROWTH_FACTOR_ARGUMENTS (2)
#define MAXIMUM_HELP_LENGTH (750)

typedef enum supported_types {
    INT,
    HELP,
    NONE
} supported_types_t;

typedef struct command_line_option {
    char* short_flag;
    char* long_flag;
    char* help_description;
    supported_types_t type_of_option;
} command_line_option_t;

typedef struct command_line_builder {
    command_line_option_t* options;
    size_t number_of_options;
    size_t size_of_options;
} command_line_builder_t;

extern void initialize_command_line_builder(command_line_builder_t* builder);
extern void resize_command_line_builder(command_line_builder_t* builder);
extern void destruct_command_line_builder(command_line_builder_t* builder);

extern void add_option_to_builder(command_line_builder_t* builder, char* short_flag, char* long_flag, char* description, supported_types_t type);
extern void create_help_description(command_line_builder_t* builder, char* help_buffer, size_t size_help_buffer);

extern void parse_command_line_arguments(command_line_builder_t* builder, parsed_collection_t* collection_to_parse, size_t arguments_count, char** arguments_value);

extern _Bool check_command_line_argument(char* argument_value);

#endif
