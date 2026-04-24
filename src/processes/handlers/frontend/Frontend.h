//
// Created by Arthur Gilfanov on 4/23/26.
//

#ifndef DSI_PROJECT_FRONTEND_H
#define DSI_PROJECT_FRONTEND_H

#include "../../process.h"

class Frontend : public Process {

public:
    explicit Frontend(const int rank, const std::string& model_path)
        : Process(ProcessRole::FRONTEND, rank), model_path(model_path) {}

    void run() override;

private:
    std::string model_path;

};

#endif //DSI_PROJECT_FRONTEND_H
