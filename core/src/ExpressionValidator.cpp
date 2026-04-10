#include "ExpressionValidator.h"

std::unordered_map<char, char> ExpressionValidator::s_kAllowedCharacters =
{
    { '+', '+' },
    { '-', '-' },
    { '*', '*' },
    { '/', '/' },
    { '^', '^' },
    { '(', '(' },
    { ')', ')' },
};
std::unordered_map<char, char> ExpressionValidator::s_kExpressionCharacters =
{
    {'+', '+'},
    {'-', '-'},
    {'*', '*'},
    {'/', '/'},
    {'^', '^'}
};

size_t ExpressionValidator::s_ExpressionCharacterLimit = 0;

bool ExpressionValidator::IsExpressionValid(const std::string& expression, std::string& reason)
{
    if (ExpressionValidator::IsExpressionEmpty(expression))
    {
        reason = "Expression cannot be empty.";
        return false;
    }

    char out_invalid_symbol;
    if (!ExpressionValidator::IsExpressionContainingInvalidSymbols(expression, out_invalid_symbol))
    {
        reason = "Expression contains invalid character: " + std::string(1, out_invalid_symbol);
        return false;
    }

    if (!ExpressionValidator::IsExpressionParathesisUseValid(expression))
    {
        reason = "All parathesis must be closed";
        return false;
    }

    if (!ExpressionValidator::IsExpressionContainingNotValidOperations(expression))
    {
        reason = "You cannot have expression with no left or right operands: ";
        return false;
    }
    
    if (!ExpressionValidator::ValidateExpressionVariableLimit(expression))
    {
        reason = "Expression variable limit reached";
        return false;
    }

    return true;
}

void ExpressionValidator::SetExpressionCharacterLimit(size_t limit)
{
    s_ExpressionCharacterLimit = limit;
}

bool ExpressionValidator::IsExpressionEmpty(const std::string& expression)
{
    return expression.empty();
}

bool ExpressionValidator::IsExpressionContainingInvalidSymbols(const std::string& expression,char& out_invalid_symbol)
{
    for (size_t i = 0; i < expression.size(); i++)
    {
        if (std::ispunct(expression[i]) && s_kAllowedCharacters.find(expression[i]) == s_kAllowedCharacters.end())
        {
            out_invalid_symbol = expression[i];
            return false;
        }
    }

    return true;
}

bool ExpressionValidator::IsExpressionParathesisUseValid(const std::string& expression)
{
    size_t left_parathesis_counter = 0, right_parathesis_counter = 0;

    for (size_t i = 0; i < expression.size(); i++)
    {
        if (expression[i] == '(')
        {
            left_parathesis_counter++;
        }
        else if (expression[i] == ')')
        {
            right_parathesis_counter++;
        }
    }

    return left_parathesis_counter == right_parathesis_counter;
}

bool ExpressionValidator::IsExpressionContainingNotValidOperations(const std::string& expression)
{
    for (size_t i = 0; i < expression.size(); i++)
    {
        if (s_kExpressionCharacters.find(expression[i]) != s_kExpressionCharacters.end())
        {
            int left_character = i - 1;
            int right_character = i + 1;

            bool isLeftCharacterValidOperand = left_character > 0 && (!std::ispunct(expression[left_character] || expression[left_character] == ')'));
            bool isRightCharacterValidOperand = right_character < expression.size() && (!std::ispunct(expression[right_character]) || expression[right_character] == '(');

            if (!(isLeftCharacterValidOperand || isRightCharacterValidOperand))
            {
                return false;
            }
        }
    }
    return true;
}

bool ExpressionValidator::ValidateExpressionVariableLimit(const std::string& expression)
{
    size_t variable_counter = 0;
 
    for (size_t i = 0; i < expression.size(); i++)
    {
        if (std::isalnum(expression[i]) || !std::ispunct(expression[i]))
        {
            variable_counter++;
        }
    }

    return variable_counter <= s_ExpressionCharacterLimit;
}
