//
// Created by Arthur Gilfanov on 4/22/26.
//

#include "Comm.h"

std::pair<int, MsgTag> Comm::probe_any() {
    MPI_Status status;
    MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    return {status.MPI_SOURCE, static_cast<MsgTag>(status.MPI_TAG)};
}

void Comm::barrier() {
    MPI_Barrier(MPI_COMM_WORLD);
}

int Comm::tag_to_int(const MsgTag tag) {
    return static_cast<int>(tag);
}
