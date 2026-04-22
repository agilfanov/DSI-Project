#ifndef DSI_PROJECT_UI_H
#define DSI_PROJECT_UI_H

#include <string>
#include <memory>
#include "../llm/Tokenizer.h"

class UI {

public:
    explicit UI(const std::string& model_gguf_path);
    virtual ~UI();

protected:
    llama_model* model;
    std::unique_ptr<Tokenizer> tokenizer;

};

#endif //DSI_PROJECT_UI_H
