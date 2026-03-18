#include "ExpressionTree.h"
#include "helpers/ExpressionConverter.h"
#include <stack>

std::unordered_map<char, int> ExpressionTree::s_symbolPriorityMap = {
            {'(',0},
            {'+',1},{'-',1},
            {'*',2},{'/',2},
            {'^',3},
            {')',4}
};
char ExpressionTree::s_reservedNodeSymbol = ';';
int ExpressionTree::s_PriorityMax = 10;
int ExpressionTree::s_PriorityMin = -1;

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

void ExpressionTree::PrintPostfix()
{
    PrintNodeLeftFirst(this->m_TreeTop);
}

void ExpressionTree::PrintPrefix()
{
    PrintNodeRightFirst(this->m_TreeTop);
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

void ExpressionTree::GenerateTree()
{
    size_t highest_priority_symbol_index = 0;
    int current_highest_priority = ExpressionTree::s_PriorityMin;
    char current_highest_priority_symbol = ' ';

    while (m_Expression.size() > 1)
    {
        bool contains_prentices = false;

        for (int i = this->m_Expression.size() - 1; i >= 0; i--) // We start right to left read so that if all have same prio the left one will be last
        {

            if (std::ispunct(this->m_Expression[i]) && this->m_Expression[i] != ExpressionTree::s_reservedNodeSymbol)
            {
                
                int symbol_priority = ExpressionTree::s_symbolPriorityMap[this->m_Expression[i]];
                if ((symbol_priority >= current_highest_priority && this->m_Expression[i] != '^')|| 
                    (this->m_Expression[i] == '^' && symbol_priority > current_highest_priority)) // we check for `=` too bcz we read right to left and if they are both same prio we pick left one
                {
                    current_highest_priority = symbol_priority;
                    highest_priority_symbol_index = i;
                    current_highest_priority_symbol = this->m_Expression[i];
                }
            }

            if (this->m_Expression[i] == ')')
            {
                current_highest_priority = ExpressionTree::s_PriorityMin;
                contains_prentices = true;
            }
            else if (this->m_Expression[i] == '(' && current_highest_priority > ExpressionTree::s_PriorityMin)
            {
                current_highest_priority = s_PriorityMax;
            }
        }

        this->ApplyOperation(highest_priority_symbol_index, contains_prentices);

        current_highest_priority = ExpressionTree::s_PriorityMin;
    }
}

void ExpressionTree::ApplyOperation(size_t symbol_index, bool remove_prentices)
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
    symbol_index --;

    if (remove_prentices && this->m_Expression[symbol_index + 1] == ')' && this->m_Expression[symbol_index - 1] == '(')
    {
        this->m_Expression.erase((this->m_Expression.begin() + (symbol_index + 1)));
        this->m_Expression.erase((this->m_Expression.begin() + (symbol_index - 1)));
    }
}

