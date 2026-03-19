#pragma once

#include "structs/TreeNode.h"
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <iterator>
#include "States/StateRecordable.h"

class ExpressionTree : public StateRecordable
{
public:
    ExpressionTree();

    const std::shared_ptr<Node> GetTreeTop()const { return m_TreeTop; }  
    std::shared_ptr<StateRecordable> RecordState()override;
    void AddFullNode(char left_operant, char operation, char right_operant);

    void PrintPostfix();
    void PrintPrefix();

private:
    void PrintNodeLeftFirst(std::shared_ptr<Node> node_to_print);
    void PrintNodeRightFirst(std::shared_ptr<Node> node_to_print);
private:
    std::shared_ptr<Node> m_TreeTop = nullptr;
};