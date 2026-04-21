//
// Created by Arthur Gilfanov on 4/13/26.
//

#include <memory>
#include <mpi.h>

#include "processes/process.h"
#include "processes/handlers/Drafter.h"
#include "processes/handlers/Orchestrator.h"
#include "processes/handlers/Target.h"

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_size < 3) {
        throw std::runtime_error("World size must be at least 3 as a Drafter, Orchestrator, and Target process are required.");
    }

    /*
     * Need one orchestrator and one drafter, following this every process
     * is an additional target to help with drafter token review
     */
    std::unique_ptr<Process> process;
    switch (world_rank) {
        case 0: process = std::make_unique<Orchestrator>(world_rank); break;
        case 1: process = std::make_unique<Drafter>(world_rank); break;
        default: process = std::make_unique<Target>(world_rank); break;
    }
    process->run();

    MPI_Finalize();
    return 0;
}
