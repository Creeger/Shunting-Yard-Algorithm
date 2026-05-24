#include "../include/tests.h"
#include <iostream>


void testTokenizer() {
    testSimpleArithmetic();
    testMathFunctions();
    testWhiteSpace();
    testNegativeNumbers();
}



int main() {
    std::cout << "Tokenizer tests\n";
    testTokenizer();

    std::cout << "\n";

    std::cout << "Shunting Yard tests\n";
    testShuntingYard();
    return 0;
}


