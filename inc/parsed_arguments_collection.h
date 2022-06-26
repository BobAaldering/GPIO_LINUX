#ifndef LED_DEVICE_DRIVER_PARSED_ARGUMENTS_COLLECTION_H
#define LED_DEVICE_DRIVER_PARSED_ARGUMENTS_COLLECTION_H

#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_NUMBER_COLLECTION (10)
#define DEFAULT_GROWTH_FACTOR_COLLECTION (2)

typedef struct argument_pair {
    char* long_flag;
    void* argument;
} argument_pair_t;

typedef struct parsed_collection {
    argument_pair_t* parsed_arguments_collection;
    size_t number_of_parsed_arguments;
    size_t size_of_collection;
} parsed_collection_t;

extern void initialize_parsed_collection(parsed_collection_t* collection);
extern void resize_parsed_collection(parsed_collection_t* collection);
extern void destruct_parsed_collection(parsed_collection_t* collection);

extern void add_parsed_collection_int(parsed_collection_t* collection, char* long_flag, int argument_value);
extern void add_parsed_collection_none(parsed_collection_t* collection, char* long_flag);

#endif
