//
// Created by Arthur Gilfanov on 4/12/26.
//

#ifndef DSI_PROJECT_LLM_H
#define DSI_PROJECT_LLM_H
#include <string>
#include <vector>
#include <memory>
#include "llama.h"
#include "eviction/EvictionKV.h"


class LLM {

public:

    static constexpr int CONTEXT_SIZE = 4096;
    static constexpr int BATCH_SIZE = 512;
    static constexpr int GPU_LAYERS = 99;

    LLM(const std::string& model_gguf_path, std::unique_ptr<EvictionKV> eviction);

    ~LLM();

    /* Samples a token from a probability distribution, returns token id and its probability */
    std::pair<int, float> choose_token_and_its_prob(const std::vector<float>& probabilities) const;


    /* Removes last n tokens from context */
    void wipe_last_n_tkns(int n);


    /* Forward pass: adds tokens to context, returns raw logits at the added positions */
    std::vector<std::vector<float>> add_tkns(const std::vector<int>& tkn_ids, bool only_last_logit = true);


private:

    static void fill_batch_at(const llama_batch& batch, int index, int tkn_id, int pos, bool needs_logits);
    void ensure_kv_capacity(int n);

    llama_model* model;
    llama_context* ctx;
    int next_pos;  /* next logical position for RoPE, monotonically increasing */
    int n_cached;  /* number of occupied cells in the KV cache */
    int sz_vocab;
    std::unique_ptr<EvictionKV> eviction;




};


#endif //DSI_PROJECT_LLM_H