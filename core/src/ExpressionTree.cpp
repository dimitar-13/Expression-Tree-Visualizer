#include "ExpressionTree.h"
#include "helpers/ExpressionConverter.h"
#include <stack>
#include "ExpressionTreeBuilder.h"

ExpressionTree::ExpressionTree()
{
 
}

const std::string& ExpressionTree::GetPostfix()
{
    if (m_postfixCached.empty())
    {
        GetNodeLeftFirst(this->GetAllActiveNodes().front(), m_postfixCached);
    }

    return m_postfixCached;
}

const std::string& ExpressionTree::GetPrefix()
{
    if (m_prefixCached.empty())
    {
        GetNodeRightFirst(this->GetAllActiveNodes().front(), m_prefixCached);
        std::reverse(m_prefixCached.begin(), m_prefixCached.end());
    }

    return m_prefixCached;
}

size_t ExpressionTree::GetDepth(std::shared_ptr<Node> top_node)
{
    if (this->m_treeDepthCached != 0)
    {
        return m_treeDepthCached;
    }

    auto top_node_to_use = top_node != nullptr ? top_node : this->GetAllActiveNodes().front();

    size_t left_depth = GetDepthLeft(top_node_to_use);
    size_t right_depth = GetDepthRight(top_node_to_use);

    this->m_treeDepthCached = std::max(left_depth, right_depth);

    return m_treeDepthCached;
}

const std::vector<std::shared_ptr<Node>>& ExpressionTree::GetAllActiveNodes() const
{
    if (this->m_AllActiveNodes.empty())
    {
        for (auto node : m_TopNodes)
        {
            if (node != nullptr)
            {
                m_AllActiveNodes.push_back(node);
            }
        }
    }
  
    return m_AllActiveNodes;
}

size_t ExpressionTree::GetDepthLeft(std::shared_ptr<Node> node)
{
    if (node->pLeftNode == nullptr)
    {
        return 1;
    }

    return GetDepthLeft(node->pLeftNode)+1;
}

size_t ExpressionTree::GetDepthRight(std::shared_ptr<Node> node)
{
    if (node->pRightNode == nullptr)
    {
        return 1;
    }

    return GetDepthRight(node->pRightNode) + 1;
}

std::shared_ptr<StateRecordable> ExpressionTree::RecordState()
{
    auto newState = std::make_shared<ExpressionTree>(*this);

    return newState;
}

void ExpressionTree::AddFullNode(char left_operant, char operation, char right_operant)
{
    constexpr size_t kAsciiZero = 48;

    auto newTop = std::make_shared<Node>(Node{ operation });
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    if (std::isdigit(right_operant))
    {
        size_t node_index = static_cast<size_t>(right_operant) - kAsciiZero;
        auto topNode = this->m_TopNodes[node_index];
        right = topNode;
        this->m_TopNodes[node_index].reset();
    }
    else
    {
        right = std::make_shared<Node>(Node{ right_operant });
    }

    if (std::isdigit(left_operant))
    {
        size_t node_index = static_cast<size_t>(left_operant) - kAsciiZero;
        auto topNode = this->m_TopNodes[node_index];
        left = topNode;
        this->m_TopNodes[node_index].reset();
    }
    else
    {
        left = std::make_shared<Node>(Node{ left_operant });
    }

    newTop->pLeftNode = left;
    newTop->pRightNode = right;
    m_TopNodes.push_back(newTop);
}


void ExpressionTree::GetNodeLeftFirst(std::shared_ptr<Node> node_to_print, std::string& out_string)
{
    out_string += node_to_print->symbol;

    if (node_to_print->pLeftNode != nullptr)
    {
        this->GetNodeLeftFirst(node_to_print->pLeftNode, out_string);
    }
    if (node_to_print->pRightNode != nullptr)
    {
        this->GetNodeLeftFirst(node_to_print->pRightNode, out_string);
    }
}

void ExpressionTree::GetNodeRightFirst(std::shared_ptr<Node> node_to_print, std::string& out_string)
{
    out_string += node_to_print->symbol;

    if (node_to_print->pRightNode != nullptr)
    {
        this->GetNodeRightFirst(node_to_print->pRightNode, out_string);
    }
    if (node_to_print->pLeftNode != nullptr)
    {
        this->GetNodeRightFirst(node_to_print->pLeftNode, out_string);
    }

}

