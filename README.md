
# Environmental Monitoring System in C

## Overview
This project implements an integrated environmental monitoring system in C, designed to fetch, process, and analyze real-time environmental data from a free API (OpenWeather). Key functionalities include:
- Fetching real-time weather data (temperature, humidity, wind speed, visibility).
- Storing raw and processed data in separate files.
- Generating real-time alerts based on weather conditions.
- Automating tasks using shell scripts.

## Features
- **Data Fetching**: Retrieves data from OpenWeather API using libcurl.
- **JSON Parsing**: Uses the cJSON library for robust JSON data handling.
- **Alerts**: Displays notifications for critical weather conditions using `notify-send`.
- **Automation**: A shell script automates data fetching and processing tasks every 10 minutes.
- **Modularity**: Organized with header files to improve code readability and maintainability.

## Prerequisites
- **cURL**: To fetch data from the API.
- **cJSON**: For JSON parsing. Install using `sudo apt install libcjson-dev`.
- **notify-send**: For real-time notifications (Linux only).

## Setup
1. Clone this repository to your local machine.
2. Compile the source files using GCC:
   ```bash
   gcc -o fetch_weather_data.out raw_data_main.c weather.c -lcjson -lcurl
   gcc -o process_weather_data.out processed_data_main.c weather_processing.c
   ```
3. Make the shell script executable:
   ```bash
   chmod +x run_weather_automation.sh
   ```
4. Run the shell script to start automation:
   ```bash
   ./run_weather_automation.sh
   ```

## Files
- `weather.h` and `weather_processing.h`: Header files for modularizing code.
- `weather.c`: Handles data fetching and processing.
- `weather_processing.c`: Processes raw data into averaged summaries.
- `run_weather_automation.sh`: Automates data fetching and processing every 10 minutes.
- `rawdata.txt` and `processeddata.txt`: Store raw and processed data, respectively.

## Alerts
- High temperature (> 35°C): Generates a "high temperature" notification.
- Low temperature (< 10°C): Generates a "low temperature" notification.
- High wind speed (> 10 m/s): Alerts about high wind speed.
- Low visibility (< 1000 meters): Warns about low visibility.

## Contributions
Feel free to contribute by adding new features or improving existing ones. Submit a pull request or raise an issue for discussion.

## License
This project is licensed under the MIT License. See the LICENSE file for details.
