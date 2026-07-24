/**
 * @file Ai_calc_esp32_code.ino
 * @brief Professional AI Calculator Main Orchestrator
 *
 * Reorganized for ESP32-S3 N16R8.
 * Features: Generic AI Service, Multi-layer Keyboard, Battery Monitoring.
 */

#include "Config.h"
#include "Secrets.h"
#include "DisplayManager.h"
#include "KeyboardManager.h"
#include "BatteryManager.h"
#include "NetworkManager.h"
#include "AIService.h"
#include "CalculatorEngine.h"

// System Instances
DisplayManager  display;
KeyboardManager keyboard;
BatteryManager  battery;
NetworkManager  network;
AIService       ai;
CalculatorEngine calc;

// Application State
enum AppMode { MODE_LOCAL, MODE_AI, MODE_WIFI_SCAN };
AppMode currentMode = MODE_LOCAL;
String  inputBuffer = "";
String  lastResult  = "";
bool    isProcessing = false;

void setup() {
    Serial.begin(115200);
    
    // Initialize Hardware
    Wire.begin(I2C_SDA, I2C_SCL);
    display.begin();
    keyboard.begin();
    battery.begin();
    network.begin();
    
    display.showStatus("Waking up...");
    
    // Connect to WiFi
    network.connectToSaved();

    if (network.isConnected()) {
        display.showStatus("WiFi Connected!");
    } else {
        display.showStatus("WiFi Disconnected\nPress SCAN to fix.");
    }

    delay(1000);
    refreshUI();
}

void loop() {
    // 1. Background Tasks
    static unsigned long lastBatteryCheck = 0;
    if (millis() - lastBatteryCheck > 30000) { // Every 30s
        battery.update();
        lastBatteryCheck = millis();
    }

    // 2. Input Handling
    String key = keyboard.scan();
    if (key != "") {
        handleInput(key);
    }
}

void handleInput(String key) {
    // Functional Keys
    if (key == KEY_MODE) {
        currentMode = (currentMode == MODE_LOCAL) ? MODE_AI : MODE_LOCAL;
        inputBuffer = "";
        refreshUI();
        return;
    }

    if (key == KEY_SHIFT || key == KEY_LAYER) {
        keyboard.handleSpecialKeys(key);
        refreshUI();
        return;
    }

    if (key == KEY_SCAN) {
        startWiFiScan();
        return;
    }

    if (key == KEY_BATTERY) {
        display.showBattery(battery.getPercentage(), battery.getVoltage(), battery.isLow());
        delay(3000);
        refreshUI();
        return;
    }

    if (key == KEY_UP) {
        display.scrollUp();
        return;
    }
    
    if (key == KEY_DOWN) {
        display.scrollDown();
        return;
    }

    if (key == KEY_CLEAR) {
        inputBuffer = "";
        refreshUI();
        return;
    }

    if (key == KEY_ZOOM_IN) {
        static int zoom = 1;
        zoom = min(3, zoom + 1);
        display.setZoom(zoom);
        return;
    }

    if (key == KEY_ZOOM_OUT) {
        static int zoom = 1;
        zoom = max(1, zoom - 1);
        display.setZoom(zoom);
        return;
    }

    // Text/Action Keys
    if (key == KEY_BACKSPACE) {
        if (inputBuffer.length() > 0) {
            inputBuffer.remove(inputBuffer.length() - 1);
        }
    } else if (key == KEY_ENTER) {
        processAction();
    } else {
        // Normal character entry
        if (inputBuffer.length() < INPUT_BUFFER_SIZE) {
            inputBuffer += key;
        }
    }

    refreshUI();
}

void processAction() {
    if (inputBuffer.length() == 0) return;

    display.showStatus("Thinking...");

    if (currentMode == MODE_AI) {
        String response = ai.ask(inputBuffer);
        display.setText(response);
        // Wait for user to read or scroll
        return;
    } else {
        String result = calc.evaluate(inputBuffer);
        display.setText(result);
        return;
    }
}

void startWiFiScan() {
    display.showStatus("Scanning WiFi...");
    int n = network.scanNetworks();
    if (n == 0) {
        display.showStatus("No networks found");
    } else {
        display.showStatus(String(n) + " found. Check Serial.");
        // Professional implementation would show a list on OLED
    }
    delay(2000);
    refreshUI();
}

void refreshUI() {
    String header = (currentMode == MODE_AI) ? "[AI MODE]" : "[CALC MODE]";
    if (keyboard.isShiftActive()) header += " (ABC)";
    if (keyboard.isSymbolLayer()) header += " (#&)";

    display.setText(header + "\n" + inputBuffer);
}
