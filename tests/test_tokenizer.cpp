#include <iostream>
#include <cassert>
#include <vector>
#include "../include/shuntingYard.h"
#include "../include/tests.h"

void evaluateTokenizer(std::vector<testCase> cases) {
    for (const auto& tc : cases) {
        std::vector<std::string> result = tokenize(tc.input);

        if (result != tc.expected) {
            std::cerr << "FAILED: " << tc.testName << "\n";
            std::cerr << "Input: " << tc.input << "\n";

            std::cerr << "Expected: ";
            for (std::string token : tc.expected) {
                std::cerr << token << " ";
            }
            std::cerr << "\n";

            std::cerr << "Got: ";
            for (int i = 0; i < result.size(); i++) {
                std::cerr << result[i] << " ";
            }
            std::cerr << "\n\n";
        } else {
            std::cout << "[PASS] " << tc.testName << "\n";
        }
    }
}

void testSimpleArithmetic() {
    std::vector<testCase> cases = {
        {"Addition", "1 + 2", {"1", "+", "2"}},
        {"Subtraction", "1 - 2", {"1", "-", "2"}},
        {"Multiplication", "2 * 2", {"2", "*", "2"}},
        {"Division", "2 / 2", {"2", "/", "2"}},
        {"Parentheses", "(1 + 2) * 3", {"(", "1", "+", "2", ")", "*", "3"}},
        {"Exponent", "2^2", {"2", "^", "2"}},
        {"Multiple digits", "22 + 543", {"22", "+", "543"}},
        {"Floating numbers", "1.2 + 2.5", {"1.2", "+", "2.5"}},
    };

    evaluateTokenizer(cases);
}

void testMathFunctions() {
    std::vector<testCase> cases = {
    {"Sin function", "sin(1 + 2)", {"sin", "(", "1", "+", "2", ")"}},
    {"Cos function", "cos(1 + 2)", {"cos", "(", "1", "+", "2", ")"}},
    {"Tan function", "tan(1 + 2)", {"tan", "(", "1", "+", "2", ")"}},
    {"Max function", "max(1, 2)", {"max", "(", "1", ",", "2", ")"}},
    {"Logarithm function", "log(1 + 2)", {"log", "(", "1", "+", "2", ")"}},
    {"Function and multiplication", "sin(1 + 2) * 3 ", {"sin", "(", "1", "+", "2", ")", "*", "3"}},
    {"Function and multi digit", "sin(35) * sin(45 + 60)", {"sin", "(", "35", ")", "*", "sin", "(", "45", "+", "60", ")"}},
    {"Nested functions", "cos(20 + sin(45))", {"cos", "(", "20", "+", "sin", "(", "45", ")", ")"}},
    };
    
    evaluateTokenizer(cases);
}


void testWhiteSpace() {
    std::vector<testCase> cases = {
        {"Whitespace multiple spaces", "1   +    2", {"1", "+", "2"}},
        {"Whitespace no spaces", "1+2*3", {"1", "+", "2", "*", "3"}},
        {"Whitespacem mixed spacing", "  1+  2 *3 ", {"1", "+", "2", "*", "3"}},
    };
    evaluateTokenizer(cases);
}


void testNegativeNumbers() {
    std::vector<testCase> cases = {
        {"Leading minus handled as operator", "1 - 2", {"1", "-", "2"}},
        {"Negative literal unary expected", "-2 + 3", {"-", "2", "+", "3"}},
        {"Double negative number", "-2 - -3", {"-", "2", "-", "-", "3"}},
    };
    evaluateTokenizer(cases);
}
