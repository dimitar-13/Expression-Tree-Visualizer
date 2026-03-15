#pragma once

#include "TreeNode.h"
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <iterator>

struct CharacterIndexValuePair
{
    char character;
    size_t character_expression_index;
};

class ExpressionTree
{
public:
    ExpressionTree(std::string expression);
    const std::shared_ptr<Node> GetTreeTop()const { return m_TreeTop; }
    
    // Only for testing, needs to be implemented properly
    void PrintAllLeft();
private:
    void GenerateTree();
    void ApplyOperation(size_t symbol_index, bool remove_prentices = false);
private:
    std::vector<char> m_Expression;
    std::shared_ptr<Node> m_TreeTop = nullptr;
    std::vector<std::shared_ptr<Node>> m_nodes;
    static std::unordered_map<char, int> s_symbolPriorityMap;
    static char s_reservedNodeSymbol;
    static int s_PriorityMax;
    static int s_PriorityMin;

};