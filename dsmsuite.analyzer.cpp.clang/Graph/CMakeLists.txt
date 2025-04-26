# Graph/CMakeLists.txt
add_library(Graph
    GraphNode.cpp
    GraphNode.h
    GraphEdge.cpp
    GraphEdge.h
    IGraphRepository.h
    INode.h
    IEdge.h
)

target_include_directories(Graph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
