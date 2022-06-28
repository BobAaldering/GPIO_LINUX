#ifndef LED_DEVICE_DRIVER_COMMAND_LINE_PARSER_H
#define LED_DEVICE_DRIVER_COMMAND_LINE_PARSER_H

#include <stdio.h> // Include the 'stdio.h' facilities.
#include <stdlib.h> // Include the 'stdlib.h' facilities.
#include <stdbool.h> // Include the 'stdbool.h' facilities.
#include <string.h> // Include the 'string.h' facilities.
#include <errno.h> // Include the 'errno.h' facilities.
#include <ctype.h> // Include the 'ctype.h' facilities.

#include "parsed_arguments_collection.h" // Include the 'parsed_arguments_collection.h' facilities.

#define HEX_BASE_NUMBER (16) // The base number for a hexadecimal number, used for converting a string to an integer.

#define DEFAULT_NUMBER_OF_OPTIONS (10) // The default number of options that the collection of options has.
#define DEFAULT_GROWTH_FACTOR_ARGUMENTS (2) // The growth factor for the collection of arguments.
#define MAXIMUM_HELP_LENGTH (750) // The maximum length for a help description.

// Enumeration with all the supported types as argument for an option.
typedef enum supported_types {
    INT, // Integer argument.
    HELP, // Indication for a help description.
    NONE // No argument needed for this option.
} supported_types_t;

// This represents all the data needed for an option.
typedef struct command_line_option {
    char* short_flag; // Short flag of the option.
    char* long_flag; // Long flag of the option.
    char* help_description; // The help description for the option.
    supported_types_t type_of_option; // The supported type of argument.
} command_line_option_t;

// The data structure that holds all the options (uses dynamically allocated memory).
typedef struct command_line_builder {
    command_line_option_t* options; // Pointer to the dynamic allocated memory with existing options.
    size_t number_of_options; // The number of options in the collection (pointer/field above).
    size_t size_of_options; // The current size of the collection.
} command_line_builder_t;

extern void initialize_command_line_builder(command_line_builder_t* builder); // This function initializes the command line builder (collection with the existing options).
extern void resize_command_line_builder(command_line_builder_t* builder); // This function resizes the data structure that holds all the arguments.
extern void destruct_command_line_builder(command_line_builder_t* builder); // This function releases all the resources for the collection of options in the program.

extern void add_option_to_builder(command_line_builder_t* builder, char* short_flag, char* long_flag, char* description, supported_types_t type); // This function adds a new option to the builder.
extern void create_help_description(command_line_builder_t* builder, char* help_buffer, size_t size_help_buffer); // This function creates a help description.

extern void parse_command_line_arguments(command_line_builder_t* builder, parsed_collection_t* collection_to_parse, size_t arguments_count, char** arguments_value); // This function parses all the arguments passed to the program (main function).

extern _Bool check_command_line_argument(char* argument_value); // This function checks if its value ('argument_value' parameter) is a flag or valid argument for an option.

#endif
