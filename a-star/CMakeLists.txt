add_executable(a-star main.cpp src/Node.cpp src/Node.h src/Graph.cpp src/Graph.h)
target_link_libraries(a-star ${SDL2_LINK_LIBRARIES})
