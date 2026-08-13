/**
 * @file NetworkManager.cpp
 * @brief Logic for WiFi connectivity, scanning, and persistent credential management.
 */

#include "NetworkManager.h"

NetworkManager::NetworkManager() {}

/**
 * @brief Initializes WiFi station mode and NVS preferences.
 */
void NetworkManager::begin() {
    WiFi.mode(WIFI_STA);
    _prefs.begin("wifi", false);
}

/**
 * @brief Attempts to connect to a specific WiFi network with a timeout.
 * Saves successful credentials to NVS.
 */
void NetworkManager::connect(const char* ssid, const char* password) {
    WiFi.begin(ssid, password);

    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < WIFI_CONNECT_TIMEOUT) {
        delay(500);
        Serial.print(".");
    }

    if (isConnected()) {
        _prefs.putString("ssid", ssid);
        _prefs.putString("password", password);
        Serial.println("\nWiFi Connected: " + String(ssid));
    } else {
        Serial.println("\nWiFi Connection Failed");
    }
}

/**
 * @brief Restores WiFi connection using saved credentials from NVS.
 */
void NetworkManager::connectToSaved() {
    String ssid = _prefs.getString("ssid", DEFAULT_WIFI_SSID);
    String password = _prefs.getString("password", DEFAULT_WIFI_PASSWORD);

    if (ssid.length() > 0) {
        connect(ssid.c_str(), password.c_str());
    }
}

/**
 * @brief Scans for available WiFi networks and returns count.
 */
int NetworkManager::scanNetworks() {
    WiFi.disconnect();
    return WiFi.scanNetworks();
}
