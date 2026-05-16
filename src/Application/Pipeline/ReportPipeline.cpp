#include "ReportPipeline.h"
#include "../../Infrastructure/XlsxReader/XlsxReader.h"
#include "../../Infrastructure/XlsxWriter/XlsxWriter.h"
#include "../../Infrastructure/DataHandler/DataHandler.h"
#include "../../Infrastructure/AppConfiguration.h"

namespace ReportPipeline {
    const std::vector<std::string> ALL_REPORT_SHEETS = {
        "Дов. розмiрів",
        "Дов. розмірів",
        "Від. розмірів",
        "Дов. артикулів",
        "Ост. в магазині",
        "Ост. в залі"
    };

    void ClearSheets() {
        const AppConfiguration configuration;
        for (const auto &filePath: {configuration.textilesPath, configuration.footwearPath}) {
            for (const auto &sheetName: ALL_REPORT_SHEETS) {
                try {
                    XlsxWriter::DeleteSheet(filePath, sheetName);
                } catch (...) {
                }
            }
        }
    }

    void Run(const StoreConfig &config) {
        const AppConfiguration appConfiguration;

        const auto rawData = XlsxReader::Read(
            config.filePath,
            appConfiguration.readSheetId,
            appConfiguration.startRow,
            appConfiguration.targetColumns
        );

        const auto products = DataHandler::Parse(rawData);

        for (const auto &reportDefinition: config.reports) {
            auto rows = reportDefinition.builder(products, config.params);
            XlsxWriter::Write(
                config.filePath,
                reportDefinition.sheetName,
                reportDefinition.header,
                reportDefinition.columns,
                rows
            );
        }
    }
}
