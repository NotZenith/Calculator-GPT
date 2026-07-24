# Calculator-GPT (ESP32)

**Credit to: Zenith**

Turn a regular scientific calculator into a **WiFi-connected AI device** that can interact with any OpenAI-compatible AI provider.

This project embeds an **ESP32 microcontroller** inside a calculator and adds an **OLED display**, **I/O expansion**, and **battery monitoring** to create a small IoT system.

From the outside it still looks like a normal calculator — but internally it becomes a **connected smart device**.

---

## Features

- **Multi-layer Keyboard:** Type letters (lower/upper) and symbols using the original keypad.
- **AI-Powered:** Query any AI provider (Gemini, OpenAI, Groq, etc.) via an OpenAI-compatible API.
- **Display Responses:** Read long AI responses on a dedicated OLED screen with scrolling support.
- **Local Calculator Mode:** Works as a normal calculator for simple math.
- **Battery Monitoring:** Real-time voltage monitoring and low-battery alerts.
- **Modular Codebase:** Professional, object-oriented C++ structure for easy maintenance.

---

## Hardware Components

- ESP32-S3 (N16R8 recommended)
- MCP23017 I/O Expander
- SSD1306 OLED Display (128x32)
- AMS1117 3.3V Voltage Regulator
- LiPo Battery
- Voltage Divider (for battery monitoring)
- Power Switch
- Casio Calculator Keypad

---

## Hardware Overview

The **ESP32** acts as the main controller.

The **MCP23017** expands the number of GPIO pins so the ESP32 can interact with multiple inputs.

The **SSD1306 OLED display** shows Telegram messages and AI responses.

A **voltage divider** allows the ESP32 to safely measure battery voltage using an analog pin.

---

## Required Libraries

Install these libraries using the Arduino Library Manager:

- WiFi
- HTTPClient
- ArduinoJson
- Adafruit SSD1306
- Adafruit GFX
- Wire
- Adafruit MCP23017, The mcp23017 library link (https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library).
  
---

## Installation

1. Go to the file **ESP32 code** run the code on the **Arduino IDE**.
2. install all the required libraries.
3. Before uploading the firmware, update these parameters in the code:
WIFI_SSID
WIFI_PASSWORD
TELEGRAM_BOT_TOKEN
TELEGRAM_USER_ID
GEMINI_API_KEY
4. Use a **USB to UART Bridg**, connect the wires TX, RX, 3.3v, GND and wire the **pin0** to the **ground** before wiring the positive rail.
5. select the com port for the esp32 then upload the code to the esp32.


