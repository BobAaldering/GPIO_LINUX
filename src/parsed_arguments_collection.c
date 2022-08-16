//
// Copyright © 2022 Bob Aaldering
//

#include "parsed_arguments_collection.h"

// This function initializes the data structure for parsed options.
void initialize_parsed_collection(parsed_collection_t *collection) {
    // Check if there is no NULL pointer passed as argument.
    if (collection == NULL)
        return; // To prevent undefined behavior, return directly.

    argument_pair_t* collection_ptr = (argument_pair_t* ) malloc(sizeof(argument_pair_t) * DEFAULT_NUMBER_COLLECTION); // Allocate memory for the collection.

    // Check if allocating memory succeeded.
    if (collection_ptr) {
        collection->parsed_arguments_collection = collection_ptr; // The pointer to the dynamic memory block.
        collection->number_of_parsed_arguments = 0; // Initial number of options in the collection.
        collection->size_of_collection = DEFAULT_NUMBER_COLLECTION; // The default size of the collection.
    }
}

// This function resizes the data structure that holds the parsed options.
void resize_parsed_collection(parsed_collection_t *collection) {
    // Check if there is no NULL pointer passed as argument.
    if (collection == NULL)
        return; // To prevent undefined behavior, return directly.

    argument_pair_t* collection_ptr = (argument_pair_t* ) realloc(collection->parsed_arguments_collection, sizeof(argument_pair_t) * collection->size_of_collection * DEFAULT_GROWTH_FACTOR_COLLECTION); // Resize the dynamic block of memory, with a growth factor of two.

    // Check if reallocating memory succeeded.
    if (collection_ptr) {
        collection->parsed_arguments_collection = collection_ptr; // The pointer to the dynamic memory block.
        collection->size_of_collection *= DEFAULT_GROWTH_FACTOR_COLLECTION; // New size of the block.
    }
}

// This function releases all resources needed for storing all the parsed options.
void destruct_parsed_collection(parsed_collection_t *collection) {
    // Check if there is no NULL pointer passed as argument.
    if (collection == NULL)
        return; // To prevent undefined behavior, return directly.

    // Now we have to release all the allocated memory for the arguments as well. This holds for every item in the collection.
    for (size_t every_collection_item = 0; every_collection_item < collection->number_of_parsed_arguments; every_collection_item++) {
        // Check if an argument exists.
        if (collection->parsed_arguments_collection[every_collection_item].argument != NULL)
            free(collection->parsed_arguments_collection[every_collection_item].argument); // Release the allocated memory for every argument.
    }

    free(collection->parsed_arguments_collection); // Release the allocated memory.

    collection->parsed_arguments_collection = NULL; // New value of for the 'options' field. To prevent dangling pointers.
    collection->number_of_parsed_arguments = 0; // No options are in the collection anymore.
    collection->size_of_collection = 0; // Size is also zero.
}

// The functions ads an integer option to the collection of parsed arguments/options.
void add_parsed_collection_int(parsed_collection_t *collection, char *long_flag, int argument_value) {
    // Check if there is no NULL pointer passed as argument.
    if (collection == NULL)
        return; // To prevent undefined behavior, return directly.

    int* value_ptr = (int* ) malloc(sizeof(int)); // Allocate memory for an integer argument.

    // Check if allocating has succeeded.
    if (value_ptr) {
        *value_ptr = argument_value; // New value for the pointer (your argument).

        collection->parsed_arguments_collection[collection->number_of_parsed_arguments].long_flag = long_flag; // Assign the long flag.
        collection->parsed_arguments_collection[collection->number_of_parsed_arguments].argument = value_ptr; // The argument.

        collection->number_of_parsed_arguments++; // New item added, so increment the number of parsed options/arguments.
    }

    // Check the current size of the collection, if you exceed its current size we are resizing the collection of parsed options/options.
    if (collection->number_of_parsed_arguments >= collection->size_of_collection)
        resize_parsed_collection(collection); // Resize the collection.
}

// This function adds only a flag to the collection of parsed options/arguments.
void add_parsed_collection_none(parsed_collection_t *collection, char *long_flag) {
    // Check if there is no NULL pointer passed as argument.
    if (collection == NULL)
        return; // To prevent undefined behavior, return directly.

    collection->parsed_arguments_collection[collection->number_of_parsed_arguments].long_flag = long_flag; // Assign the long flag.
    collection->parsed_arguments_collection[collection->number_of_parsed_arguments].argument = NULL; // The argument, in this case 'NULL', because it does not exist.

    collection->number_of_parsed_arguments++; // New item added, so increment the number of parsed options/arguments.

    // Check the current size of the collection, if you exceed its current size we are resizing the collection of parsed options/options.
    if (collection->number_of_parsed_arguments >= collection->size_of_collection)
        resize_parsed_collection(collection); // Resize the collection.
}
