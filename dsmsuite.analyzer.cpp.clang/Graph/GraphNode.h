#pragma once
#include "INode.h"

class GraphNode : public INode {
public:
    GraphNode(int id, std::string name, int parentId);

    int getId() const override;
    std::string getName() const override;
    int getParentId() const override;
    void addChild(std::shared_ptr<INode> child) override;
    const std::vector<std::shared_ptr<INode>>& getChildren() const override;

private:
    int id_;
    std::string name_;
    int parentId_;
    std::vector<std::shared_ptr<INode>> children_;
};
