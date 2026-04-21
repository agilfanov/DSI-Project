//
// Created by Arthur Gilfanov on 4/20/26.
//

#ifndef DSI_PROJECT_PROCESS_H
#define DSI_PROJECT_PROCESS_H

#include "../constants.h"

class Process {

public:
    explicit Process(const ProcessRole role, const int rank) : role(role), rank(rank) {}
    virtual ~Process() = default;
    virtual void run() = 0;

protected:
    ProcessRole role;
    int rank;

};



#endif //DSI_PROJECT_PROCESS_H
