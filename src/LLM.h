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

    /* Returns a unique ptr to a float vector representing the probabilities */
    std::unique_ptr<std::vector<float>> get_tkn_probabilities() const;

    /* Just runs the random choosing to pick one, does not add into context though */
    std::pair<int, float> choose_token_and_its_prob(const std::unique_ptr<std::vector<float>>& probabilities) const;


    /* Removes last n tokens from context */
    void wipe_last_n_tkns(int n);


    /* Place a single token into context */
    void add_tkn(int tkn_id);


    /* Adds the list of tokens into end of context */
    void add_tkns(const std::vector<int>& tkn_ids);


private:

    static void fill_batch_at(const llama_batch& batch, const int index, const int tkn_id, const int pos, const bool needs_logits);

    llama_model* model;
    llama_context* ctx;
    const llama_vocab* vocab;
    int kv_ind; /* next write position in the KV cache */
    int sz_vocab;




};


#endif //DSI_PROJECT_LLM_H