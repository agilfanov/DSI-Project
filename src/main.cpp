//
// Created by Arthur Gilfanov on 4/13/26.
//

#include <memory>
#include <mpi.h>

#include "processes/process.h"
#include "processes/handlers/frontend/Frontend.h"
#include "processes/handlers/drafter/Drafter.h"
#include "processes/handlers/orchestrator/Orchestrator.h"
#include "processes/handlers/target/Target.h"

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (argc < 3) {
        throw std::runtime_error("Format for input needs to be DSI-Project drafter_gguf_path target_gguf_path");
    }

    const std::string drafter_path = argv[1];
    const std::string target_path = argv[2];

    constexpr int NUM_FRONTENDS = 1;
    constexpr int NUM_ORCHESTRATORS = 1;
    constexpr int NUM_DRAFTERS = 1;
    constexpr int MIN_TARGETS = 1;
    constexpr int MIN_WORLD_SIZE = NUM_FRONTENDS + NUM_ORCHESTRATORS + NUM_DRAFTERS + MIN_TARGETS;

    if (world_size < MIN_WORLD_SIZE) {
        throw std::runtime_error("World size must be at least " + std::to_string(MIN_WORLD_SIZE));
    }

    constexpr int ORCHESTRATOR_START = NUM_FRONTENDS;
    constexpr int DRAFTER_START = ORCHESTRATOR_START + NUM_ORCHESTRATORS;
    constexpr int TARGET_START = DRAFTER_START + NUM_DRAFTERS;

    std::unique_ptr<Process> process;
    if (world_rank < ORCHESTRATOR_START) {
        process = std::make_unique<Frontend>(world_rank, drafter_path);
    } else if (world_rank < DRAFTER_START) {
        process = std::make_unique<Orchestrator>(world_rank, drafter_path);
    } else if (world_rank < TARGET_START) {
        process = std::make_unique<Drafter>(world_rank, drafter_path);
    } else {
        process = std::make_unique<Target>(world_rank, target_path);
    }
    process->run();

    MPI_Finalize();
    return 0;
}
