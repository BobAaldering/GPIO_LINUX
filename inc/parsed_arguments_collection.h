#ifndef LED_DEVICE_DRIVER_PARSED_ARGUMENTS_COLLECTION_H
#define LED_DEVICE_DRIVER_PARSED_ARGUMENTS_COLLECTION_H

#include <stdlib.h> // Include the 'stdlib.h' facilities.
#include <stdio.h> // Include the 'stdio.h' facilities.

#define DEFAULT_NUMBER_COLLECTION (10) // The default number of parsed arguments that the collection of options has.
#define DEFAULT_GROWTH_FACTOR_COLLECTION (2) // The growth factor for the collection of parsed options.

// This represents a parsed argument (based on 'argc' and 'argv'). We are using the long flag identification and a specific argument.
// Note that I am using a 'void' pointer to allow generic types. This field is dynamically allocated too.
typedef struct argument_pair {
    char* long_flag; // The long flag, for instance '--display'.
    void* argument; // The argument with that option.
} argument_pair_t;

// The data structure that holds all the parsed options (uses dynamically allocated memory).
typedef struct parsed_collection {
    argument_pair_t* parsed_arguments_collection; // Pointer to the dynamic allocated memory with parsed options.
    size_t number_of_parsed_arguments; // The number of parsed options in the collection (pointer/field above).
    size_t size_of_collection; // The current size of the collection.
} parsed_collection_t;

extern void initialize_parsed_collection(parsed_collection_t* collection); // This function initializes the data structure for parsed options.
extern void resize_parsed_collection(parsed_collection_t* collection); // This function resizes the data structure that holds the parsed options.
extern void destruct_parsed_collection(parsed_collection_t* collection); // This function releases all resources needed for storing all the parsed options.

extern void add_parsed_collection_int(parsed_collection_t* collection, char* long_flag, int argument_value); // The functions ads an integer option to the collection of parsed arguments/options.
extern void add_parsed_collection_none(parsed_collection_t* collection, char* long_flag); // This function adds only a flag to the collection of parsed options/arguments.

#endif
