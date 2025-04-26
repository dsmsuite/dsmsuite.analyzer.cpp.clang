#pragma once
#include <string>
#include <memory>

class IDatabase {
public:
    virtual ~IDatabase() = default;

    virtual bool connect(const std::string& dbPath) = 0;
    virtual bool execute(const std::string& sql) = 0;
    virtual bool prepare(const std::string& sql, void** stmt) = 0;
    virtual bool step(void* stmt) = 0;
    virtual void finalize(void* stmt) = 0;
};
