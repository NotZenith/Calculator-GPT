#include "NetworkManager.h"

NetworkManager::NetworkManager() {}

void NetworkManager::begin() {
    WiFi.mode(WIFI_STA);
    _prefs.begin("wifi", false);
}

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
        Serial.println("\nWiFi Connected");
    }
}

void NetworkManager::connectToSaved() {
    String ssid = _prefs.getString("ssid", DEFAULT_WIFI_SSID);
    String password = _prefs.getString("password", DEFAULT_WIFI_PASSWORD);

    if (ssid.length() > 0) {
        connect(ssid.c_str(), password.c_str());
    }
}

void NetworkManager::saveAISettings(const String& apiKey, const String& endpoint, const String& model) {
    _prefs.putString("ai_key", apiKey);
    _prefs.putString("ai_url", endpoint);
    _prefs.putString("ai_model", model);
}

int NetworkManager::scanNetworks() {
    WiFi.disconnect();
    return WiFi.scanNetworks();
}
