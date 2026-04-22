#include "UI.h"

UI::UI(const std::string& model_gguf_path) {
    llama_model_params params = llama_model_default_params();
    params.vocab_only = true;
    model = llama_model_load_from_file(model_gguf_path.c_str(), params);
    tokenizer = std::make_unique<Tokenizer>(llama_model_get_vocab(model));
}

UI::~UI() {
    if (model) llama_model_free(model);
}
