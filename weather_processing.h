#ifndef WEATHER_PROCESSING_H
#define WEATHER_PROCESSING_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RAW_DATA_FILE "rawdata.txt"
#define PROCESSED_DATA_FILE "processeddata.txt"

// Function declarations
void get_current_datetime(char *buffer, size_t size);
void process_weather_data();

#endif // WEATHER_PROCESSING_H
