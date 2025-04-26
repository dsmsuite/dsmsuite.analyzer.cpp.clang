#pragma once

#include <string>
#include <memory>
#include "IDatabase.h"

class SqliteSchemaInitializer {
public:
    SqliteSchemaInitializer(std::shared_ptr<IDatabase> db);
    bool initialize();

private:
    std::shared_ptr<IDatabase> db_;
};
