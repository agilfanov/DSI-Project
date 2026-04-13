//
// Created by Arthur Gilfanov on 4/12/26.
//

#ifndef DSI_PROJECT_LLM_H
#define DSI_PROJECT_LLM_H
#include <string>
#include <vector>


class LLM {

public:

    LLM(const std::string& model_gguf_path);

    /* Float vector, index i stores probability of token i to be generated*/
    std::vector<float> get_tkn_probabilities();

    /* index of next chosen token */
    int get_next_tkn_id();

    /* Converts token index to its string */
    std::string tkn_id_to_str(int tkn_id);

    /* Removes last n tokens from the kv cache which essentially*/
    void wipe_last_n_tkns_kv_cache(int n);

    /* Adds a new token into the kv cache */
    void insert_tkn_kv_cache(int tkn_id);


private:

    std::vector<float> get_next_raw_logits();


};


#endif //DSI_PROJECT_LLM_H