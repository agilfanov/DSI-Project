#ifndef DSI_PROJECT_CLI_H
#define DSI_PROJECT_CLI_H

#include "../UI.h"

class CLI : public UI {

public:
    explicit CLI(const std::string& model_gguf_path);

};

#endif //DSI_PROJECT_CLI_H
