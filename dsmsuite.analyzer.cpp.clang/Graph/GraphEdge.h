#pragma once
#include "IEdge.h"

class GraphEdge : public IEdge {
public:
    GraphEdge(int sourceId, int targetId, int typeId);

    int getSourceId() const override;
    int getTargetId() const override;
    int getTypeId() const override;

private:
    int sourceId_;
    int targetId_;
    int typeId_;
};
