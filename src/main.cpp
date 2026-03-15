#include <iostream>
#include "ExpressionTree.h"

int main()
{
    std::cout << "Hello word" << '\n';

    // 3 + 6 * 7
    // 3 + *
    // +

    ExpressionTree testTree("3*5+6*7+5*7+2");

    testTree.PrintAllLeft();
}