#include <algorithm>
#include "UI/MenuOptions.h"
#include "ReportBuilder/ReportPresets.h"
#include "XlsxHandler/XlsxConfiguration.h"
#include "ReportBuilder/ReportService/ReportService.h"
#include "UI/Key.h"
#include "UI/UI.h"

int main() {
    UI::ApplyUkrainianLanguage();

    UI::ShowMessage("Підготовка файлів...");
    ReportService::ClearFileSheets(XlsxConfiguration::TEXTILE_PATH, ReportPresets::SHEETS);
    ReportService::ClearFileSheets(XlsxConfiguration::FOOTWEAR_PATH, ReportPresets::SHEETS);

    MenuOptions::STOR_TYPES storType = MenuOptions::STOR_TYPES::Concept;

    switch (UI::SelectionMenu(MenuOptions::STOR_TYPE_OPTIONS, 0, false)) {
        case MenuOptions::STOR_TYPES::Concept: {
            storType = MenuOptions::STOR_TYPES::Concept;
            break;
        }
        case MenuOptions::STOR_TYPES::Discount: {
            storType = MenuOptions::STOR_TYPES::Discount;
            break;
        }
        default: {
            break;
        }
    }

    bool continueRunning = true;
    int selected = 0;

    do {
        selected = UI::SelectionMenu(MenuOptions::REPORT_TYPE_OPTIONS, selected);

        switch (selected) {
            case MenuOptions::REPORT_TYPES::Textile: {
                system("cls");
                UI::ShowMessage("Формування звітів по тектстилю...\n");
                ReportService::FormTextileReports(storType);
                UI::ShowMessage("Натисність Enter для проовження...");
                UI::WaitKeyPress(Key::KEY_ENTER);
                break;
            }
            case MenuOptions::REPORT_TYPES::Footwear: {
                system("cls");
                UI::ShowMessage("Формування звітів по взуттю...\n");
                ReportService::FormFootwearReports(storType);
                UI::ShowMessage("Натисність Enter для проовження...");
                UI::WaitKeyPress(Key::KEY_ENTER);
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
