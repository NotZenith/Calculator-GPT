#include "BatteryManager.h"

BatteryManager::BatteryManager()
    : _voltage(0), _percentage(0), _isLow(false), _isCriticallyLow(false) {}

void BatteryManager::begin() {
    analogReadResolution(12);
    analogSetAttenuation(ADC_11db);
    pinMode(BATTERY_PIN, INPUT);
    update(); // Initial reading
}

void BatteryManager::update() {
    // Average 16 samples for stability
    float sum = 0;
    for (int i = 0; i < 16; i++) {
        sum += analogRead(BATTERY_PIN);
        delay(1);
    }
    float avgAdc = sum / 16.0f;

    // Convert to voltage
    _voltage = (avgAdc * ADC_REFERENCE / ADC_MAX) * VOLTAGE_DIVIDER_RATIO;
    _voltage = constrain(_voltage, VOLTAGE_MIN, VOLTAGE_MAX);

    // Convert to percentage
    _percentage = (int)(((_voltage - VOLTAGE_MIN) / (VOLTAGE_MAX - VOLTAGE_MIN)) * 100.0f);
    _percentage = constrain(_percentage, 0, 100);

    // Status checks
    _isLow = (_voltage <= LOW_BATTERY_THRESHOLD);
    _isCriticallyLow = (_voltage <= VOLTAGE_MIN + 0.05f);
}
