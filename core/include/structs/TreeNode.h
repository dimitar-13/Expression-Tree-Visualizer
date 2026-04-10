#pragma once
#include <iostream>
#include <memory>

struct Node
{
	char symbol;
    std::shared_ptr<Node> pLeftNode = nullptr;
    std::shared_ptr<Node> pRightNode = nullptr;

};
