cmake_minimum_required(VERSION 3.0)
project(Heap)

set(CMAKE_CXX_STANDARD 20)

set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON)

add_subdirectory(contrib/benchmark)
add_executable(bench main.cpp Heap.h MinMaxAndDAryHeap.h)
target_link_libraries(bench benchmark::benchmark)