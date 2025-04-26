#include "SqliteSchemaInitializer.h"
#include "SchemaSql.h"

SqliteSchemaInitializer::SqliteSchemaInitializer(std::shared_ptr<IDatabase> db)
    : db_(db) {}

bool SqliteSchemaInitializer::initialize() {
    return db_->execute(SchemaSql::createSchema());
}
