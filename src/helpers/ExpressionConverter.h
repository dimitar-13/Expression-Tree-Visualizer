#pragma once
#include <string>
#include <queue>

class ExpressionConverter
{
public:
    static void ConvertExpressionNumbersToLetters(std::string& stringToConvert)
    {
        size_t length = stringToConvert.length();
        char startingCharacter = 96; // The character code of `, this symbol is before `a` so we can increment it to get a and etc.

        for (size_t i = 0; i < length; i++)
        {
            if (std::isdigit(stringToConvert[i]))
            {
                stringToConvert[i] = ++startingCharacter;
            }
        }
    }

    static std::queue<std::string> ConvertToOperationQueue(const std::string& expression)
    {
        size_t length = expression.length();

        for (size_t i = 0; i < length; i++)
        {
            if (std::isdigit(expression[i]))
            {

            }
        }
    }

};