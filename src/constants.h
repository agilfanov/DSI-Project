//
// Created by Arthur Gilfanov on 4/13/26.
//

#ifndef DSI_PROJECT_CONSTANTS_H
#define DSI_PROJECT_CONSTANTS_H

enum class ProcessRole { ORCHESTRATOR, DRAFTER, TARGET };

constexpr int OMP_PARALLEL_THRESHOLD = 10000;
constexpr int LLM_CONTEXT_SIZE = 4096;
constexpr int LLM_BATCH_SIZE = 512;
constexpr int LLM_GPU_LAYERS = 99;
constexpr int DSI_LOOKAHEAD = 4;

#endif //DSI_PROJECT_CONSTANTS_H
