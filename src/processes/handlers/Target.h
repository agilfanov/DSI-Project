//
// Created by Arthur Gilfanov on 4/13/26.
//

#ifndef DSI_PROJECT_TARGET_H
#define DSI_PROJECT_TARGET_H

#include <string>
#include "../process.h"

class Target : public Process {

public:
    explicit Target(const int rank, const std::string& model_path)
        : Process(ProcessRole::TARGET, rank), model_path(model_path) {}
    void run() override;

private:
    std::string model_path;

};


#endif //DSI_PROJECT_TARGET_H