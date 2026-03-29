#include "ExpressionTreeBuilder.h"
#include "helpers/ExpressionConverter.h"

std::unordered_map<char, int> ExpressionTreeBuilder::s_symbolPriorityMap = {
            {'(',0},
            {'+',1},{'-',1},
            {'*',2},{'/',2},
            {'^',3},
            {')',4}
};
char ExpressionTreeBuilder::s_reservedNodeSymbol = ';';
int ExpressionTreeBuilder::s_PriorityMax = 10;
int ExpressionTreeBuilder::s_PriorityMin = -1;

ExpressionTreeBuilder::ExpressionTreeBuilder(std::string expression)
{
    this->m_Tree = std::make_shared<ExpressionTree>();
    this->m_TreeStateManager = std::make_shared<StateManager<ExpressionTree>>(m_Tree);


    this->m_Expression.reserve(expression.length());
    ExpressionConverter::ConvertExpressionNumbersToLetters(expression);

    for (size_t i = 0; i < expression.length(); i++)
    {
        this->m_Expression.push_back(expression[i]);
    }

    this->BuildExpressionTree();
}

void ExpressionTreeBuilder::BuildExpressionTree()
{
    size_t highest_priority_symbol_index = 0;
    int current_highest_priority = ExpressionTreeBuilder::s_PriorityMin;
    char current_highest_priority_symbol = ' ';

    while (m_Expression.size() > 1)
    {
        bool contains_prentices = false;

        for (int i = this->m_Expression.size() - 1; i >= 0; i--) // We start right to left read so that if all have same prio the left one will be last
        {

            if (std::ispunct(this->m_Expression[i]) && this->m_Expression[i] != ExpressionTreeBuilder::s_reservedNodeSymbol)
            {

                int symbol_priority = ExpressionTreeBuilder::s_symbolPriorityMap[this->m_Expression[i]];
                if ((symbol_priority >= current_highest_priority && this->m_Expression[i] != '^') ||
                    (this->m_Expression[i] == '^' && symbol_priority > current_highest_priority)) // we check for `=` too bcz we read right to left and if they are both same prio we pick left one
                {
                    current_highest_priority = symbol_priority;
                    highest_priority_symbol_index = i;
                    current_highest_priority_symbol = this->m_Expression[i];
                }
            }

            if (this->m_Expression[i] == ')')
            {
                current_highest_priority = ExpressionTreeBuilder::s_PriorityMin;
                contains_prentices = true;
            }
            else if (this->m_Expression[i] == '(' && current_highest_priority > ExpressionTreeBuilder::s_PriorityMin)
            {
                current_highest_priority = s_PriorityMax;
            }
        }

        this->ApplyOperation(highest_priority_symbol_index, contains_prentices);

        current_highest_priority = ExpressionTreeBuilder::s_PriorityMin;
    }
}

void ExpressionTreeBuilder::ApplyOperation(size_t symbol_index, bool remove_prentices)
{
    size_t expression_length = this->m_Expression.size();

    if (!(symbol_index + 1 >= expression_length && symbol_index - 1 < 0))
    {
        char leftOperant = ExpressionTreeBuilder::s_reservedNodeSymbol == this->m_Expression[symbol_index - 1] ? ' ' : this->m_Expression[symbol_index - 1];
        char rightOperant = ExpressionTreeBuilder::s_reservedNodeSymbol == this->m_Expression[symbol_index + 1] ? ' ' : this->m_Expression[symbol_index + 1];
        char operation = this->m_Expression[symbol_index];

        this->m_Tree->AddFullNode(leftOperant, operation, rightOperant);

        this->m_Expression[symbol_index] = ExpressionTreeBuilder::s_reservedNodeSymbol;

        this->m_Expression.erase((this->m_Expression.begin() + (symbol_index + 1)));
        this->m_Expression.erase((this->m_Expression.begin() + (symbol_index - 1)));

        this->m_TreeStateManager->SaveState();
    }
    symbol_index--;

    if (remove_prentices && this->m_Expression[symbol_index + 1] == ')' && this->m_Expression[symbol_index - 1] == '(')
    {
        this->m_Expression.erase((this->m_Expression.begin() + (symbol_index + 1)));
        this->m_Expression.erase((this->m_Expression.begin() + (symbol_index - 1)));
    }

}
