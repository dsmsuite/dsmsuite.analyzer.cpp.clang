#include "GraphEdge.h"

GraphEdge::GraphEdge(int sourceId, int targetId, int typeId)
    : sourceId_(sourceId), targetId_(targetId), typeId_(typeId) {}

int GraphEdge::getSourceId() const { return sourceId_; }
int GraphEdge::getTargetId() const { return targetId_; }
int GraphEdge::getTypeId() const { return typeId_; }
