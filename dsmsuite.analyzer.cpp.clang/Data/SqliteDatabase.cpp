#include "SqliteDatabase.h"

SqliteDatabase::SqliteDatabase() : db_(nullptr) {}

SqliteDatabase::~SqliteDatabase() {
    if (db_) {
        sqlite3_close(db_);
    }
}

bool SqliteDatabase::connect(const std::string& dbPath) {
    return sqlite3_open(dbPath.c_str(), &db_) == SQLITE_OK;
}

bool SqliteDatabase::execute(const std::string& sql) {
    char* errMsg = nullptr;
    bool success = sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &errMsg) == SQLITE_OK;
    if (errMsg) sqlite3_free(errMsg);
    return success;
}

bool SqliteDatabase::prepare(const std::string& sql, void** stmt) {
    return sqlite3_prepare_v2(db_, sql.c_str(), -1, reinterpret_cast<sqlite3_stmt**>(stmt), nullptr) == SQLITE_OK;
}

bool SqliteDatabase::step(void* stmt) {
    return sqlite3_step(reinterpret_cast<sqlite3_stmt*>(stmt)) == SQLITE_ROW;
}

void SqliteDatabase::finalize(void* stmt) {
    sqlite3_finalize(reinterpret_cast<sqlite3_stmt*>(stmt));
}
