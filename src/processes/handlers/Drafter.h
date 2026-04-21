//
// Created by Arthur Gilfanov on 4/13/26.
//

#ifndef DSI_PROJECT_DRAFTER_H
#define DSI_PROJECT_DRAFTER_H

#include "../process.h"

class Drafter : public Process {

public:
    explicit Drafter(const int rank) : Process(ProcessRole::DRAFTER, rank) {}
    void run() override;

private:



};


#endif //DSI_PROJECT_DRAFTER_H