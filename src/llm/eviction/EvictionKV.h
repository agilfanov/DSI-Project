#ifndef DSI_PROJECT_EVICTION_KV_H
#define DSI_PROJECT_EVICTION_KV_H

#include "llama.h"

class EvictionKV {

public:
    virtual ~EvictionKV() = default;
    virtual int evict(llama_memory_t memory, int n) = 0;

};

#endif //DSI_PROJECT_EVICTION_KV_H
