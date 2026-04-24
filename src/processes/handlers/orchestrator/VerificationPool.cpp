//
// Created by Arthur Gilfanov on 4/23/26.
//

#include "VerificationPool.h"

void VerificationPool::insert(DraftBatch batch) {
    batch_pq.push(std::move(batch));
}

DraftBatch VerificationPool::next_batch() {
    DraftBatch batch = std::move(const_cast<DraftBatch&>(batch_pq.top()));
    batch_pq.pop();
    return batch;
}

void VerificationPool::clear() {
    batch_pq = {};
}

bool VerificationPool::empty() const {
    return batch_pq.empty();
}

int VerificationPool::size() const {
    return static_cast<int>(batch_pq.size());
}
