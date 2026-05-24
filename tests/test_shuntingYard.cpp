#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include "../include/shuntingYard.h"
#include "../include/tests.h"


std::vector<std::string> stackToVector(std::stack<std::string> s) {
    std::vector<std::string> v;

    while (!s.empty()) {
        v.push_back(s.top());
        s.pop();
    }

    std::reverse(v.begin(), v.end());
    return v;
}


void evaluateShuntingYard(std::vector<testCase> cases) {
    for (const auto& tc : cases) {
        std::vector<std::string> result = shuntingYard(tokenize(tc.input));

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


void testShuntingYard() {
    std::vector<testCase> cases = {
        {"Addition only", "1 + 2", {"1", "2", "+"}},
        {"Operator precedence", "1 + 2 * 3", {"1", "2", "3", "*", "+"}},
        {"Leading negative digit", "-5 + 2", {"5", "-", "2", "+"}},
        {"Floating point numbers", "2.2 + 5.5", {"2.2", "5.5", "+"}},
        {"Exponent right associativity", "2 ^ 3 ^ 2", {"2", "3", "2", "^", "^"}},
        {"Parentheses override precedence", "(1 + 2) * 3", {"1", "2", "+", "3", "*"}},
        {"Deep nesting", "(1 + (2 + (3 + 4)))", {"1", "2", "3", "4", "+", "+", "+"}},
        {"Multiple parentheses and operator mix", "(3 + 4) * (5 - 2) ^ 2", {"3", "4", "+", "5", "2", "-", "2", "^", "*"}},
        {"Full operator stress test", "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3", {"3", "4", "2", "*", "1", "5", "-", "2", "3", "^", "^", "/", "+"}},
        {"Single function", "sin(2 / 3 * 5)", {"2", "3", "/", "5", "*", "sin"}},
        {"Nested functions and mixed operatos", "cos(5^5 + 4 * sin(4 * 5))", {"5", "5", "^", "4", "4", "5", "*", "sin", "*", "+", "cos"}},
        {"Operator not preceeding function", "1 sin(0)", {""}},
        {"Function preceeding function", "sin sin(0)", {""}},

        {"Max function", "max(1,2)", {"1", "2", "max"}},
        {"Max mixed expression", "max(1+2,3*4)", {"1", "2", "+", "3", "4", "*", "max"}},
        {"Max nested function", "cos(max(1,2))", {"1", "2", "max", "cos"}},



        {"Multiple digits addition", "12 + 34", {"12", "34", "+"}},
        {"Multiple digits large numbers", "123 + 4567", {"123", "4567", "+"}},
        {"Multiple digits precedence", "12 + 34 * 5", {"12", "34", "5", "*", "+"}},
        {"Multiple digits mixed ops", "12 + 34 * 56 ^ 2", {"12", "34", "56", "2", "^", "*", "+"}},
        {"Multiple digits long chain", "10 + 20 + 30 + 40 * 50 / 60", {"10", "20", "+", "30", "+", "40", "50", "*", "60", "/", "+"}},
        {"Multiple digits parentheses", "(12 + 34) * 56", {"12", "34", "+", "56", "*"}},
        {"Multiple digits nested", "100 + (200 * 300)", {"100", "200", "300", "*", "+"}},
        {"Multiple digits exponent chain", "10 ^ 20 ^ 30", {"10", "20", "30", "^", "^"}},
        {"Multiple digits function", "sin(12 + 34)", {"12", "34", "+", "sin"}},
        {"Multiple digits nested functions", "cos(100 + sin(200))", {"100", "200", "sin", "+", "cos"}},
    };

    evaluateShuntingYard(cases);
}

