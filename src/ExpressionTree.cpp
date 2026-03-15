#include "ExpressionTree.h"
#include "helpers/ExpressionConverter.h"

std::unordered_map<char, int> ExpressionTree::s_symbolPriorityMap = {
            {'+',1},{'-',1},
            {'*',2},{'/',2},
            {'^',3}
};
char ExpressionTree::s_reservedNodeSymbol = ';';

ExpressionTree::ExpressionTree(std::string expression)
{
    this->m_Expression.reserve(expression.length());
    ExpressionConverter::ConvertExpressionNumbersToLetters(expression);

    for (size_t i = 0; i < expression.length(); i++)
    {
        this->m_Expression.push_back(expression[i]);
    }

    this->GenerateTree();
}

void ExpressionTree::PrintAllLeft()
{
    std::shared_ptr<Node> tempTop = this->m_TreeTop;

    while (tempTop != nullptr)
    {
        std::cout << tempTop->symbol;
        tempTop = tempTop->pLeftNode;
    }
}

void ExpressionTree::GenerateTree()
{
    size_t highest_priority_symbol_index = 0;
    int current_highest_priority = -1;


    while (m_Expression.size() > 1)
    {
        for (size_t i = this->m_Expression.size() - 1; i > 0; i--) // We start right to left read so that if all have same prio the left one will be last
        {
            if (std::ispunct(this->m_Expression[i]) && this->m_Expression[i] != ExpressionTree::s_reservedNodeSymbol)
            {
                int symbol_priority = ExpressionTree::s_symbolPriorityMap[this->m_Expression[i]];
                if (symbol_priority >= current_highest_priority) // we check for `=` too bcz we read right to left and if they are both same prio we pick left one
                {
                    current_highest_priority = symbol_priority;
                    highest_priority_symbol_index = i;
                }
            }
        }

        this->ApplyOperation(highest_priority_symbol_index);

        current_highest_priority = -1;
    }
}

void ExpressionTree::ApplyOperation(size_t symbol_index)
{


    size_t expression_length = this->m_Expression.size();

    if (!(symbol_index + 1 >= expression_length && symbol_index - 1 < 0))
    {
        auto newTop = std::make_shared<Node>();
        newTop->symbol = this->m_Expression[symbol_index];

        auto right = ExpressionTree::s_reservedNodeSymbol == this->m_Expression[symbol_index + 1] ? this->m_TreeTop : std::make_shared<Node>(Node{ this->m_Expression[symbol_index + 1] });
        auto left = ExpressionTree::s_reservedNodeSymbol == this->m_Expression[symbol_index - 1] ? this->m_TreeTop : std::make_shared<Node>(Node{ this->m_Expression[symbol_index - 1] });

        newTop->pLeftNode = left;
        newTop->pRightNode = right;

        this->m_TreeTop = newTop;

        this->m_Expression[symbol_index] = ExpressionTree::s_reservedNodeSymbol;

        this->m_Expression.erase((this->m_Expression.begin() + (symbol_index + 1)));
        this->m_Expression.erase((this->m_Expression.begin() + (symbol_index - 1)));
    }
}

