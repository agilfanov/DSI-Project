//
// Created by Arthur Gilfanov on 4/23/26.
//

#ifndef DSI_PROJECT_VERIFICATIONPOOL_H
#define DSI_PROJECT_VERIFICATIONPOOL_H

#include <queue>
#include "../../../types/DraftBatch.h"

class VerificationPool {

public:

    void insert(DraftBatch batch);

    DraftBatch next_batch();

    void clear();

    bool empty() const;

    int size() const;

private:

    struct BatchCompare {
        bool operator()(const DraftBatch& a, const DraftBatch& b) {
            return a.global_pos_start > b.global_pos_start;
        }
    };

    std::priority_queue<DraftBatch, std::vector<DraftBatch>, BatchCompare> batch_pq;

};

#endif //DSI_PROJECT_VERIFICATIONPOOL_H
