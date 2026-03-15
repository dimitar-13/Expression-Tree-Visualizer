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

    ExpressionTree testTree("(2*(3+4)*5*(3+4))*3");

    testTree.PrintAllLeft();
}