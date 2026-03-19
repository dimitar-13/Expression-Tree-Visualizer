#include "ExpressionTree.h"
#include "helpers/ExpressionConverter.h"
#include <stack>
#include "ExpressionTreeBuilder.h"

ExpressionTree::ExpressionTree()
{
 
}

void ExpressionTree::PrintPostfix()
{
    PrintNodeLeftFirst(this->m_TreeTop);
}

void ExpressionTree::PrintPrefix()
{
    PrintNodeRightFirst(this->m_TreeTop);
}

std::shared_ptr<StateRecordable> ExpressionTree::RecordState()
{
    auto newState = std::make_shared<ExpressionTree>(*this);

    return newState;
}

void ExpressionTree::AddFullNode(char left_operant, char operation, char right_operant)
{
    auto newTop = std::make_shared<Node>(Node { operation });
    auto left = left_operant == ' ' ? this->m_TreeTop : std::make_shared<Node>(Node{ left_operant });
    auto right = right_operant == ' ' ? this->m_TreeTop : std::make_shared<Node>(Node{ right_operant });
    newTop->pLeftNode = left;
    newTop->pRightNode = right;

    this->m_TreeTop = newTop;
}


void ExpressionTree::PrintNodeLeftFirst(std::shared_ptr<Node> node_to_print)
{
    std::cout << node_to_print->symbol;
    if (node_to_print->pLeftNode != nullptr)
    {
        this->PrintNodeLeftFirst(node_to_print->pLeftNode);
    }
    if (node_to_print->pRightNode != nullptr)
    {
        this->PrintNodeLeftFirst(node_to_print->pRightNode);
    }
}

void ExpressionTree::PrintNodeRightFirst(std::shared_ptr<Node> node_to_print)
{
    std::cout << node_to_print->symbol;
    if (node_to_print->pRightNode != nullptr)
    {
        this->PrintNodeRightFirst(node_to_print->pRightNode);
    }
    if (node_to_print->pLeftNode != nullptr)
    {
        this->PrintNodeRightFirst(node_to_print->pLeftNode);
    }
}

