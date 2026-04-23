#include "Tokenizer.h"

Tokenizer::Tokenizer(const std::string& model_gguf_path) {
    llama_model_params params = llama_model_default_params();
    params.vocab_only = true;
    model = llama_model_load_from_file(model_gguf_path.c_str(), params);
    vocab = llama_model_get_vocab(model);
    sz_vocab = llama_vocab_n_tokens(vocab);
}

Tokenizer::~Tokenizer() {
    if (model) llama_model_free(model);
}

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
