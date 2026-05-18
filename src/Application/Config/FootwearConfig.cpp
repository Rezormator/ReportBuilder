#include "StoreConfig.h"
#include "../../Domain/Builders/Builders.h"
#include "../../Infrastructure/AppConfiguration.h"
#include "../../Infrastructure/AppSettings.h"

StoreConfig MakeFootwearConfig(const ReportParams &params, FootwearReportFlags flags) {
    const std::vector<std::string> COL_SIZE      = {"Артикул", "Розмір", "Опис", "Полиця", "Кількість"};
    const std::vector<std::string> COL_LOW_COUNT = {"Артикул", "Опис", "Полиця", "Зал", "Склад", "Кількість"};

    std::vector<ReportDef> reports;

    if (flags.addSizes) {
        reports.push_back({
            .sheetName = "Дов. розмiрів",
            .header    = "Звіт по довішуванню розмірів",
            .columns   = COL_SIZE,
            .builder   = [](const auto &products, const auto &p) {
                return Builders::AddFootwearSizes(products, p);
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
        .filePath = AppConfiguration{}.footwearPath,
        .params   = params,
        .reports  = reports
    };
}
