#include "command_line_parser.h"
#include "parsed_arguments_collection.h"
#include "segment_display_general.h"

int main(int argc, char* argv[]) {
    command_line_builder_t options_collection = {
        .options = NULL,
        .number_of_options = 0,
        .size_of_options = 0
    };

    parsed_collection_t parsed_collection = {
        .parsed_arguments_collection = NULL,
        .number_of_parsed_arguments = 0,
        .size_of_collection = 0
    };

    has_parsed_arguments_t existing_arguments = {
        .display_option = {.has_argument = false, .number_in_collection = 0},
        .countdown_option = {.has_argument = false, .number_in_collection = 0},
        .countup_option = {.has_argument = false, .number_in_collection = 0},
        .delay_option = {.has_argument = false, .number_in_collection = 0}
    };

    initialize_segment_driver_general();

    initialize_command_line_builder(&options_collection);
    initialize_parsed_collection(&parsed_collection);

    add_option_to_builder(&options_collection, "-d", "--display", "Shows a hexadecimal number on the display, passed as argument to this option.", INT);
    add_option_to_builder(&options_collection, "-l", "--countdown", "Counts down till '0x0' on the display, from the value passed as argument to this option. Default delay without '--wait' is '0x3E8'.", INT);
    add_option_to_builder(&options_collection, "-u", "--countup", "Counts up till '0xF' on the seven segment display, from the value passed as argument to this option. Default delay without '--wait' is '0x3E8'.", INT);
    add_option_to_builder(&options_collection, "-w", "--wait", "Represents the delay in the '--countdown' or '--countup' commands.", INT);
    add_option_to_builder(&options_collection, "-h", "--help", "This shows this help description.", HELP);

    parse_command_line_arguments(&options_collection, &parsed_collection, argc, argv);

    argument_segment_driver_general(&parsed_collection, &existing_arguments);

    destruct_command_line_builder(&options_collection);
    destruct_parsed_collection(&parsed_collection);

    de_initialize_segment_driver_general();

    return 0;
}
