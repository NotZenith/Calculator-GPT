#include "CalculatorEngine.h"

CalculatorEngine::CalculatorEngine() {}

String CalculatorEngine::evaluate(const String& expression) {
    if (expression.length() == 0) return "";

    // Support for simple A op B (e.g., 12+34)
    char op = 0;
    int opIdx = -1;

    if ((opIdx = expression.indexOf('+')) > 0) op = '+';
    else if ((opIdx = expression.indexOf('-')) > 0) op = '-';
    else if ((opIdx = expression.indexOf('*')) > 0) op = '*';
    else if ((opIdx = expression.indexOf('/')) > 0) op = '/';

    if (opIdx == -1) return expression; // Just a number

    float a = expression.substring(0, opIdx).toFloat();
    float b = expression.substring(opIdx + 1).toFloat();
    float result = 0;

    switch(op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': result = (b != 0) ? a / b : 0; break;
    }

    return String(result);
}
