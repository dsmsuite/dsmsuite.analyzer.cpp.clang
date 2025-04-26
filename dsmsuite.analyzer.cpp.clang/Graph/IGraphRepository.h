#pragma once
#include <memory>
#include <vector>
#include "INode.h"
#include "IEdge.h"

class IGraphRepository {
public:
    virtual ~IGraphRepository() = default;
    virtual bool saveNode(const INode& node) = 0;
    virtual bool saveEdge(const IEdge& edge) = 0;
    virtual std::vector<std::shared_ptr<INode>> loadAllNodes() = 0;
    virtual std::vector<std::shared_ptr<IEdge>> loadAllEdges() = 0;
};
