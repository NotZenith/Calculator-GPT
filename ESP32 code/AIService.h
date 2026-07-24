#ifndef AI_SERVICE_H
#define AI_SERVICE_H

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "Config.h"
#include "Secrets.h"

class AIService {
public:
    AIService();

    // Sends prompt and returns response string
    // This is non-blocking in the sense that it uses timeouts efficiently
    String ask(const String& prompt);

private:
    String buildJsonPayload(const String& prompt);
    String parseResponse(const String& payload);
};

#endif // AI_SERVICE_H
