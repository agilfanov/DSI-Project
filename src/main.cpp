//
// Created by Arthur Gilfanov on 4/13/26.
//

#include <iostream>
#include "LLM.h"

int main() {
    LLM llm("../models/Qwen3-0.6B-Q8_0.gguf");

    std::vector<int> tokens = llm.tokenize_string("How is it going today on campus? Let's get dinner today.");
    for (int id : tokens) {
        std::cout << id << " -> \"" << llm.tkn_id_to_str(id) << "\"\n";
    }

    return 0;
}