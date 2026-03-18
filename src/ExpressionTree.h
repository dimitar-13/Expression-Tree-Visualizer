#pragma once

#include "TreeNode.h"
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <iterator>


class ExpressionTree
{
public:
    ExpressionTree(std::string expression);

    const std::shared_ptr<Node> GetTreeTop()const { return m_TreeTop; }  
    void PrintPostfix();
    void PrintPrefix();
private:
    void PrintNodeLeftFirst(std::shared_ptr<Node> node_to_print);
    void PrintNodeRightFirst(std::shared_ptr<Node> node_to_print);

    void GenerateTree();
    void ApplyOperation(size_t symbol_index, bool remove_prentices = false);
private:
    std::vector<char> m_Expression;
    std::shared_ptr<Node> m_TreeTop = nullptr;

private:
    static std::unordered_map<char, int> s_symbolPriorityMap;
    static char s_reservedNodeSymbol;
    static int s_PriorityMax;
    static int s_PriorityMin;

};