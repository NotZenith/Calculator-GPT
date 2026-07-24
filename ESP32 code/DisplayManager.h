#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "Config.h"

class DisplayManager {
public:
    DisplayManager();
    void begin();
    void clear();
    void update();

    // Text rendering
    void setText(const String& text);
    void appendText(const String& text);
    void scrollUp();
    void scrollDown();
    void setZoom(int level);

    // UI Feedback
    void showStatus(const String& status, int durationMs = 1000);
    void showBattery(int percent, float voltage, bool isLow);
    void showWiFiProgress(const String& ssid);

private:
    Adafruit_SSD1306 _display;
    String _buffer;
    int _scrollIndex;
    int _zoomLevel;

    void renderLines();
};

#endif // DISPLAY_MANAGER_H
