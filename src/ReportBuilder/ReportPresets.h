#pragma once

#include "ReportConfigurations.h"

namespace ReportPresets {
    constexpr auto CONCEPT_TEXTILE_CONFIGURATIONS = ReportConfigurations(4, 6);
    constexpr auto CONCEPT_FOOTWEAR_CONFIGURATIONS = ReportConfigurations(1, 1, 3);
    constexpr auto DISCOUNT_TEXTILE_CONFIGURATIONS = ReportConfigurations(1, 10);
    constexpr auto DISCOUNT_FOOTWEAR_CONFIGURATIONS = ReportConfigurations(1, 1, 1);

    inline std::vector<std::string> COL_SIZE = {"Артикул", "Розмір", "Опис", "Полиця", "Кількість"};
    inline std::vector<std::string> COL_PRODUCT = {"Артикул", "Опис", "Полиця", "Кількість"};
    inline std::vector<std::string> COL_LOW_COUNT = {"Артикул", "Опис", "Полиця", "Зал", "Склад", "Кількість"};

    inline std::vector<std::string> SHEETS = {
        "Дов. розмiрів",
        "Дов. розмірів",
        "Від. розмірів",
        "Дов. артикулів",
        "Ост. в магазині",
        "Ост. в залі"
    };

    inline std::vector COLUMN_HEADERS = {
        COL_SIZE,
        COL_SIZE,
        COL_SIZE,
        COL_PRODUCT,
        COL_LOW_COUNT,
        COL_LOW_COUNT
    };

    inline std::vector<std::string> HEADERS = {
        "Звіт по довішуванню розмірів",
        "Звіт по довішуванню розмірів за розмірною сіткою",
        "Звіт по відвішуванню розмірів за розмірною сіткою",
        "Звіт по відсутнім в залі артикулам",
        "Звіт по артикулам котрих мало в магазині",
        "Звіт по артикулам в залі котрих мало в магазині"
    };
}
