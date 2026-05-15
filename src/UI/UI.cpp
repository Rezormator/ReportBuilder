#include "UI.h"
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include "Color.h"
#include "Key.h"

namespace UI {
    void ApplyUkrainianLanguage() {
        SetConsoleOutputCP(65001);
    }

    int SelectionMenu(std::vector<std::string> options, const int current, const bool addExit) {
        if (addExit) {
            options.emplace_back("Вихід");
        }

        const int optionsCount = static_cast<int>(options.size());
        int selected = current;
        bool continueSelection = true;

        do {
            system("cls");

            for (int i = 0; i < optionsCount; i++) {
                if (i == selected) {
                    std::cout << Color::BACKGROUND_WHITE << options[i] << std::endl;
                }
                else {
                    std::cout << Color::BACKGROUND_BLACK << options[i] << std::endl;
                }
            }

            switch (_getch()) {
                case Key::KEY_UP:
                    selected = (selected - 1 + optionsCount) % optionsCount;
                break;
                case Key::KEY_DOWN:
                    selected = (selected + 1) % optionsCount;
                break;
                case Key::KEY_ENTER:
                    continueSelection = false;
                break;
                default:
                    break;
            }

        } while (continueSelection);

        return selected;
    }

    void ShowMessage(const std::string &message) {
        std::cout << message << std::endl;
    }

    void WaitKeyPress(const int Key) {
        while (_getch() != Key);
    }
}
