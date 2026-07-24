#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <WiFi.h>
#include <Preferences.h>
#include "Config.h"
#include "Secrets.h"

class NetworkManager {
public:
    NetworkManager();
    void begin();

    bool isConnected() const { return WiFi.status() == WL_CONNECTED; }
    void connect(const char* ssid, const char* password);
    void connectToSaved();

    // Settings persistence
    void saveAISettings(const String& apiKey, const String& endpoint, const String& model);
    String getAIKey() { return _prefs.getString("ai_key", AI_API_KEY); }
    String getAIEndpoint() { return _prefs.getString("ai_url", AI_ENDPOINT_URL); }
    String getAIModel() { return _prefs.getString("ai_model", AI_MODEL_NAME); }

    // Scan logic
    int scanNetworks();
    String getSSID(int index) { return WiFi.SSID(index); }

private:
    Preferences _prefs;
};

#endif // NETWORK_MANAGER_H
