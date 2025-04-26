#pragma once
#include <string>
#include <memory>
#include <vector>

class INode {
public:
    virtual ~INode() = default;
    virtual int getId() const = 0;
    virtual std::string getName() const = 0;
    virtual int getParentId() const = 0;
    virtual void addChild(std::shared_ptr<INode> child) = 0;
    virtual const std::vector<std::shared_ptr<INode>>& getChildren() const = 0;
};
