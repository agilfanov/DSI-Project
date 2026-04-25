//
// Created by Arthur Gilfanov on 4/23/26.
//

#include "Session.h"

Session::Session(const std::string& model_path)
    : tokenizer(model_path) {}

std::vector<int> Session::tokenize(const std::string& text) {
    return tokenizer.tokenize_string(text);
}

std::string Session::detokenize(const std::vector<int>& tkn_ids) {
    std::string result;
    for (int id : tkn_ids) {
        result += tokenizer.tkn_id_to_str(id);
    }
    return result;
}
