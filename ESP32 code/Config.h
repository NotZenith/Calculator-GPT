#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

/**
 * @file Config.h
 * @brief Hardware pinouts and system-wide constants.
 */

// I2C Configuration
#define I2C_SDA 21
#define I2C_SCL 22

// OLED Display Configuration
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 32
#define OLED_ADDR     0x3C
#define SCREEN_RESET  -1

// Battery Monitoring
#define BATTERY_PIN           34
#define VOLTAGE_DIVIDER_RATIO 2.0f
#define ADC_REFERENCE         3.3f
#define ADC_MAX               4095
#define VOLTAGE_MAX           3.8f
#define VOLTAGE_MIN           2.9f
#define LOW_BATTERY_THRESHOLD 2.92f

// Keypad Configuration (MCP23017)
#define MCP_I2C_ADDR 0x20
const uint8_t ROW_PINS[6] = {0, 1, 2, 3, 4, 5};
const uint8_t COL_PINS[9] = {8, 9, 10, 11, 12, 13, 14, 15, 6};

// UI Settings
#define SCROLL_SPEED_MS      200
#define KEY_DEBOUNCE_MS      150
#define AI_TIMEOUT_MS        15000
#define WIFI_CONNECT_TIMEOUT 10000

// Memory Settings
#define INPUT_BUFFER_SIZE  1024
#define JSON_DOC_SIZE      2048

#endif // CONFIG_H
// Update 1
// Update 2
// Update 3
// Update 4
// Update 5
// Update 6
// Update 7
// Update 8
