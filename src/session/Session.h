//
// Created by Arthur Gilfanov on 4/23/26.
//

#ifndef DSI_PROJECT_SESSION_H
#define DSI_PROJECT_SESSION_H

#include <string>
#include <vector>
#include "../llm/Tokenizer.h"

class Session {

public:
    explicit Session(const std::string& model_path);

    std::vector<int> tokenize(const std::string& text);

    std::string detokenize(const std::vector<int>& tkn_ids);

private:
    Tokenizer tokenizer;

};

#endif //DSI_PROJECT_SESSION_H
