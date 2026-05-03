#pragma once

#include <string>
#include <vector>

namespace UI {
    void ApplyUkrainianLanguage();
    int SelectionMenu(std::vector<std::string> options, int current = 0, bool addExit = true);
    void WaitKeyPress(int Key, int rowsCount);
}
