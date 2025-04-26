#pragma once
#include "IDatabase.h"
#include <sqlite3.h>

class SqliteDatabase : public IDatabase {
public:
    SqliteDatabase();
    ~SqliteDatabase() override;

    bool connect(const std::string& dbPath) override;
    bool execute(const std::string& sql) override;
    bool prepare(const std::string& sql, void** stmt) override;
    bool step(void* stmt) override;
    void finalize(void* stmt) override;

private:
    sqlite3* db_;
};
