# Software Architecture

The project follows a modular object-oriented design:

## Modules
- **DisplayManager**: Handles SSD1306 rendering and UI state.
- **KeyboardManager**: Manages MCP23017 scanning and character mapping.
- **BatteryManager**: Monitors voltage and manages power alerts.
- **NetworkManager**: Handles WiFi connectivity and persistence.
- **AIService**: Generic wrapper for OpenAI-compatible APIs.
- **CalculatorEngine**: Local math evaluator.

## Communication
All managers communicate through the main application loop in `Ai_calc_esp32_code.ino`.
