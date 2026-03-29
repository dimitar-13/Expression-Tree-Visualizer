#include "ExpressionTree.h"
#include "helpers/ExpressionConverter.h"
#include <stack>
#include "ExpressionTreeBuilder.h"

ExpressionTree::ExpressionTree()
{
 
}

void ExpressionTree::PrintPostfix()
{
    PrintNodeLeftFirst(this->m_TopNodes.front());
}

void ExpressionTree::PrintPrefix()
{
    PrintNodeRightFirst(this->m_TopNodes.front());
}

std::shared_ptr<StateRecordable> ExpressionTree::RecordState()
{
    auto newState = std::make_shared<ExpressionTree>(*this);

    return newState;
}

void ExpressionTree::AddFullNode(char left_operant, char operation, char right_operant)
{
    auto newTop = std::make_shared<Node>(Node{ operation });
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    bool isLeftPopped = false;

    if (left_operant == ' ')
    {
        auto topNode = this->m_TopNodes.front();
        m_TopNodes.pop();
        left = topNode;
        isLeftPopped = true;
    }
    else
    {
        left = std::make_shared<Node>(Node{ left_operant });
    }

    if (right_operant == ' ')
    {
        auto topNode = this->m_TopNodes.front();
        m_TopNodes.pop();
        right = topNode;
    }
    else
    {
        right = std::make_shared<Node>(Node{ right_operant });
    }
    newTop->pLeftNode = left;
    newTop->pRightNode = right;
    m_TopNodes.push(newTop);

    if (isLeftPopped)
    {
        std::stack <std::shared_ptr<Node>> s;
        std::shared_ptr<Node> temp;
        std::shared_ptr<Node> front;

        while (m_TopNodes.size() > 0)
        {
            front = m_TopNodes.front();
            s.push(front);
            m_TopNodes.pop();
        }
      
        while (s.size() > 0)
        {
            m_TopNodes.push(s.top());
            s.pop();
        }
    }
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

