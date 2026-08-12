/**
 * @file Ai_calc_esp32_code.ino
 * @brief Professional AI Calculator Main Orchestrator
 *
 * Reorganized for ESP32-S3 N16R8.
 * Features: Generic AI Service, Multi-layer Keyboard, Battery Monitoring, Interactive WiFi.
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
enum AppMode { MODE_LOCAL, MODE_AI, MODE_WIFI_SCAN, MODE_WIFI_PWD, MODE_MODEL_SELECT };
AppMode currentMode = MODE_LOCAL;
String  inputBuffer = "";
String  wifiSsid    = "";
int     selectedWifi = 0;
int     selectedModel = 0;
int     numNetworks  = 0;

const char* AI_MODELS[] = {"GPT-4o Mini", "Gemini 1.5", "Claude 3.5"};
const int TOTAL_MODELS = 3;

void setup() {
    Serial.begin(115200);
    
    Wire.begin(I2C_SDA, I2C_SCL);
    display.begin();
    keyboard.begin();
    battery.begin();
    network.begin();

    display.showStatus("Calculator-GPT booting...");
    network.connectToSaved();

    delay(1000);
    refreshUI();
}

void loop() {
    static unsigned long lastBatteryCheck = 0;
    if (millis() - lastBatteryCheck > 60000) {
        battery.update();
        lastBatteryCheck = millis();
    }

    String key = keyboard.scan();
    if (key != "") {
        handleInput(key);
    }
}

void handleInput(String key) {
    // Stealth Mode Toggle (SHIFT + BATTERY)
    if (key == KEY_BATTERY && keyboard.isShiftActive()) {
        display.setStealth(!display.isStealth());
        return;
    }

    // Don't process other keys if in stealth (except to wake up)
    if (display.isStealth()) {
        return;
    }

    // Mode-specific handling
    if (currentMode == MODE_WIFI_SCAN) {
        handleWiFiScanInput(key);
        return;
    }

    if (currentMode == MODE_WIFI_PWD) {
        handleWiFiPwdInput(key);
        return;
    }

    if (currentMode == MODE_MODEL_SELECT) {
        handleModelSelectInput(key);
        return;
    }

    // Main App Functional Keys
    if (key == KEY_MODE) {
        if (keyboard.isShiftActive()) {
            currentMode = MODE_MODEL_SELECT;
        } else {
            currentMode = (currentMode == MODE_LOCAL) ? MODE_AI : MODE_LOCAL;
        }
        inputBuffer = "";
        refreshUI();
        return;
    }

    if (key == KEY_SCAN) {
        startWiFiScan();
        return;
    }

    if (key == KEY_SHIFT || key == KEY_LAYER) {
        keyboard.handleSpecialKeys(key);
        refreshUI();
        return;
    }

    if (key == KEY_BATTERY) {
        display.showBattery(battery.getPercentage(), battery.getVoltage(), battery.isLow());
        delay(3000);
        refreshUI();
        return;
    }

    if (key == KEY_UP) { display.scrollUp(); return; }
    if (key == KEY_DOWN) { display.scrollDown(); return; }
    if (key == KEY_ZOOM_IN) { display.setZoom(display.getZoom() + 1); return; }
    if (key == KEY_ZOOM_OUT) { display.setZoom(display.getZoom() - 1); return; }
    if (key == KEY_CLEAR) { inputBuffer = ""; refreshUI(); return; }

    // Text/Action Keys
    if (key == KEY_BACKSPACE) {
        if (inputBuffer.length() > 0) inputBuffer.remove(inputBuffer.length() - 1);
    } else if (key == KEY_ENTER) {
        processAction();
    } else {
        if (inputBuffer.length() < INPUT_BUFFER_SIZE) inputBuffer += key;
    }
    
    refreshUI();
}

void handleWiFiScanInput(String key) {
    if (key == KEY_UP) {
        selectedWifi = max(0, selectedWifi - 1);
    } else if (key == KEY_DOWN) {
        selectedWifi = min(numNetworks - 1, selectedWifi + 1);
    } else if (key == KEY_ENTER) {
        wifiSsid = network.getSSID(selectedWifi);
        inputBuffer = "";
        currentMode = MODE_WIFI_PWD;
    } else if (key == KEY_CLEAR) {
        currentMode = MODE_LOCAL;
    }

    if (currentMode == MODE_WIFI_SCAN) {
        String ssids[20];
        for(int i=0; i<min(numNetworks, 20); i++) ssids[i] = network.getSSID(i);
        display.showMenu("Select WiFi:", ssids, min(numNetworks, 20), selectedWifi);
    } else {
        refreshUI();
    }
}

void handleModelSelectInput(String key) {
    if (key == KEY_UP) {
        selectedModel = max(0, selectedModel - 1);
    } else if (key == KEY_DOWN) {
        selectedModel = min(TOTAL_MODELS - 1, selectedModel + 1);
    } else if (key == KEY_ENTER) {
        ai.setModel(selectedModel);
        currentMode = MODE_AI;
    } else if (key == KEY_CLEAR || key == KEY_MODE) {
        currentMode = MODE_AI;
    }

    if (currentMode == MODE_MODEL_SELECT) {
        String modelNames[TOTAL_MODELS];
        for(int i=0; i<TOTAL_MODELS; i++) modelNames[i] = String(AI_MODELS[i]);
        display.showMenu("Select Model:", modelNames, TOTAL_MODELS, selectedModel);
    } else {
        refreshUI();
    }
}

void handleWiFiPwdInput(String key) {
    if (key == KEY_ENTER) {
        display.showStatus("Connecting...");
        network.connect(wifiSsid.c_str(), inputBuffer.c_str());
        currentMode = MODE_LOCAL;
        inputBuffer = "";
    } else if (key == KEY_BACKSPACE) {
        if (inputBuffer.length() > 0) inputBuffer.remove(inputBuffer.length() - 1);
    } else if (key == KEY_CLEAR) {
        currentMode = MODE_WIFI_SCAN;
        inputBuffer = "";
    } else if (key != KEY_SHIFT && key != KEY_LAYER && key != KEY_MODE) {
        inputBuffer += key;
    }

    if (currentMode == MODE_WIFI_PWD) {
        display.showPasswordInput("Password:", inputBuffer, !keyboard.isShiftActive());
    } else {
        refreshUI();
    }
}

void startWiFiScan() {
    display.showStatus("Scanning...");
    numNetworks = network.scanNetworks();
    selectedWifi = 0;
    currentMode = MODE_WIFI_SCAN;
    handleWiFiScanInput(""); 
}

void processAction() {
    if (inputBuffer.length() == 0) return;
    display.showStatus("Please wait...");

    if (currentMode == MODE_AI) {
        String response = ai.ask(inputBuffer);
        display.setText(response);
    } else {
        String result = calc.evaluate(inputBuffer);
        display.setText("Result:\n" + result);
    }
}

void refreshUI() {
    String header = (currentMode == MODE_AI) ? "[" + ai.getModelName() + "]" : "[CALC MODE]";
    if (keyboard.isShiftActive()) header += " ^";
    if (keyboard.isSymbolLayer()) header += " #";

    display.setText(header + "\n" + inputBuffer);
}
