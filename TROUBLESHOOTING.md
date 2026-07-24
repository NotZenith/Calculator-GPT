# Troubleshooting Guide

## WiFi Connection Issues
- Ensure your network is 2.4GHz (ESP32 does not support 5GHz).
- Check that the SSID and Password are correct.
- Verify the antenna connection on your ESP32-S3.

## OLED Display Not Working
- Check I2C wiring (SDA/SCL).
- Verify the OLED address in `Config.h` (default is 0x3C).
- Ensure the display is receiving 3.3V.

## AI API Errors
- Check your internet connection.
- Verify your API Key in `Secrets.h` or via the on-device settings.
- Check the API endpoint URL for typos.

## Battery Monitor Inaccurate
- Calibrate the `VOLTAGE_DIVIDER_RATIO` in `Config.h`.
- Ensure the battery pin is connected to the correct ADC pin.
