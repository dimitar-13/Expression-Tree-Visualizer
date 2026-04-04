#pragma once
#include <string>
#include <unordered_map>

class ExpressionValidator
{
public:
    static bool IsExpressionValid(const std::string& expression, std::string& reason);
private:
    static bool IsExpressionEmpty(const std::string& expression);
    static bool IsExpressionContainingInvalidSymbols(const std::string& expression, char& out_invalid_symbol);
    static bool IsExpressionParathesisUseValid(const std::string& expression);
    static bool IsExpressionContainingNotValidOperations(const std::string& expression);

private:
    static std::unordered_map<char, char> s_kAllowedCharacters;
    static std::unordered_map<char, char> s_kExpressionCharacters;
};