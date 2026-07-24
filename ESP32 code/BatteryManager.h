#ifndef BATTERY_MANAGER_H
#define BATTERY_MANAGER_H

#include "Config.h"

class BatteryManager {
public:
    BatteryManager();
    void begin();
    void update();

    float getVoltage() const { return _voltage; }
    int getPercentage() const { return _percentage; }
    bool isLow() const { return _isLow; }
    bool isCriticallyLow() const { return _isCriticallyLow; }

private:
    float _voltage;
    int _percentage;
    bool _isLow;
    bool _isCriticallyLow;

    float readADC();
};

#endif // BATTERY_MANAGER_H
