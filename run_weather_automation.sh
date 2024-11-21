#!/bin/bash

# Script to automate weather data fetching and processing

# Infinite loop to run the application every 10 minutes
while true; do
    # Fetch raw data
    ./fetch_weather_data.out

    # Process raw data into processed data
    ./process_weather_data.out

    # Wait for 10 minutes before the next execution
    sleep 600
done
