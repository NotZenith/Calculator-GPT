#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H

#include <Adafruit_MCP23X17.h>
#include "Config.h"
#include "KeyMap.h"

class KeyboardManager {
public:
    KeyboardManager();
    void begin();

    // Returns a raw key identifier if pressed, else empty string
    String scan();

    // State management
    bool isShiftActive() const { return _shiftActive; }
    bool isSymbolLayer() const { return _symbolLayer; }

    // Process input and update internal state
    void handleSpecialKeys(const String& key);

private:
    Adafruit_MCP23X17 _mcp;
    unsigned long _lastPressTime;
    String _lastKey;

    bool _shiftActive;
    bool _symbolLayer;

    String getMappedKey(int row, int col);
};

#endif // KEYBOARD_MANAGER_H
