cmake_minimum_required(VERSION 3.18) # The minimum CMake version used.
project(LED_DEVICE_DRIVER) # Name of the current project.

add_executable(LED_DEVICE_DRIVER) # Define a name for your executable.

set(target LED_DEVICE_DRIVER) # Create a name for your target.

set(USE_WIRINGPI ON CACHE BOOL "Variable to indicate using WiringPi for driving the seven segment display.")
target_compile_definitions(LED_DEVICE_DRIVER PRIVATE WIRINGPI_SETUP ${USE_WIRINGPI})

# Here, you can add the files you want to add to your executable.
target_sources(${target}
        PRIVATE
        ./main.c # The main file of the project.
        ./src/command_line_parser.c
        ./src/parsed_arguments_collection.c
        ./src/segment_driver_wiringpi.c
        ./src/segment_driver_general.c
        )

include_directories(./inc) # Instruct the compiler where to look for the given header files within this project.

find_library(WIRINGPI_LIBRARIES NAMES wiringPi) # Find the 'WiringPi' package. For CLion, also see: https://youtrack.jetbrains.com/issue/CPP-17322/CLion-doesnt-find-implementations-but-code-compiles-and-executes-fine
target_link_libraries(LED_DEVICE_DRIVER ${WIRINGPI_LIBRARIES} -lbcm2835) # Link against libraries.

target_compile_features(${target} PRIVATE c_std_11) # We are using the newest language standards, so C23.
set_target_properties(${target} PROPERTIES C_EXTENSIONS OFF) # Turn off compiler specific language extensions.

# Set the options for GNU-linke compilers:
target_compile_options(${target} PRIVATE
        # Set all warnings for all the build types.
        $<$<C_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Werror -fno-omit-frame-pointer>
        # Just for macOS, only apply the '-Wall' and '-fno-omit-frame-pointer' to suppress deprecated errors from the compiler.
        $<$<C_COMPILER_ID:AppleClang>: -Wall -fno-omit-frame-pointer>
        # Optimisation for 'Release' mode.
        $<$<AND:$<C_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:Release>>:-O3>
        # Optimisation in 'Debug'.
        $<$<AND:$<C_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:Debug>>:-Og -g>
        )

# Enable the 'Address Sanitizer'.
option(USE_ASAN "Use address sanitizer if available" OFF) # Fancy message. It shows how to turn of the 'Address Sanitizer'.

# Try to find the path of your 'Address Sanitizer'.
execute_process(COMMAND "${CMAKE_C_COMPILER}" -print-file-name=libasan.so
        OUTPUT_VARIABLE LIBASAN_PATH
        RESULT_VARIABLE ASAN_RESULT
        OUTPUT_STRIP_TRAILING_WHITESPACE)

set(HAS_ASAN FALSE)

# Check if the path of the 'Address Sanitizer' is found.
if (USE_ASAN AND (${ASAN_RESULT} EQUAL 0) AND (NOT ${LIBASAN_PATH} STREQUAL ""))
    message("libasan found @${LIBASAN_PATH}") # Show the path of the sanitizer.
    message("To disable the address sanitizer set USE_ASAN to OFF.\n") # Show how to turn off the address sanitizer.
    set(HAS_ASAN TRUE) # Now, your sanitizer is enabled.
endif ()

if (HAS_ASAN AND USE_ASAN)
    target_compile_options(${target} PRIVATE -fsanitize=address) # Set the target compile options for the sanitizer.
    target_link_options(${target} PRIVATE -fsanitize=address) # The link options for the sanitizer.
endif ()
