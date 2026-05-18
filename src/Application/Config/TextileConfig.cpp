#include "StoreConfig.h"
#include "../../Domain/Builders/Builders.h"
#include "../../Infrastructure/AppConfiguration.h"
#include "../../Infrastructure/AppSettings.h"

StoreConfig MakeTextileConfig(const ReportParams &params, TextileReportFlags flags) {
    const std::vector<std::string> COL_SIZE      = {"Артикул", "Розмір", "Опис", "Полиця", "Кількість"};
    const std::vector<std::string> COL_PRODUCT   = {"Артикул", "Опис", "Полиця", "Кількість"};
    const std::vector<std::string> COL_LOW_COUNT = {"Артикул", "Опис", "Полиця", "Зал", "Склад", "Кількість"};

    std::vector<ReportDef> reports;

    if (flags.addSizes) {
        reports.push_back({
            .sheetName = "Дов. розмiрів",
            .header    = "Звіт по довішуванню розмірів",
            .columns   = COL_SIZE,
            .builder   = [](const auto &products, const auto &p) {
                return Builders::AddSizes(products, p);
            }
        });
    }

    if (flags.addAndReplaceSizes) {
        reports.push_back({
            .sheetName = "Дов. розмірів",
            .header    = "Звіт по довішуванню розмірів за розмірною сіткою",
            .columns   = COL_SIZE,
            .builder   = [](const auto &products, const auto &p) {
                return Builders::AddAndReplaceSizes(products, p).first;
            }
        });
        reports.push_back({
            .sheetName = "Від. розмірів",
            .header    = "Звіт по відвішуванню розмірів за розмірною сіткою",
            .columns   = COL_SIZE,
            .builder   = [](const auto &products, const auto &p) {
                return Builders::AddAndReplaceSizes(products, p).second;
            }
        });
    }

    if (flags.addProducts) {
        reports.push_back({
            .sheetName = "Дов. артикулів",
            .header    = "Звіт по відсутнім в залі артикулам",
            .columns   = COL_PRODUCT,
            .builder   = [](const auto &products, const auto &p) {
                return Builders::AddProducts(products, p);
            }
        });
    }

    if (flags.lowCountStore) {
        reports.push_back({
            .sheetName = "Ост. в магазині",
            .header    = "Звіт по артикулам котрих мало в магазині",
            .columns   = COL_LOW_COUNT,
            .builder   = [](const auto &products, const auto &p) {
                return Builders::LowCount(products, p, false);
            }
        });
    }

    if (flags.lowCountHall) {
        reports.push_back({
            .sheetName = "Ост. в залі",
            .header    = "Звіт по артикулам в залі котрих мало в магазині",
            .columns   = COL_LOW_COUNT,
            .builder   = [](const auto &products, const auto &p) {
                return Builders::LowCount(products, p, true);
            }
        });
    }

    return StoreConfig{
        .filePath = AppConfiguration{}.textilesPath,
        .params   = params,
        .reports  = reports
    };
}
