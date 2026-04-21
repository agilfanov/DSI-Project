//
// Created by Arthur Gilfanov on 4/12/26.
//
#include "../LLM.h"
#include "../constants.h"
#include "ggml-backend.h"
#include "../utilities/Math.h"

LLM::LLM(const std::string& model_gguf_path) {
    model = nullptr;
    ctx = nullptr;
    vocab = nullptr;
    kv_ind = 0;

    llama_backend_init();
    ggml_backend_load_all();

    llama_model_params model_params = llama_model_default_params();
    model_params.n_gpu_layers = LLM_GPU_LAYERS;
    model = llama_model_load_from_file(model_gguf_path.c_str(), model_params);

    vocab = llama_model_get_vocab(model);
    sz_vocab = llama_vocab_n_tokens(vocab);

    llama_context_params ctx_params = llama_context_default_params();
    ctx_params.n_ctx = LLM_CONTEXT_SIZE;
    ctx_params.n_batch = LLM_BATCH_SIZE;
    ctx = llama_init_from_model(model, ctx_params);
}


std::vector<int> LLM::tokenize_string(const std::string &text) const {

    /* Using text.size() for the n_tokens_max as can't be more tokens than characters in the string itself */
    std::vector<int> tokens(text.size());
    const int n = llama_tokenize(vocab, text.c_str(), static_cast<int>(text.size()),tokens.data(), static_cast<int>(tokens.size()), false, true);
    tokens.resize(n);
    return tokens;
}


std::string LLM::tkn_id_to_str(const int tkn_id) const {
    constexpr int buffer_sz = 256;
    char buf[buffer_sz];
    size_t len = llama_token_to_piece(vocab, tkn_id, buf, sizeof(buf), 0, true);
    return {buf, len};
}


std::unique_ptr<std::vector<float>> LLM::get_tkn_probabilities() const {
    if (kv_ind == 0) return nullptr;

    float* logits = llama_get_logits_ith(ctx, -1);
    auto raw_probabilities = std::make_unique<std::vector<float>>(logits, logits + sz_vocab);
    Math::parallel_softmax(*raw_probabilities);
    return raw_probabilities;
}

std::pair<int, float> LLM::choose_token_and_its_prob(const std::unique_ptr<std::vector<float>>& probabilities) const {
    const float r = Math::random_float();
    float cumulative = 0.0f;
    for (int i = 0; i < sz_vocab; i++) {
        cumulative += (*probabilities)[i];
        if (r <= cumulative) return {i, (*probabilities)[i]};
    }
    return {sz_vocab - 1, (*probabilities)[sz_vocab - 1]};
}

void LLM::wipe_last_n_tkns(const int n) {
    const int wipe_from = kv_ind - n;
    llama_memory_seq_rm(llama_get_memory(ctx), 0, wipe_from, kv_ind);
    kv_ind = wipe_from;
}

void LLM::fill_batch_at(const llama_batch& batch, const int index, const int tkn_id, const int pos, const bool needs_logits) {
    batch.token[index] = tkn_id;
    batch.pos[index] = pos;
    batch.n_seq_id[index] = 1;
    batch.seq_id[index][0] = 0;
    batch.logits[index] = needs_logits ? 1 : 0;
}

void LLM::add_tkn(const int tkn_id) {
    llama_batch batch = llama_batch_init(1, 0, 1);
    fill_batch_at(batch, 0, tkn_id, kv_ind, true);
    batch.n_tokens = 1;

    llama_decode(ctx, batch);
    llama_batch_free(batch);
    kv_ind++;
}

void LLM::add_tkns(const std::vector<int>& tkn_ids) {
    const int count = static_cast<int>(tkn_ids.size());
    llama_batch batch = llama_batch_init(count, 0, 1);

    for (int i = 0; i < count; i++) {
        fill_batch_at(batch, i, tkn_ids[i], kv_ind + i, i == count - 1);
    }
    batch.n_tokens = count;

    llama_decode(ctx, batch);
    llama_batch_free(batch);
    kv_ind += count;
}

LLM::~LLM() {
    if (ctx)   llama_free(ctx);
    if (model) llama_model_free(model);
    llama_backend_free();
}

