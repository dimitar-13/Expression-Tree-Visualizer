#pragma once

#include "structs/TreeNode.h"
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <iterator>
#include "States/StateRecordable.h"
#include <queue>
class ExpressionTree : public StateRecordable
{
public:
    ExpressionTree();

    const std::shared_ptr<Node> GetTreeTop()const { return m_TopNodes.front(); }
    const std::queue<std::shared_ptr<Node>>& GetTreeTopNodes()const { return m_TopNodes; }
    bool isTreeConnected()const { return m_TopNodes.size() == 1; }
    const std::shared_ptr<Node> GetTreeBeginNode()const { return m_BeginningNode; }

    std::shared_ptr<StateRecordable> RecordState()override;
    void AddFullNode(char left_operant, char operation, char right_operant);

    void PrintPostfix();
    void PrintPrefix();

private:
    void PrintNodeLeftFirst(std::shared_ptr<Node> node_to_print);
    void PrintNodeRightFirst(std::shared_ptr<Node> node_to_print);
private:
    std::queue<std::shared_ptr<Node>> m_TopNodes;
    std::shared_ptr<Node> m_BeginningNode = nullptr;
};