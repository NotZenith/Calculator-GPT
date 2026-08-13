#include "DisplayManager.h"

DisplayManager::DisplayManager()
    : _display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, SCREEN_RESET),
      _buffer(""), _scrollIndex(0), _zoomLevel(1), _stealth(false) {}

void DisplayManager::begin() {
    if (!_display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    _display.clearDisplay();
    _display.setTextColor(SSD1306_WHITE);
    _display.display();
}

void DisplayManager::clear() {
    _buffer = "";
    _scrollIndex = 0;
    update();
}

void DisplayManager::setText(const String& text) {
    _buffer = text;
    _scrollIndex = 0;
    update();
}

void DisplayManager::appendText(const String& text) {
    _buffer += text;
    update();
}

void DisplayManager::typewrite(const String& text, int speedMs) {
    _buffer = "";
    _scrollIndex = 0;
    for (int i = 0; i < text.length(); i++) {
        _buffer += text[i];
        update();
        delay(speedMs);
        // Quick break if a key is pressed?
        // No, DisplayManager doesn't know about KeyboardManager
    }
}

void DisplayManager::setZoom(int level) {
    _zoomLevel = constrain(level, 1, 3);
    update();
}

void DisplayManager::scrollUp() {
    if (_scrollIndex > 0) {
        _scrollIndex--;
        update();
    }
}

void DisplayManager::scrollDown() {
    _scrollIndex++;
    update();
}

void DisplayManager::update() {
    if (_stealth) {
        _display.clearDisplay();
        _display.display();
        return;
    }
    _display.clearDisplay();
    _display.setTextSize(_zoomLevel);
    _display.setCursor(0, 0);

    // Simple line wrap and scroll logic
    // In a professional project, we calculate line counts based on zoom
    renderLines();

    _display.display();
}

void DisplayManager::setStealth(bool enabled) {
    _stealth = enabled;
    update();
}

void DisplayManager::renderLines() {
    int charsPerLine = 21 / _zoomLevel;
    int linesPerScreen = 4 / _zoomLevel;
    int currentLine = 0;
    int charCount = 0;

    // This is a simplified version of your word wrapping logic
    // but optimized for the scrollIndex
    String tempLine = "";
    int linesSkipped = 0;

    for (int i = 0; i < _buffer.length(); i++) {
        char c = _buffer.charAt(i);

        if (c == '\n' || tempLine.length() >= charsPerLine) {
            if (linesSkipped < _scrollIndex) {
                linesSkipped++;
            } else if (currentLine < linesPerScreen) {
                _display.println(tempLine);
                currentLine++;
            }
            tempLine = (c == '\n') ? "" : String(c);
        } else {
            tempLine += c;
        }

        if (currentLine >= linesPerScreen) break;
    }

    if (currentLine < linesPerScreen && tempLine.length() > 0 && linesSkipped >= _scrollIndex) {
        _display.println(tempLine);
    }
}

void DisplayManager::showStatus(const String& status, int durationMs) {
    _display.clearDisplay();
    _display.setTextSize(1);
    _display.setCursor(0, 0);
    _display.println(status);
    _display.display();
    if (durationMs > 0) delay(durationMs);
}

void DisplayManager::showBattery(int percent, float voltage, bool isLow) {
    _display.clearDisplay();
    _display.setTextSize(1);
    _display.setCursor(0, 0);
    _display.printf("Battery: %d%% (%.2fV)\n", percent, voltage);

    // Draw battery icon
    _display.drawRect(10, 15, 40, 10, SSD1306_WHITE);
    _display.fillRect(50, 17, 3, 6, SSD1306_WHITE);
    int fill = map(percent, 0, 100, 0, 38);
    _display.fillRect(11, 16, fill, 8, SSD1306_WHITE);

    if (isLow) {
        _display.setCursor(0, 24);
        _display.println(F("CRITICAL: LOW POWER"));
    }
    _display.display();
}

void DisplayManager::showWiFiProgress(const String& ssid) {
    _display.clearDisplay();
    _display.setCursor(0, 0);
    _display.println(F("Connecting to:"));
    _display.println(ssid);
    _display.display();
}

void DisplayManager::showMenu(const String& title, const String items[], int count, int selectedIndex) {
    _display.clearDisplay();
    _display.setTextSize(1);
    _display.setCursor(0, 0);
    _display.println(title);

    int startIdx = max(0, selectedIndex - 1);
    for (int i = startIdx; i < min(startIdx + 2, count); i++) {
        _display.print(i == selectedIndex ? "> " : "  ");
        _display.println(items[i]);
    }
    _display.display();
}

void DisplayManager::showPasswordInput(const String& title, const String& currentInput, bool masked) {
    _display.clearDisplay();
    _display.setTextSize(1);
    _display.setCursor(0, 0);
    _display.println(title);

    String displayStr = "";
    if (masked) {
        for (int i = 0; i < currentInput.length(); i++) displayStr += "*";
    } else {
        displayStr = currentInput;
    }

    _display.println(displayStr + "_");
    _display.display();
}
