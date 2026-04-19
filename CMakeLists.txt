cmake_minimum_required(VERSION 3.14)
project(DSI-Project)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm/bin/clang")
set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")

set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/llvm")

set(OpenMP_C_FLAGS "-fopenmp")
set(OpenMP_CXX_FLAGS "-fopenmp")
set(OpenMP_C_LIB_NAMES "omp")
set(OpenMP_CXX_LIB_NAMES "omp")
set(OpenMP_omp_LIBRARY "/opt/homebrew/opt/libomp/lib/libomp.dylib")
include_directories(/opt/homebrew/include)
include_directories(/opt/homebrew/opt/llvm/include)

link_directories(/opt/homebrew/lib)
link_directories(/opt/homebrew/opt/llvm/lib)

add_executable(DSI-Project
        src/llm.cpp
        src/llm.h
        src/utilities/math.cpp
        src/utilities/math.h
        src/handling/Drafter.cpp
        src/handling/Drafter.h
        src/handling/Reviewer.cpp
        src/handling/Reviewer.h
        src/main.cpp
        src/constants.h)

find_package(OpenMP REQUIRED)
find_package(MPI REQUIRED)

target_link_libraries(DSI-Project PRIVATE llama ggml OpenMP::OpenMP_CXX MPI::MPI_CXX)