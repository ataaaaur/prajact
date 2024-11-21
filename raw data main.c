// main.c
#include "weather.h"

int main(void) {
    char *weather_data = fetch_weather_data();

    if(weather_data) {
        parse_and_process_weather_data(weather_data);
        free(weather_data);
    } else {
        printf("Failed to retrieve weather data.\n");
    }

    return 0;
}
