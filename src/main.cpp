//
// Created by Arthur Gilfanov on 4/13/26.
//

#include <memory>
#include <mpi.h>

#include "processes/process.h"
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

    if (world_size < 3) {
        throw std::runtime_error("World size must be at least 3 as a Drafter, Orchestrator, and Target process need");
    }

    /*
     * Need one orchestrator and one drafter, following this every process
     * is an additional target to help with drafter token review
     */
    std::unique_ptr<Process> process;
    switch (world_rank) {
        case 0: process = std::make_unique<Orchestrator>(world_rank, drafter_path); break;
        case 1: process = std::make_unique<Drafter>(world_rank, drafter_path); break;
        default: process = std::make_unique<Target>(world_rank, target_path); break;
    }
    process->run();

    MPI_Finalize();
    return 0;
}
