#include <iostream>
#include "ExpressionTree.h"

int main()
{
    std::cout << "Hello word" << '\n';

    // 3 + 6 * 7
    // 3 + *
    // +

    // (3 + 6)*8+(3+7)
    //


    // (1+2)*3
    // (a+b)*c
    // 

    ExpressionTree testTree("1-3*5^7");

    testTree.PrintPostfix();

    std::cout << '\n';

    testTree.PrintPrefix();
}