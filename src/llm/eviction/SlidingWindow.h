#ifndef DSI_PROJECT_SLIDING_WINDOW_H
#define DSI_PROJECT_SLIDING_WINDOW_H

#include "EvictionKV.h"

class SlidingWindow : public EvictionKV {

public:
    int evict(llama_memory_t memory, int n) override;

};

#endif //DSI_PROJECT_SLIDING_WINDOW_H
