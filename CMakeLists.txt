cmake_minimum_required(VERSION 3.14)

set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm/bin/clang")
set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")

project(DSI-Project)

set(CMAKE_CXX_STANDARD 20)

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
        src/llm/LLM.cpp
        src/llm/LLM.h
        src/utilities/Math.cpp
        src/utilities/Math.h
        src/processes/handlers/drafter/Drafter.cpp
        src/processes/handlers/drafter/Drafter.h
        src/processes/handlers/target/Target.cpp
        src/processes/handlers/target/Target.h
        src/main.cpp
        src/processes/handlers/orchestrator/Orchestrator.cpp
        src/processes/handlers/orchestrator/Orchestrator.h
        src/processes/handlers/orchestrator/VerificationPool.h
        src/processes/handlers/orchestrator/VerificationPool.cpp
        src/processes/Process.cpp
        src/processes/Process.h
        src/llm/eviction/SlidingWindow.h
        src/llm/eviction/SlidingWindow.cpp
        src/llm/eviction/EvictionKV.h
        src/llm/Tokenizer.h
        src/llm/Tokenizer.cpp
        src/processes/handlers/frontend/Frontend.h
        src/processes/handlers/frontend/Frontend.cpp
        src/session/Session.h
        src/session/Session.cpp
        src/chat/TUI.h
        src/chat/TUI.cpp
        src/comm/Comm.h
        src/comm/Comm.cpp
        src/comm/Protocol.h
        src/comm/Protocol.cpp
)

include(FetchContent)
FetchContent_Declare(
        ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG v6.1.9
)
FetchContent_MakeAvailable(ftxui)

find_package(OpenMP REQUIRED)
find_package(MPI REQUIRED)

target_link_libraries(DSI-Project PRIVATE
        llama ggml
        OpenMP::OpenMP_CXX MPI::MPI_CXX
        ftxui::screen ftxui::dom ftxui::component
)