#include "ReportService.h"
#include "../ReportConfigurations.h"
#include "../ReportPresets.h"
#include "../../Product/DataHandler/DataHandler.h"
#include "../../UI/UI.h"
#include "../../XlsxHandler/XlsxConfiguration.h"
#include "../../XlsxHandler/XlsxHandler.h"
#include "../Builder/Builder.h"

namespace ReportService {
    enum ReportType {
        AddSizes,
        AddSizesReplace,
        RemoveSizesReplace,
        AddProducts,
        LowCountStore,
        LowCountHall
    };

    void FormTextileReports(const MenuOptions::STOR_TYPES &storType) {
        const auto data = XlsxHandler::ReadXlsxFile(
            XlsxConfiguration::TEXTILE_PATH,
            XlsxConfiguration::READ_SHEET_ID,
            XlsxConfiguration::START_ROW,
            XlsxConfiguration::TARGET_COLUMNS);
        const auto products = DataHandler::ConvertDataToProduct(data);

        const ReportConfigurations textileConfigurations = storType == MenuOptions::STOR_TYPES::Concept
            ? ReportPresets::CONCEPT_TEXTILE_CONFIGURATIONS : ReportPresets::DISCOUNT_TEXTILE_CONFIGURATIONS;

        auto addSizes = Builder::AddSizes(products, textileConfigurations);
        XlsxHandler::WriteXlsxFile(XlsxConfiguration::TEXTILE_PATH, ReportPresets::SHEETS[AddSizes],
        addSizes, ReportPresets::COLUMN_HEADERS[AddSizes], ReportPresets::HEADERS[AddSizes]);

        auto addProducts = Builder::AddProducts(products, textileConfigurations);
        XlsxHandler::WriteXlsxFile(XlsxConfiguration::TEXTILE_PATH, ReportPresets::SHEETS[AddProducts],
        addProducts, ReportPresets::COLUMN_HEADERS[AddProducts], ReportPresets::HEADERS[AddProducts]);

        auto lowCountProducts = Builder::LowCountProducts(products, textileConfigurations);
        XlsxHandler::WriteXlsxFile(XlsxConfiguration::TEXTILE_PATH, ReportPresets::SHEETS[LowCountStore],
        lowCountProducts, ReportPresets::COLUMN_HEADERS[LowCountStore], ReportPresets::HEADERS[LowCountStore]);

        auto lowCountHallProducts = Builder::LowCountProducts(products, textileConfigurations, true);
        XlsxHandler::WriteXlsxFile(XlsxConfiguration::TEXTILE_PATH, ReportPresets::SHEETS[LowCountHall],
        lowCountHallProducts, ReportPresets::COLUMN_HEADERS[LowCountHall], ReportPresets::HEADERS[LowCountHall]);

        if (storType == MenuOptions::STOR_TYPES::Concept) {
            auto [toAdd, toRemove] = Builder::AddAndReplaceSizes(products, textileConfigurations);
            XlsxHandler::WriteXlsxFile(XlsxConfiguration::TEXTILE_PATH, ReportPresets::SHEETS[AddSizesReplace],
            toAdd, ReportPresets::COLUMN_HEADERS[AddSizesReplace], ReportPresets::HEADERS[AddSizesReplace]);
            XlsxHandler::WriteXlsxFile(XlsxConfiguration::TEXTILE_PATH, ReportPresets::SHEETS[RemoveSizesReplace],
            toRemove, ReportPresets::COLUMN_HEADERS[RemoveSizesReplace], ReportPresets::HEADERS[RemoveSizesReplace]);
        }
    }

    void FormFootwearReports(const MenuOptions::STOR_TYPES &storType) {
        const auto data = XlsxHandler::ReadXlsxFile(
                    XlsxConfiguration::FOOTWEAR_PATH,
                    XlsxConfiguration::READ_SHEET_ID,
                    XlsxConfiguration::START_ROW,
                    XlsxConfiguration::TARGET_COLUMNS);
        auto products = DataHandler::ConvertDataToProduct(data);

        const ReportConfigurations footwearConfigurations = storType == MenuOptions::STOR_TYPES::Concept
            ? ReportPresets::CONCEPT_FOOTWEAR_CONFIGURATIONS : ReportPresets::DISCOUNT_FOOTWEAR_CONFIGURATIONS;

        auto addSizes = Builder::AddFootwearSizes(products, footwearConfigurations);
        XlsxHandler::WriteXlsxFile(XlsxConfiguration::FOOTWEAR_PATH, ReportPresets::SHEETS[AddSizes],
        addSizes, ReportPresets::COLUMN_HEADERS[AddSizes], ReportPresets::HEADERS[AddSizes]);

        auto lowSizeCountProducts = Builder::LowSizeCountProducts(products, footwearConfigurations);
        XlsxHandler::WriteXlsxFile(XlsxConfiguration::FOOTWEAR_PATH, ReportPresets::SHEETS[LowCountStore],
        lowSizeCountProducts, ReportPresets::COLUMN_HEADERS[LowCountStore], ReportPresets::HEADERS[LowCountStore]);

        if (storType == MenuOptions::STOR_TYPES::Concept) {
            auto lowSizeCountHallProducts = Builder::LowSizeCountProducts(products, footwearConfigurations, true);
            XlsxHandler::WriteXlsxFile(XlsxConfiguration::FOOTWEAR_PATH, ReportPresets::SHEETS[LowCountHall],
            lowSizeCountHallProducts, ReportPresets::COLUMN_HEADERS[LowCountHall], ReportPresets::HEADERS[LowCountHall]);
        }
    }

    void ClearFileSheets(const std::string& filePath, const std::vector<std::string>& sheets) {
        for (const auto& sheet : sheets) {
            XlsxHandler::DeleteSheet(filePath, sheet);
        }
    }
}
