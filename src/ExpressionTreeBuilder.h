#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "ExpressionTree.h"
#include "States/StateManager.h"

class ExpressionTreeBuilder
{
public:
    ExpressionTreeBuilder(std::string expression);
    const StateManager<ExpressionTree>& GetStateManager()const { return *m_TreeStateManager; }
private:
    void BuildExpressionTree();
    void ApplyOperation(size_t symbol_index, bool remove_prentices);
private:
    std::vector<char> m_Expression;
    std::shared_ptr<ExpressionTree> m_Tree;
    std::unique_ptr<StateManager<ExpressionTree>> m_TreeStateManager;
private:
    static std::unordered_map<char, int> s_symbolPriorityMap;
    static char s_reservedNodeSymbol;
    static int s_PriorityMax;
    static int s_PriorityMin;
};