//
// Created by Arthur Gilfanov on 4/20/26.
//

#ifndef DSI_PROJECT_ORCHESTRATOR_H
#define DSI_PROJECT_ORCHESTRATOR_H



#include "../process.h"

class Orchestrator : public Process {

public:
    explicit Orchestrator(const int rank) : Process(ProcessRole::ORCHESTRATOR, rank) {}
    void run() override;

};



#endif //DSI_PROJECT_ORCHESTRATOR_H
