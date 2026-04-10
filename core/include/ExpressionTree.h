#pragma once

#include "structs/TreeNode.h"
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <iterator>
#include "States/StateRecordable.h"
#include <unordered_map>

class ExpressionTree : public StateRecordable
{
public:
    ExpressionTree();

    const std::shared_ptr<Node> GetTreeTop()const { return *(GetAllActiveNodes().end() - 1); }
    const std::vector<std::shared_ptr<Node>>& GetTreeTopNodes()const { return GetAllActiveNodes(); }
    bool isTreeConnected()const { return GetAllActiveNodes().size() == 1; }

    std::shared_ptr<StateRecordable> RecordState()override;
    void AddFullNode(char left_operant, char operation, char right_operant);

    const std::string& GetPostfix();
    const std::string& GetPrefix();
    size_t GetDepth(std::shared_ptr<Node> top_node = nullptr);
private:
    const std::vector<std::shared_ptr<Node>>& GetAllActiveNodes()const;

    size_t GetDepthLeft(std::shared_ptr<Node> node);
    size_t GetDepthRight(std::shared_ptr<Node> node);

    void GetNodeLeftFirst(std::shared_ptr<Node> node_to_print, std::string& out_string);
    void GetNodeRightFirst(std::shared_ptr<Node> node_to_print, std::string& out_string);
private:
    mutable std::vector<std::shared_ptr<Node>> m_AllActiveNodes;
    std::vector<std::shared_ptr<Node>> m_TopNodes;
    size_t m_treeDepthCached = 0;
    std::string m_postfixCached;
    std::string m_prefixCached;
};