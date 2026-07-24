#include "KeyboardManager.h"

KeyboardManager::KeyboardManager()
    : _lastPressTime(0), _lastKey(""), _shiftActive(false), _symbolLayer(false) {}

void KeyboardManager::begin() {
    if (!_mcp.begin_I2C(MCP_I2C_ADDR)) {
        Serial.println(F("MCP23017 not found"));
        for (;;);
    }

    // Setup rows as input with pullup
    for (int i = 0; i < 6; i++) {
        _mcp.pinMode(ROW_PINS[i], INPUT_PULLUP);
    }

    // Setup columns as output, high by default
    for (int i = 0; i < 9; i++) {
        _mcp.pinMode(COL_PINS[i], OUTPUT);
        _mcp.digitalWrite(COL_PINS[i], HIGH);
    }
}

String KeyboardManager::scan() {
    if (millis() - _lastPressTime < KEY_DEBOUNCE_MS) return "";

    for (int c = 0; c < 9; c++) {
        _mcp.digitalWrite(COL_PINS[c], LOW);

        for (int r = 0; r < 6; r++) {
            if (_mcp.digitalRead(ROW_PINS[r]) == LOW) {
                String key = getMappedKey(r, c);
                if (key != "") {
                    _mcp.digitalWrite(COL_PINS[c], HIGH);
                    _lastPressTime = millis();
                    return key;
                }
            }
        }
        _mcp.digitalWrite(COL_PINS[c], HIGH);
    }
    return "";
}

String KeyboardManager::getMappedKey(int row, int col) {
    const char* keyPtr = _symbolLayer ? SYMBOL_MAP[row][col] : ALPHABET_MAP[row][col];
    if (!keyPtr) return "";

    String key = String(keyPtr);

    // Apply Shift logic for alphabet
    if (!_symbolLayer && _shiftActive && key.length() == 1) {
        char c = key.charAt(0);
        if (c >= 'a' && c <= 'z') {
            key = String((char)(c - 32));
        }
    }

    return key;
}

void KeyboardManager::handleSpecialKeys(const String& key) {
    if (key == KEY_SHIFT) {
        _shiftActive = !_shiftActive;
    } else if (key == KEY_LAYER) {
        _symbolLayer = !_symbolLayer;
    }
}
