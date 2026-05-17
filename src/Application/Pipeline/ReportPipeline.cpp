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
        const AppConfiguration appCfg;

        const auto raw = XlsxReader::Read(config.filePath, appCfg.readSheetId, appCfg.startRow);
        const auto products = DataHandler::Parse(raw);

        for (const auto &def : config.reports) {
            auto rows = def.builder(products, config.params);
            XlsxWriter::Write(config.filePath, def.sheetName, def.header, def.columns, rows);
        }
    }
}
