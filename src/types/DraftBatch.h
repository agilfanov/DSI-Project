//
// Created by Arthur Gilfanov on 4/23/26.
//

#ifndef DSI_PROJECT_DRAFTBATCH_H
#define DSI_PROJECT_DRAFTBATCH_H

#include <vector>

struct DraftBatch {
    int global_pos_start;
    std::vector<int> tkn_ids;
    std::vector<float> draft_probs;
};

#endif //DSI_PROJECT_DRAFTBATCH_H
