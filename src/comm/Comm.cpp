//
// Created by Arthur Gilfanov on 4/22/26.
//

#include "Comm.h"

void Comm::barrier() {
    MPI_Barrier(MPI_COMM_WORLD);
}

int Comm::tag_to_int(const MsgTag tag) {
    return static_cast<int>(tag);
}
