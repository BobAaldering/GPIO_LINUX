#include "command_line_parser.h"
#include "parsed_arguments_collection.h"
#include "segment_display_general.h"

#include "gpio_controller.h"

int main(int argc, char* argv[]) {
    command_line_builder_t options_collection;
    parsed_collection_t parsed_collection;

    initialize_segment_driver_general();

    initialize_command_line_builder(&options_collection);
    initialize_parsed_collection(&parsed_collection);

    add_option_to_builder(&options_collection, "-d", "--display", "Shows a number on the display.", INT);
    add_option_to_builder(&options_collection, "-cd", "--countdown", "Counts down till zero.", INT);
    add_option_to_builder(&options_collection, "-cu", "--countup", "Counts up till nine.", INT);
    add_option_to_builder(&options_collection, "-h", "--help", "This shows the help description.", HELP);

    parse_command_line_arguments(&options_collection, &parsed_collection, argc, argv);

    argument_segment_driver_general(&parsed_collection);

    destruct_command_line_builder(&options_collection);
    destruct_parsed_collection(&parsed_collection);

    return 0;
}
