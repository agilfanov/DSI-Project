//
// Created by Arthur Gilfanov on 4/13/26.
//

#ifndef DSI_PROJECT_DRAFTER_H
#define DSI_PROJECT_DRAFTER_H

#include <string>
#include "../process.h"

class Drafter : public Process {

public:
    explicit Drafter(const int rank, const std::string& model_path)
        : Process(ProcessRole::DRAFTER, rank), model_path(model_path) {}






    void run() override;

private:
    std::string model_path;

};


#endif //DSI_PROJECT_DRAFTER_H