#pragma once

#include <string>
#include <vector>
#include <stack>

std::vector<std::string> tokenize(const std::string& expression);

std::vector<std::string> shuntingYard(std::vector<std::string> tokens);
