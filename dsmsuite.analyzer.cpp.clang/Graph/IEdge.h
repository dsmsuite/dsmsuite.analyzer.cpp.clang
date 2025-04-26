#pragma once

class IEdge {
public:
    virtual ~IEdge() = default;
    virtual int getSourceId() const = 0;
    virtual int getTargetId() const = 0;
    virtual int getTypeId() const = 0;
};
