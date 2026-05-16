#include "StoreConfig.h"
#include "../../Domain/Builders/Builders.h"
#include "../../Infrastructure/AppConfiguration.h"

StoreConfig MakeConceptFootwear() {
    constexpr ReportParams parameters{.minCount = 1, .maxCount = 1, .minSizeCount = 3, .lowCount = 3};

    const std::vector<std::string> COL_SIZE = {"Артикул", "Розмір", "Опис", "Полиця", "Кількість"};
    const std::vector<std::string> COL_LOW_COUNT = {"Артикул", "Опис", "Полиця", "Зал", "Склад", "Кількість"};

    return StoreConfig{
        .filePath = AppConfiguration{}.footwearPath,
        .params = parameters,
        .reports = {
            {
                .sheetName = "Дов. розмiрів",
                .header = "Звіт по довішуванню розмірів",
                .columns = COL_SIZE,
                .builder = [](const auto &products, const auto &p) {
                    return Builders::AddFootwearSizes(products, p);
                }
            },
            {
                .sheetName = "Ост. в магазині",
                .header = "Звіт по артикулам котрих мало в магазині",
                .columns = COL_LOW_COUNT,
                .builder = [](const auto &products, const auto &p) {
                    return Builders::LowCount(products, p, false);
                }
            },
            {
                .sheetName = "Ост. в залі",
                .header = "Звіт по артикулам в залі котрих мало в магазині",
                .columns = COL_LOW_COUNT,
                .builder = [](const auto &products, const auto &p) {
                    return Builders::LowCount(products, p, true);
                }
            }
        }
    };
}
