add_library(Analysis
    ClangCodeAnalyzer.cpp
    ClangCodeAnalyzer.h
    DependencyVisitor.cpp
    DependencyVisitor.h
    NodeEmitter.cpp
    NodeEmitter.h
)

target_include_directories(Analysis PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Analysis Graph clangTooling clangBasic clangAST clangFrontend)


///


add_library(core
    Analysis/NodeEmitter.cpp
    Analysis/DependencyVisitor.cpp
    Analysis/DependencyFrontendAction.cpp
    Analysis/IncludeTracker.cpp
    Graph/GraphRepositorySqlite.cpp
)

target_link_libraries(core
    clangTooling clangFrontend clangAST clangLex clangBasic
    sqlite3 Threads::Threads
)

add_executable(dep-analyzer Main/Main.cpp)
target_link_libraries(dep-analyzer core)
