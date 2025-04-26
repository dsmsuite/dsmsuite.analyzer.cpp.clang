#include "GraphNode.h"

GraphNode::GraphNode(int id, std::string name, int parentId)
    : id_(id), name_(std::move(name)), parentId_(parentId) {}

int GraphNode::getId() const { return id_; }
std::string GraphNode::getName() const { return name_; }
int GraphNode::getParentId() const { return parentId_; }

void GraphNode::addChild(std::shared_ptr<INode> child) {
    children_.push_back(std::move(child));
}

const std::vector<std::shared_ptr<INode>>& GraphNode::getChildren() const {
    return children_;
}
