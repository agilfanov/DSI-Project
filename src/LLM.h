//
// Created by Arthur Gilfanov on 4/12/26.
//

#ifndef DSI_PROJECT_LLM_H
#define DSI_PROJECT_LLM_H
#include <string>
#include <vector>
#include "llama.h"


class LLM {

public:

    LLM(const std::string& model_gguf_path);

    ~LLM();

    /* Tokenize a string and decode its tokens */
    std::vector<int> tokenize_string(const std::string& text);

    /* Place a single token into the KV cache */
    void tkn_to_kv_cache(int tkn_id);

    /* Float vector, index i stores probability of token i being next */
    std::vector<float> get_tkn_probabilities();

    /* Get next generated token */
    int get_next_tkn_id();

    /* Converts token index to its string */
    std::string& tkn_id_to_str(int tkn_id);

    /* Removes last n tokens from the KV cache */
    void wipe_last_n_tkns_kv_cache(int n);


private:

    std::vector<float> get_next_raw_logits();

    llama_model* model;
    llama_context* ctx;
    const llama_vocab* vocab;
    int kv_ind; /* next write position in the KV cache */
};


#endif //DSI_PROJECT_LLM_H