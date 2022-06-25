#ifndef LED_DEVICE_DRIVER_SEGMENT_SHOWER_H
#define LED_DEVICE_DRIVER_SEGMENT_SHOWER_H

#include <string.h>

#include "parsed_arguments_collection.h"
#include "gpio_controller.h"

extern void initialize_segment_driver_general();
extern void argument_segment_driver_general(parsed_collection_t* collection);
extern void de_initialize_segment_driver_general();

#endif
