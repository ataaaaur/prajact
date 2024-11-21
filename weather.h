// weather.h
#ifndef WEATHER_H
#define WEATHER_H

#include <stdlib.h>
#include <stdio.h>
#include <curl/curl.h>

#define FILE_PATH "C:\\Users\\asras\\OneDrive\\Desktop\\3 sem\\CEW OEL\\rawdata.txt"
#define API_URL "http://api.openweathermap.org/data/2.5/weather?appid=48aa3c8391469b22c4595c940c269bae&q=karachi"

// Structure to store fetched data
struct MemoryStruct {
    char *memory;
    size_t size;
};

// Function declarations
char *fetch_weather_data();
void parse_and_process_weather_data(const char *data);

#endif // WEATHER_H

