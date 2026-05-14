#include <algorithm>
#include "Configurations/MenuOptions.h"
#include "Configurations/SizePriority.h"
#include "Configurations/XlsxConfiguration.h"
#include "Product/DataHandler/DataHandler.h"
#include "ReportBuilder/Textile/Builder.h"
#include "UI/UI.h"
#include "XlsxHandler/XlsxHandler.h"

int main() {
    UI::ApplyUkrainianLanguage();

    // TODO clear all sheets

    switch (UI::SelectionMenu(MenuOptions::STOR_TYPE_OPTIONS, 0, false)) {
        case MenuOptions::STOR_TYPES::Concept: {
            //TODO Встановлення мінмальної/максимальної кількості одягу
            break;
        }
        case MenuOptions::STOR_TYPES::Discount: {
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
        selected = UI::SelectionMenu(MenuOptions::REPORT_TYPE_OPTIONS, selected);

        switch (selected) {
            case MenuOptions::REPORT_TYPES::Textile: {
                auto data = XlsxHandler::ReadXlsxFile(XlsxConfiguration::TEXTILE_PATH, XlsxConfiguration::READ_SHEET_ID,
                                                      XlsxConfiguration::START_ROW, XlsxConfiguration::TARGET_COLUMNS);
                auto products = DataHandler::ConvertDataToProduct(data);
                ReportConfigurations textileConfigurations;

                auto addSizes = Builder::AddSizes(products, textileConfigurations);
                XlsxHandler::WriteXlsxFile(XlsxConfiguration::TEXTILE_PATH,
                    "Дов. розм",
                    addSizes,
                    {"Артикул", "Розмір", "Опис", "Полиця", "Кількість"},
                    "Звіт по довішуванню розмірів");

                auto addAndReplace = Builder::AddAndReplaceSizes(products, textileConfigurations);
                XlsxHandler::WriteXlsxFile(XlsxConfiguration::TEXTILE_PATH,
                    "Дов. розмірів",
                    addAndReplace.first,
                    {"Артикул", "Розмір", "Опис", "Полиця", "Кількість"},
                    "Звіт по довішуванню розмірів");
                XlsxHandler::WriteXlsxFile(XlsxConfiguration::TEXTILE_PATH,
                    "Від. розмірів",
                    addAndReplace.second,
                    {"Артикул", "Розмір", "Опис", "Полиця", "Кількість"},
                    "Звіт по відвішуванню розмірів");

                auto addProducts = Builder::AddProducts(products, textileConfigurations);
                XlsxHandler::WriteXlsxFile(XlsxConfiguration::TEXTILE_PATH,
                    "Дов. артикулів",
                    addProducts,
                    {"Артикул", "Опис", "Полиця", "Кількість"},
                    "Звіт по відсутнім в залі артикулам");

                auto lowCountProducts = Builder::LowCountProducts(products, textileConfigurations);
                XlsxHandler::WriteXlsxFile(XlsxConfiguration::TEXTILE_PATH,
                    "Ост. в магазині",
                    lowCountProducts,
                    {"Артикул", "Опис", "Полиця", "Зал", "Склад", "Кількість"},
                    "Звіт по артикулам кортих мало в магазині");

                auto lowCountHallProducts = Builder::LowCountProducts(products, textileConfigurations, true);
                XlsxHandler::WriteXlsxFile(XlsxConfiguration::TEXTILE_PATH,
                    "Ост. в залі",
                    lowCountHallProducts,
                    {"Артикул", "Опис", "Полиця", "Зал", "Склад", "Кількість"},
                    "Звіт по артикулам в залі кортих мало в магазині");

                //TODO Формування усіх звітів по текстилю
                break;
            }
            case MenuOptions::REPORT_TYPES::Footwear: {
                auto data = XlsxHandler::ReadXlsxFile(
                    XlsxConfiguration::FOOTWEAR_PATH,
                    XlsxConfiguration::READ_SHEET_ID,
                    XlsxConfiguration::START_ROW,
                    XlsxConfiguration::TARGET_COLUMNS);
                auto products = DataHandler::ConvertDataToProduct(data);

                ReportConfigurations footwearConfigurations;
                footwearConfigurations.maxCount = 1;
                footwearConfigurations.minCount = 1;
                footwearConfigurations.minSizeCount = 3;

                auto addFootwearSizes = Builder::AddFootwearSizes(products, footwearConfigurations);

                XlsxHandler::WriteXlsxFile(XlsxConfiguration::FOOTWEAR_PATH,
                    "Дов. розм",
                    addFootwearSizes,
                    {"Артикул", "Розмір", "Опис", "Полиця", "Кількість"},
                    "Звіт по довішуванню розмірів");
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
