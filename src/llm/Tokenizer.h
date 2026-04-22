#ifndef DSI_PROJECT_TOKENIZER_H
#define DSI_PROJECT_TOKENIZER_H

#include <string>
#include <vector>
#include "llama.h"

class Tokenizer {

public:
    explicit Tokenizer(const llama_vocab* vocab);

    std::vector<int> tokenize_string(const std::string& text) const;

    std::string tkn_id_to_str(int tkn_id) const;

    int get_sz_vocab() const;

private:
    const llama_vocab* vocab;
    int sz_vocab;

};

#endif //DSI_PROJECT_TOKENIZER_H
