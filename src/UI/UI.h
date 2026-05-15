#pragma once

#include <string>
#include <vector>

namespace UI {
    void ApplyUkrainianLanguage();
    int SelectionMenu(std::vector<std::string> options, int current = 0, bool addExit = true);
    void ShowMessage(const std::string &message);
    void WaitKeyPress(int Key);
}
