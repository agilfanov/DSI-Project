//
// Created by Arthur Gilfanov on 4/23/26.
//

#ifndef DSI_PROJECT_FRONTEND_H
#define DSI_PROJECT_FRONTEND_H

#include "../../process.h"
#include "../../../session/Session.h"
#include "../../../chat/TUI.h"

class Frontend : public Process {

public:
    explicit Frontend(const int rank, const std::string& model_path)
        : Process(ProcessRole::FRONTEND, rank), session(model_path) {}

    void run() override;

private:
    Session session;
    TUI tui;

};

#endif //DSI_PROJECT_FRONTEND_H
