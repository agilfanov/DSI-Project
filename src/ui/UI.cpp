#include "UI.h"

UI::UI(const std::string& model_gguf_path)
    : tokenizer(model_gguf_path) {}
