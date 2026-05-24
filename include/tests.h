#pragma once

#include <string>
#include <vector>

struct testCase {
    std::string testName;
    std::string input;
    std::vector<std::string> expected;
};


void testSimpleArithmetic();
void testMathFunctions();
void testWhiteSpace();
void testNegativeNumbers();
void testShuntingYard();

