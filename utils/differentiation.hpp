#if !defined(DIFFERENTIATION_HPP)
#define DIFFERENTIATION_HPP

#include <map>
#define FUNCTION_COUNT 7

std::map<std::string, std::string> differentiation = {
    {"sin", "cos"},
    {"cos", "(-1)sin"},
    {"tan", "sec(^2)"},
    {"cot", "(-1)cosec(^2)"}
};

const std::string functions[FUNCTION_COUNT] = {
    "cosec",
    "sin",
    "cos",
    "tan",
    "sec",
    "cot",
    "log"
};

#endif // DIFFERENTIATION_HPP
