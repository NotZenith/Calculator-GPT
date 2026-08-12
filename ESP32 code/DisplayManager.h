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
    int getZoom() const { return _zoomLevel; }

    // UI Feedback
    void showStatus(const String& status, int durationMs = 1000);
    void showBattery(int percent, float voltage, bool isLow);
    void showWiFiProgress(const String& ssid);

    // Interactive UI
    void showMenu(const String& title, const String items[], int count, int selectedIndex);
    void showPasswordInput(const String& title, const String& currentInput, bool masked = true);

    // Stealth Mode
    void setStealth(bool enabled);
    bool isStealth() const { return _stealth; }

private:
    Adafruit_SSD1306 _display;
    String _buffer;
    int _scrollIndex;
    int _zoomLevel;
    bool _stealth;

    void renderLines();
};

#endif // DISPLAY_MANAGER_H
