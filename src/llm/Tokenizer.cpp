#include "Tokenizer.h"

Tokenizer::Tokenizer(const llama_vocab* vocab)
    : vocab(vocab), sz_vocab(llama_vocab_n_tokens(vocab)) {}

std::vector<int> Tokenizer::tokenize_string(const std::string& text) const {
    std::vector<int> tokens(text.size());
    const int n = llama_tokenize(vocab, text.c_str(), static_cast<int>(text.size()),
                                 tokens.data(), static_cast<int>(tokens.size()), false, true);
    tokens.resize(n);
    return tokens;
}

std::string Tokenizer::tkn_id_to_str(const int tkn_id) const {
    constexpr int buffer_sz = 256;
    char buf[buffer_sz];
    size_t len = llama_token_to_piece(vocab, tkn_id, buf, sizeof(buf), 0, true);
    return {buf, len};
}

int Tokenizer::get_sz_vocab() const {
    return sz_vocab;
}
