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

    LLM(const std::string& model_gguf_path, std::unique_ptr<EvictionKV> eviction);

    ~LLM();

    /* Tokenize a string and decode its tokens */
    std::vector<int> tokenize_string(const std::string& text) const;


    /* Converts token index to its string */
    std::string tkn_id_to_str(int tkn_id) const;

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
    const llama_vocab* vocab;
    int next_pos;  /* next logical position for RoPE, monotonically increasing */
    int n_cached;  /* number of occupied cells in the KV cache */
    int sz_vocab;
    std::unique_ptr<EvictionKV> eviction;




};


#endif //DSI_PROJECT_LLM_H