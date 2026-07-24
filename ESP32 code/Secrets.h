#ifndef SECRETS_H
#define SECRETS_H

/**
 * @file Secrets.h
 * @brief User-specific credentials and configuration.
 *
 * Edit this file to configure your WiFi and AI provider.
 */

// WiFi Configuration
#define DEFAULT_WIFI_SSID     "Your_SSID"
#define DEFAULT_WIFI_PASSWORD "Your_Password"

// AI Provider Configuration
// This works with OpenAI, Gemini (OpenAI-compatible), Groq, DeepSeek, etc.
#define AI_API_KEY      "your_api_key_here"
#define AI_ENDPOINT_URL "https://generativelanguage.googleapis.com/v1beta/openai/chat/completions"
#define AI_MODEL_NAME   "gemini-2.0-flash-exp" // or "gpt-4o", "deepseek-chat", etc.

// Optional: System prompt to set the AI's personality
#define AI_SYSTEM_PROMPT "You are a helpful calculator assistant. Keep answers brief."

#endif // SECRETS_H
