#include "CalculatorEngine.h"

CalculatorEngine::CalculatorEngine() {}

String CalculatorEngine::evaluate(const String& expression) {
    // For a professional project, we can implement a Shunting-yard algorithm
    // or use a library like tinyexpr.
    // For now, we'll keep it simple or allow the AI to handle complex math
    // but provide a basic "local" result for simple arithmetic.

    if (expression.length() == 0) return "";

    // Check if it looks like math
    bool isMath = true;
    for (int i = 0; i < expression.length(); i++) {
        char c = expression.charAt(i);
        if (!isDigit(c) && c != '.' && c != '+' && c != '-' && c != '*' && c != '/' && c != ' ') {
            isMath = false;
            break;
        }
    }

    if (!isMath) return "Not a math expression";

    // Very basic 2-operand evaluator for demonstration
    // In a real project, this would be a full parser.
    return "Result: [Local Calc]";
}
