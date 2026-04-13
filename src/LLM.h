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
    std::vector<int> tokenize_string(const std::string& text) const;


    /* Converts token index to its string */
    std::string tkn_id_to_str(int tkn_id) const;


    /* Float vector, index i stores probability of token i being next */
    std::vector<float> get_tkn_probabilities() const;


    /* Returns generated token id but does not add it in */
    int get_next_tkn() const;


    /* Removes last n tokens from context */
    void wipe_last_n_tkns(int n);


    /* Place a single token into context */
    void add_tkn(int tkn_id);


    /* Adds the list of tokens into end of context */
    void add_tkns(std::vector<int>& tkn_ids);


private:

    std::vector<float> get_next_raw_logits();

    llama_model* model;
    llama_context* ctx;
    const llama_vocab* vocab;
    int kv_ind; /* next write position in the KV cache */
};


#endif //DSI_PROJECT_LLM_H