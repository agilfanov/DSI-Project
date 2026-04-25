//
// Created by Arthur Gilfanov on 4/22/26.
//

#ifndef DSI_PROJECT_COMM_H
#define DSI_PROJECT_COMM_H

#include <vector>
#include <mpi.h>
#include "Protocol.h"

class Comm {

    friend class Process;

private:

    template<typename T>
    static void send(const std::vector<T>& data, const int dest, const MsgTag tag) {
        MPI_Send(data.data(), static_cast<int>(data.size()), mpi_type<T>(),
                 dest, tag_to_int(tag), MPI_COMM_WORLD);
    }

    template<typename T>
    static std::vector<T> recv(const int source, const MsgTag tag) {
        MPI_Status status;
        MPI_Probe(source, tag_to_int(tag), MPI_COMM_WORLD, &status);

        int count;
        MPI_Get_count(&status, mpi_type<T>(), &count);

        std::vector<T> data(count);
        MPI_Recv(data.data(), count, mpi_type<T>(), source, tag_to_int(tag), MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        return data;
    }

    /* first is rank of who sent it, second is tag */
    static std::pair<int, MsgTag> probe_any();

    static void barrier();

private:

    static int tag_to_int(MsgTag tag);

    template<typename T>
    static MPI_Datatype mpi_type();

};

template<> inline MPI_Datatype Comm::mpi_type<int>() { return MPI_INT; }
template<> inline MPI_Datatype Comm::mpi_type<float>() { return MPI_FLOAT; }
template<> inline MPI_Datatype Comm::mpi_type<char>() { return MPI_CHAR; }

#endif //DSI_PROJECT_COMM_H
