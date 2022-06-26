#include "parsed_arguments_collection.h"

void initialize_parsed_collection(parsed_collection_t *collection) {
    if (collection == NULL)
        return;

    argument_pair_t* collection_ptr = (argument_pair_t* ) malloc(sizeof(argument_pair_t) * DEFAULT_NUMBER_COLLECTION);

    if (collection_ptr) {
        collection->parsed_arguments_collection = collection_ptr;
        collection->number_of_parsed_arguments = 0;
        collection->size_of_collection = DEFAULT_NUMBER_COLLECTION;
    }
}

void resize_parsed_collection(parsed_collection_t *collection) {
    if (collection == NULL)
        return;

    argument_pair_t* collection_ptr = (argument_pair_t* ) realloc(collection->parsed_arguments_collection, sizeof(argument_pair_t) * collection->size_of_collection * DEFAULT_GROWTH_FACTOR_COLLECTION);

    if (collection_ptr) {
        collection->parsed_arguments_collection = collection_ptr;
        collection->size_of_collection *= DEFAULT_GROWTH_FACTOR_COLLECTION;
    }
}

void destruct_parsed_collection(parsed_collection_t *collection) {
    if (collection == NULL)
        return;

    for (size_t every_collection_item = 0; every_collection_item < collection->number_of_parsed_arguments; every_collection_item++) {
        if (collection->parsed_arguments_collection[every_collection_item].argument != NULL)
            free(collection->parsed_arguments_collection[every_collection_item].argument);
    }

    free(collection->parsed_arguments_collection);

    collection->parsed_arguments_collection = NULL;
    collection->number_of_parsed_arguments = 0;
    collection->size_of_collection = 0;
}

void add_parsed_collection_int(parsed_collection_t *collection, char *long_flag, int argument_value) {
    if (collection == NULL)
        return;

    int* value_ptr = (int* ) malloc(sizeof(int));

    if (value_ptr) {
        *value_ptr = argument_value;

        collection->parsed_arguments_collection[collection->number_of_parsed_arguments].long_flag = long_flag;
        collection->parsed_arguments_collection[collection->number_of_parsed_arguments].argument = value_ptr;

        collection->number_of_parsed_arguments++;
    }

    if (collection->number_of_parsed_arguments >= collection->size_of_collection)
        resize_parsed_collection(collection);
}

void add_parsed_collection_none(parsed_collection_t *collection, char *long_flag) {
    if (collection == NULL)
        return;

    collection->parsed_arguments_collection[collection->number_of_parsed_arguments].long_flag = long_flag;
    collection->parsed_arguments_collection[collection->number_of_parsed_arguments].argument = NULL;

    collection->number_of_parsed_arguments++;

    if (collection->number_of_parsed_arguments >= collection->size_of_collection)
        resize_parsed_collection(collection);
}
