#pragma once

#include "IGraphRepository.h"
#include "IDatabase.h"

class SqliteGraphRepository : public IGraphRepository {
public:
    explicit SqliteGraphRepository(std::shared_ptr<IDatabase> db);

    bool saveNode(const INode& node) override;
    bool saveEdge(const IEdge& edge) override;
    std::vector<std::shared_ptr<INode>> loadAllNodes() override;
    std::vector<std::shared_ptr<IEdge>> loadAllEdges() override;

private:
    std::shared_ptr<IDatabase> db_;
};
