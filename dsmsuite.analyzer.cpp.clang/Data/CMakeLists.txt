# Data/CMakeLists.txt
add_library(Data
    IDatabase.h
    SqliteDatabase.cpp
    SqliteDatabase.h
    SqliteSchemaInitializer.cpp
    SqliteSchemaInitializer.h
    SchemaSql.cpp
    SchemaSql.h
)

target_include_directories(Data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Data sqlite3)

------

target_sources(Graph PRIVATE
    SqliteGraphRepository.cpp
    SqliteGraphRepository.h
)

target_link_libraries(Graph Data)  # Depends on IDatabase

