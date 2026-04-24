//
// Created by Arthur Gilfanov on 4/20/26.
//

#ifndef DSI_PROJECT_ORCHESTRATOR_H
#define DSI_PROJECT_ORCHESTRATOR_H


#include <vector>

#include "../../process.h"

class Orchestrator : public Process {

public:
    explicit Orchestrator(const int rank, const std::string& model_path)
        : Process(ProcessRole::ORCHESTRATOR, rank), model_path(model_path) {}




    /*
     * What Orchestrator needs to handle:
     *      - Taking in user tokens
     *      - Taking in stop command from user and thus stopping drafter, targets for now, waiting for next
     *      - Take in reviewed and confirmed generated tokens
     *      - Send out confirmed tokens (as the token list here is the source of truth)
     *      - Send confirmed tokens to UI interface
     */

    void run() override;




private:

    /*
     * Contains the entire sequence of tokens in this session that models will have as their context.
     * Therefore, it contains both model generated (and target confirmed) tokens and user input
     *
     * For message passing, will send tkn id along with its index / unique position so that
     * it is idempotent
     *
     */

    std::string model_path;
    std::vector<int> confirmed_tkn_ids;




    void broadcast_tkn_ids();

};



#endif //DSI_PROJECT_ORCHESTRATOR_H
