
#include "weather.h"
#include <string.h>
#include <cjson/cJSON.h>

// Function to parse and process weather data using cJSON
void parse_and_process_weather_data(const char *data) {
    // Parse the JSON string
    cJSON *json = cJSON_Parse(data);
    if (!json) {
        fprintf(stderr, "Error before: %s\n", cJSON_GetErrorPtr());
        return;
    }

    // Extract required fields
    cJSON *main = cJSON_GetObjectItemCaseSensitive(json, "main");
    cJSON *wind = cJSON_GetObjectItemCaseSensitive(json, "wind");
    cJSON *visibility = cJSON_GetObjectItemCaseSensitive(json, "visibility");

    double temp = cJSON_GetObjectItem(main, "temp")->valuedouble - 273.15; // Kelvin to Celsius
    int humidity = cJSON_GetObjectItem(main, "humidity")->valueint;
    double wind_speed = cJSON_GetObjectItem(wind, "speed")->valuedouble;
    int visibility_m = visibility->valueint;

    // Open file to store raw data
    FILE *file = fopen(FILE_PATH, "a");
    if (file != NULL) {
        fprintf(file, "Temperature: %.2f °C, ", temp);
        fprintf(file, "Humidity: %d%%, ", humidity);
        fprintf(file, "Wind Speed: %.2f m/s, ", wind_speed);
        fprintf(file, "Visibility: %d meters\n", visibility_m);
        fclose(file);
        printf("Weather data saved to %s\n", FILE_PATH);
    } else {
        perror("Error opening file");
    }

    // Alerts based on conditions
    if (temp > 35) {
        printf("ALERT: Temperature is high (%.2f°C)\n", temp);
        system("notify-send 'Weather Alert' 'High temperature detected!'");
    } else if (temp < 10) {
        printf("ALERT: Temperature is low (%.2f°C)\n", temp);
        system("notify-send 'Weather Alert' 'Low temperature detected!'");
    }

    if (wind_speed > 10) {
        printf("ALERT: High wind speed detected (%.2f m/s)\n", wind_speed);
        system("notify-send 'Weather Alert' 'High wind speed detected!'");
    }

    if (visibility_m < 1000) {
        printf("ALERT: Low visibility detected (%d meters)\n", visibility_m);
        system("notify-send 'Weather Alert' 'Low visibility detected!'");
    }

    // Free memory allocated by cJSON
    cJSON_Delete(json);
}
