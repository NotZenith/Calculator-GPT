#include "AIService.h"

AIService::AIService() {}

String AIService::ask(const String& prompt) {
    if (WiFi.status() != WL_CONNECTED) return "Error: No WiFi";

    HTTPClient http;
    http.begin(AI_ENDPOINT_URL);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", String("Bearer ") + AI_API_KEY);
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
    doc["model"] = AI_MODEL_NAME;

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
