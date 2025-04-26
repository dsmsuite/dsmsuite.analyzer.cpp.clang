#include "SqliteGraphRepository.h"
#include "GraphNode.h"
#include "GraphEdge.h"

SqliteGraphRepository::SqliteGraphRepository(std::shared_ptr<IDatabase> db)
    : db_(std::move(db)) {}

bool SqliteGraphRepository::saveNode(const INode& node) {
    std::string sql = "INSERT INTO Node (id, parent_id, loc, detail_id, created) "
                      "VALUES (" +
                      std::to_string(node.getId()) + ", " +
                      std::to_string(node.getParentId()) + ", 0, 0, 1);"; // loc=0, detail_id=0 stub
    return db_->execute(sql);
}

bool SqliteGraphRepository::saveEdge(const IEdge& edge) {
    std::string sql = "INSERT INTO Edge (source_id, target_id, strength, detail_id, created) "
                      "VALUES (" +
                      std::to_string(edge.getSourceId()) + ", " +
                      std::to_string(edge.getTargetId()) + ", 1, " +
                      std::to_string(edge.getTypeId()) + ", 1);";
    return db_->execute(sql);
}

std::vector<std::shared_ptr<INode>> SqliteGraphRepository::loadAllNodes() {
    std::vector<std::shared_ptr<INode>> nodes;
    void* stmt = nullptr;
    if (!db_->prepare("SELECT id, parent_id FROM Node;", &stmt)) return nodes;

    while (db_->step(stmt)) {
        int id = sqlite3_column_int(static_cast<sqlite3_stmt*>(stmt), 0);
        int parentId = sqlite3_column_int(static_cast<sqlite3_stmt*>(stmt), 1);
        auto node = std::make_shared<GraphNode>(id, "Unknown", parentId);
        nodes.push_back(node);
    }

    db_->finalize(stmt);
    return nodes;
}

std::vector<std::shared_ptr<IEdge>> SqliteGraphRepository::loadAllEdges() {
    std::vector<std::shared_ptr<IEdge>> edges;
    void* stmt = nullptr;
    if (!db_->prepare("SELECT source_id, target_id, detail_id FROM Edge;", &stmt)) return edges;

    while (db_->step(stmt)) {
        int src = sqlite3_column_int(static_cast<sqlite3_stmt*>(stmt), 0);
        int tgt = sqlite3_column_int(static_cast<sqlite3_stmt*>(stmt), 1);
        int type = sqlite3_column_int(static_cast<sqlite3_stmt*>(stmt), 2);
        auto edge = std::make_shared<GraphEdge>(src, tgt, type);
        edges.push_back(edge);
    }

    db_->finalize(stmt);
    return edges;
}
