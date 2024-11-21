// weather_processing.c
#include "weather_processing.h"
#include <string.h>

// Function to get the current date and time as a string
void get_current_datetime(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}

// Function to read and process data from rawdata.txt
void process_weather_data() {
    FILE *raw_file = fopen(RAW_DATA_FILE, "r");
    FILE *processed_file = fopen(PROCESSED_DATA_FILE, "a");  // Open for appending

    if (!raw_file) {
        perror("Failed to open raw data file");
        return;
    }
    if (!processed_file) {
        perror("Failed to open processed data file");
        fclose(raw_file);
        return;
    }

    double temp_sum = 0, wind_speed_sum = 0, visibility_sum = 0;
    int count = 0;
    double temp, wind_speed;
    int visibility;

    // Buffer to read each line
    char line[256];
    while (fgets(line, sizeof(line), raw_file)) {
        // Parse each line to extract temperature, wind speed, and visibility
        if (sscanf(line, "Temperature: %lf °C, Humidity: %*d%%, Wind Speed: %lf m/s, Visibility: %d meters",
                   &temp, &wind_speed, &visibility) == 3) {
            temp_sum += temp;
            wind_speed_sum += wind_speed;
            visibility_sum += visibility;
            count++;
        }
    }

    if (count > 0) {
        // Calculate averages
        double avg_temp = temp_sum / count;
        double avg_wind_speed = wind_speed_sum / count;
        double avg_visibility = visibility_sum / count;

        // Get current date and time
        char datetime[20];
        get_current_datetime(datetime, sizeof(datetime));

        // Write averaged data with timestamp to processed data file
        fprintf(processed_file, "Date and Time: %s: Average Temperature: %.2f °C, Average Wind Speed: %.2f m/s, Average Visibility: %.0f meters\n\n",
                datetime, avg_temp, avg_wind_speed, avg_visibility);
        printf("Averaged data saved to %s\n", PROCESSED_DATA_FILE);
    } else {
        printf("No data to process.\n");
    }

    // Close files
    fclose(raw_file);
    fclose(processed_file);

    // Delete rawdata.txt after processing
    if (remove(RAW_DATA_FILE) == 0) {
        printf("Raw data file deleted successfully.\n");
    } else {
        perror("Error deleting raw data file");
    }
}

