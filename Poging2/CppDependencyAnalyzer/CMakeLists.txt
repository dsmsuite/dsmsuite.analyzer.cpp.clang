cmake_minimum_required(VERSION 3.13)
project(CppDependencyAnalyzer)

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS} ${CLANG_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(CppDependencyAnalyzer src/main.cpp src/DependencyAnalyzer.cpp)

target_include_directories(CppDependencyAnalyzer PRIVATE ${CLANG_INCLUDE_DIRS})
target_link_libraries(CppDependencyAnalyzer PRIVATE clangTooling clangBasic clangAST clangFrontend)