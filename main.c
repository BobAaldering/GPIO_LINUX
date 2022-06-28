#include "command_line_parser.h" // Include the 'command_line_parser.h' facilities.
#include "parsed_arguments_collection.h" // Include the 'parsed_arguments_collection.h' facilities.
#include "segment_display_general.h" // Include the 'segment_display_general.h' facilities.

// Note: this program uses dynamically allocated memory. To make sure that this works well, it is extensively tested with an 'address sanitizer'.

int main(int argc, char* argv[]) {
    // This variable will hold the collection with options the program supports.
    command_line_builder_t options_collection = {
        .options = NULL,
        .number_of_options = 0,
        .size_of_options = 0
    };

    // This variable will hold the collection with parsed options passed to the program.
    parsed_collection_t parsed_collection = {
        .parsed_arguments_collection = NULL,
        .number_of_parsed_arguments = 0,
        .size_of_collection = 0
    };

    // This variable will give an identification of all the parsed arguments to the program.
    // A boolean indicates if the argument is present, and a number indicating its position in the 'parsed_collection' data structure.
    has_parsed_arguments_t existing_arguments = {
        .display_option = {.has_argument = false, .number_in_collection = 0},
        .countdown_option = {.has_argument = false, .number_in_collection = 0},
        .countup_option = {.has_argument = false, .number_in_collection = 0},
        .delay_option = {.has_argument = false, .number_in_collection = 0}
    };

    initialize_segment_display_general(); // Initialize the seven segment display, based on its configuration passed as an argument in CMake.

    initialize_command_line_builder(&options_collection); // Initialize the builder for command line arguments.
    initialize_parsed_collection(&parsed_collection); // Initialize the parsed collection for command line arguments.

    // Add all the different options to the program:
    add_option_to_builder(&options_collection, "-d", "--display", "Shows a hexadecimal number on the display, passed as argument to this option.", INT); // Option to show digits in hexadecimal format on the seven segment display.
    add_option_to_builder(&options_collection, "-l", "--countdown", "Counts down till '0x0' on the display, from the value passed as argument to this option. Default delay without '--wait' is '0x3E8'.", INT); // Option for counting down, based on a specified delay and argument.
    add_option_to_builder(&options_collection, "-u", "--countup", "Counts up till '0xF' on the seven segment display, from the value passed as argument to this option. Default delay without '--wait' is '0x3E8'.", INT); // Option for counting up, based on a specified delay and argument.
    add_option_to_builder(&options_collection, "-w", "--wait", "Represents the delay in the '--countdown' or '--countup' commands.", INT); // Option for specifying your own delay.
    add_option_to_builder(&options_collection, "-h", "--help", "This shows this help description.", HELP); // Option for showing the program help functionality.

    parse_command_line_arguments(&options_collection, &parsed_collection, argc, argv); // Parse all the command line argument of 'argc' and 'argv'.

    argument_segment_display_general(&parsed_collection, &existing_arguments); // Display the information on the seven segment display.

    destruct_command_line_builder(&options_collection); // Destruct the builder with command line arguments (release all the dynamic resources).
    destruct_parsed_collection(&parsed_collection); // Destruct the collection with parsed arguments (release all the dynamic resources).

    de_initialize_segment_display_general(); // Make sure that all resources for the seven segment display are released.

    return 0;
}
