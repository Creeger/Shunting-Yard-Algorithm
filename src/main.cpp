#include "../include/shuntingYard.h"
#include <string>
#include <vector>
#include <iostream>

int main(int argc, char *argv[]) {
    char *expression = argv[1];
    std::vector<std::string> tokens = tokenize(expression)  ;
    
    shuntingYard(tokens);
}
