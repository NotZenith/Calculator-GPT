#include "AIService.h"

AIService::AIService() : _currentModelIdx(0) {}

const char* MODELS[] = {"gpt-4o-mini", "gemini-1.5-flash", "claude-3-haiku"};
const int MODEL_COUNT = 3;

void AIService::setModel(int index) {
    _currentModelIdx = index % MODEL_COUNT;
}

String AIService::getModelName() const {
    return MODELS[_currentModelIdx];
}

String AIService::buildJsonPayload(const String& prompt) {
    DynamicJsonDocument doc(JSON_DOC_SIZE);
    doc["model"] = MODELS[_currentModelIdx];
    if (WiFi.status() != WL_CONNECTED) return "Error: No WiFi";

    // Wake up the HTTP client
    HTTPClient http;
    http.begin(AI_ENDPOINT_URL);

    // Set headers for standard OpenAI-compatible auth
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", String("Bearer ") + AI_API_KEY);

    // Set a reasonable timeout for LLM responses
    http.setTimeout(AI_TIMEOUT_MS);

    String payload = buildJsonPayload(prompt);
    int httpCode = http.POST(payload);

    String response = "Error: Timeout";

    if (httpCode > 0) {
        String rawResponse = http.getString();
        if (httpCode == 200) {
            response = parseResponse(rawResponse);
        } else {
            response = "API Error: " + String(httpCode);
            Serial.println(rawResponse);
        }
    }

    http.end();
    return response;
}

String AIService::buildJsonPayload(const String& prompt) {
    DynamicJsonDocument doc(JSON_DOC_SIZE);
    doc["model"] = MODELS[_currentModelIdx];

    JsonArray messages = doc.createNestedArray("messages");

    JsonObject systemMsg = messages.createNestedObject();
    systemMsg["role"] = "system";
    systemMsg["content"] = AI_SYSTEM_PROMPT;

    JsonObject userMsg = messages.createNestedObject();
    userMsg["role"] = "user";
    userMsg["content"] = prompt;

    String output;
    serializeJson(doc, output);
    return output;
}

String AIService::parseResponse(const String& payload) {
    DynamicJsonDocument doc(JSON_DOC_SIZE);
    DeserializationError error = deserializeJson(doc, payload);

    if (error) return "Error: JSON Parse Fail";

    // Standard OpenAI response path
    if (doc.containsKey("choices")) {
        return doc["choices"][0]["message"]["content"].as<String>();
    }

    // Gemini-specific OpenAI compatibility path if needed
    if (doc.containsKey("candidates")) {
        return doc["candidates"][0]["content"]["parts"][0]["text"].as<String>();
    }

    return "Error: Unknown Format";
}
