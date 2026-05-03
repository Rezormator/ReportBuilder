#include "Configurations/MenuOptions.h"
#include "UI/UI.h"
#include "XlsxHandler/XlsxHandler.h"

int main() {
    UI::ApplyUkrainianLanguage();

    switch (UI::SelectionMenu(MenuOptions::STOR_TYPES, 0, false)) {
        case MenuOptions::Concept: {
            //TODO Встановлення мінмальної/максимальної кількості одягу
            break;
        }
        case MenuOptions::Discount: {
            //TODO Встановлення максимальної кількості одягу
            break;
        }
        default: {
            break;
        }
    }

    bool continueRunning = true;
    int selected = 0;

    do {
        selected = UI::SelectionMenu(MenuOptions::REPORT_TYPES, selected);

        switch (selected) {
            case MenuOptions::Textile: {
                //TODO Формування усіх звітів по текстилю
                break;
            }
            case MenuOptions::Footwear: {
                //TODO Формування усіх звітів по взуттю
                break;
            }
            case MenuOptions::Exit: {
                continueRunning = false;
                break;
            }
            default: {
                break;
            }
        }
    } while (continueRunning);

    return 0;
}
