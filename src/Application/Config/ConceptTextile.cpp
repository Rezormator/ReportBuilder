#include "StoreConfig.h"
#include "../../Domain/Builders/Builders.h"
#include "../../Infrastructure/AppConfiguration.h"

StoreConfig MakeConceptTextile() {
    constexpr ReportParams parameters{.minCount = 4, .maxCount = 6, .minSizeCount = 3, .lowCount = 3};

    const std::vector<std::string> COL_SIZE = {"Артикул", "Розмір", "Опис", "Полиця", "Кількість"};
    const std::vector<std::string> COL_PRODUCT = {"Артикул", "Опис", "Полиця", "Кількість"};
    const std::vector<std::string> COL_LOW_COUNT = {"Артикул", "Опис", "Полиця", "Зал", "Склад", "Кількість"};

    return StoreConfig{
        .filePath = AppConfiguration{}.textilesPath,
        .params = parameters,
        .reports = {
            {
                .sheetName = "Дов. розмiрів",
                .header = "Звіт по довішуванню розмірів",
                .columns = COL_SIZE,
                .builder = [](const auto &products, const auto &p) {
                    return Builders::AddSizes(products, p);
                }
            },
            {
                .sheetName = "Дов. розмірів",
                .header = "Звіт по довішуванню розмірів за розмірною сіткою",
                .columns = COL_SIZE,
                .builder = [](const auto &products, const auto &p) {
                    return Builders::AddAndReplaceSizes(products, p).first;
                }
            },
            {
                .sheetName = "Від. розмірів",
                .header = "Звіт по відвішуванню розмірів за розмірною сіткою",
                .columns = COL_SIZE,
                .builder = [](const auto &products, const auto &p) {
                    return Builders::AddAndReplaceSizes(products, p).second;
                }
            },
            {
                .sheetName = "Дов. артикулів",
                .header = "Звіт по відсутнім в залі артикулам",
                .columns = COL_PRODUCT,
                .builder = [](const auto &products, const auto &p) {
                    return Builders::AddProducts(products, p);
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
