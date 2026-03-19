#include <iostream>
#include "ExpressionTreeBuilder.h"

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

    ExpressionTreeBuilder testTree("1+1+1+1");

    for (size_t i = 0; i < 5; i++)
    {
        auto currentState = testTree.GetStateManager().GetNextState();
        currentState.lock()->PrintPostfix();
        std::cout << '\n';
    }
    std::cout << '\n';

}