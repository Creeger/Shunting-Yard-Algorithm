#include <stack>
#include <vector>
#include <cctype>
#include <cstring>
#include <string>
#include "../include/shuntingYard.h"
#include <cstdlib>

bool isNumber(std::string token);
bool isFunction(std::string token);
int precedence(std::string operation);

// TODO: Change the tests such that it only prints the tests that fails and if all passes
// print something along the lines of All tests [PASSED]

std::vector<std::string> tokenize(const std::string& expression) {
    std::vector<std::string> tokens;
    std::string token;

    for (size_t i = 0; i < expression.size(); i++) {
        char c = expression[i];

        // Check white space
        if (std::isspace(static_cast<unsigned char>(c))) {
            continue;

        // Check for number or decimal point
        } else if (std::isdigit(c) || c == '.') {
            while (i < expression.size() && (std::isdigit(expression[i]) || expression[i] == '.')) {          
                token.push_back(expression[i]);
                i++;
            }
            tokens.push_back(token);
            token.clear();
            i--; // Prevent skipping characters

        } else if (isalpha(c)) {
                        
            while (i < expression.size() && (std::isalpha(expression[i]))) {
                token.push_back(expression[i]);
                i++;
            }
        tokens.push_back(token);
        token.clear();
        i--;

        // Operators / parentheses ew
        } else {
            token.push_back(c);
            tokens.push_back(token);
            token.clear();
        }
    }
    return tokens;
}

std::vector<std::string> shuntingYard(std::vector<std::string> tokens) {
    std::vector<std::string> outputStack;
    std::stack<std::string> operatorStack;
    std::string prevToken = "";
    bool firstToken = true;

    for (std::string token : tokens) {

        if (isNumber(token)) {
            if (!firstToken && (isNumber(prevToken) || prevToken == ")")) {
                    return {""};
            }
            outputStack.push_back(token);

        }  else if (isFunction(token)) {
            if (!firstToken && (isNumber(prevToken) || prevToken == ")" || isFunction(prevToken))) {
                    return {""}; 
            }
            operatorStack.push(token);

        } else if (token == "(") {
            operatorStack.push(token);

        } else if (token == ")") {
            while (!operatorStack.empty() && operatorStack.top() != "(") {
                outputStack.push_back(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.pop(); // Pop left parentheses
            if (!operatorStack.empty() && isFunction(operatorStack.top())) {
                outputStack.push_back(operatorStack.top());
                operatorStack.pop();
            }
        } else if (token == ",") {
            while (!operatorStack.empty() && operatorStack.top() != "(") {
                outputStack.push_back(operatorStack.top());
                operatorStack.pop();
            }
        } else {
            while (!operatorStack.empty() && operatorStack.top() != "(" && (precedence(operatorStack.top()) > precedence(token) || precedence(operatorStack.top()) == precedence(token) && token != "^")) {
                outputStack.push_back(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.push(token);
        } 
        prevToken = token;
        firstToken = false;
    }

    while (!operatorStack.empty()) {
        outputStack.push_back(operatorStack.top());
        operatorStack.pop();
    } 
    return outputStack;
}


bool isNumber(std::string token) {
    for (char c : token) {
        if (!isdigit(c) && c != '.') {
            return false;
        }
    }
    return true;
}

bool isFunction(std::string token) {
    for (char c : token) {
        if (!isalpha(c)) {
            return false;
        }
    }
    return true;
}


int precedence(std::string operation) {
    char op = operation[0];
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}


