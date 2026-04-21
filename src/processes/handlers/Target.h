//
// Created by Arthur Gilfanov on 4/13/26.
//

#ifndef DSI_PROJECT_TARGET_H
#define DSI_PROJECT_TARGET_H

#include "../process.h"

class Target : public Process {

public:
    explicit Target(const int rank) : Process(ProcessRole::TARGET, rank) {}
    void run() override;

private:

};


#endif //DSI_PROJECT_TARGET_H