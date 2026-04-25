//
// Created by Arthur Gilfanov on 4/24/26.
//

#ifndef DSI_PROJECT_TUI_H
#define DSI_PROJECT_TUI_H

#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>

#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>

class TUI {

public:
    TUI();

    void start();

    void stop();

    std::string get_prompt();

    void stream_model_output_tkn(const std::string& token);

    void stop_generation();

    void clear_screen();

    void show_welcome();

    void show_system_status();

private:



};

#endif //DSI_PROJECT_TUI_H
