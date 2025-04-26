cmake_minimum_required(VERSION 3.16)
project(DepAnalyzer)

set(CMAKE_CXX_STANDARD 17)

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)
find_package(Threads REQUIRED)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_subdirectory(src)
add_subdirectory(tests)
