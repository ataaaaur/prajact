#include "weather.h"
#include <string.h>
#include <cjson/cJSON.h>

// Function to write the fetched weather data
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) {
        fprintf(stderr, "Not enough memory for data fetch\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

// Function to fetch weather data from the API
char *fetch_weather_data() {
    CURL *curl_handle;
    CURLcode res;

    struct MemoryStruct chunk;
    chunk.memory = malloc(1);  // Initial memory allocation
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();

    if (curl_handle) {
        curl_easy_setopt(curl_handle, CURLOPT_URL, API_URL);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl_handle);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            free(chunk.memory);
            chunk.memory = NULL;
        }

        curl_easy_cleanup(curl_handle);
    }

    curl_global_cleanup();
    return chunk.memory;
}

// Function to parse and process weather data
void parse_and_process_weather_data(const char *data) {
    if (!data) {
        fprintf(stderr, "No data provided to parse\n");
        return;
    }

    cJSON *json = cJSON_Parse(data);
    if (!json) {
        fprintf(stderr, "Error parsing JSON: %s\n", cJSON_GetErrorPtr());
        return;
    }

    cJSON *main = cJSON_GetObjectItemCaseSensitive(json, "main");
    cJSON *wind = cJSON_GetObjectItemCaseSensitive(json, "wind");
    cJSON *visibility = cJSON_GetObjectItemCaseSensitive(json, "visibility");

    double temp = cJSON_GetObjectItem(main, "temp")->valuedouble - 273.15; // Kelvin to Celsius
    int humidity = cJSON_GetObjectItem(main, "humidity")->valueint;
    double wind_speed = cJSON_GetObjectItem(wind, "speed")->valuedouble;
    int visibility_m = visibility->valueint;

    FILE *file = fopen(FILE_PATH, "a");
    if (file != NULL) {
        fprintf(file, "Temperature: %.2f °C, Humidity: %d%%, Wind Speed: %.2f m/s, Visibility: %d meters\n",
                temp, humidity, wind_speed, visibility_m);
        fclose(file);
        printf("Weather data saved to %s\n", FILE_PATH);
    } else {
        perror("Error opening file");
    }

    // Alerts for specific weather conditions
    if (temp > 35) {
        printf("ALERT: High temperature detected (%.2f°C)\n", temp);
        system("notify-send 'Weather Alert' 'High temperature detected!'");
    } else if (temp < 10) {
        printf("ALERT: Low temperature detected (%.2f°C)\n", temp);
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

    cJSON_Delete(json);
}
