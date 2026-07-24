#ifndef CALCULATOR_ENGINE_H
#define CALCULATOR_ENGINE_H

#include <Arduino.h>

class CalculatorEngine {
public:
    CalculatorEngine();

    // Evaluates a string like "5+5" and returns result
    // Note: This is a basic implementation. For complex math,
    // one would use an expression parser library.
    String evaluate(const String& expression);
};

#endif // CALCULATOR_ENGINE_H
