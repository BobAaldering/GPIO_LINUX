#include <stdio.h>

#include "command_line_parser.h"
#include "segment_driver_wiringpi.h"

int main(int argc, char* argv[]) {
    display_configuration_wiringpi_t configuration;

    initialize_segment_driver_wiringpi(&configuration, 0, 1, 2);
    display_number(&configuration, 6);

    command_line_builder_t options;

    initialize_command_line_builder(&options);

    add_option_to_builder(&options, "-d", "--display", "Shows a number on the display.");
    add_option_to_builder(&options, "-c", "--countdown", "Counts down till zero.");
    add_option_to_builder(&options, "-h", "--help", "This shows the help description.");

    parse_command_line_arguments(&options, argc, argv);

    destruct_command_line_builder(&options);

    return 0;
}
