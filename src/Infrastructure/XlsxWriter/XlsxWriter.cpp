#include "XlsxWriter.h"
#include <XLDocument.hpp>
#include <XLSheet.hpp>

namespace XlsxWriter {
    void Write(const std::string &filePath, const std::string &sheetName, const std::string &reportName,
               const std::vector<std::string> &headerRow, const std::vector<std::vector<std::string> > &data) {
        OpenXLSX::XLDocument document;
        document.open(filePath);

        auto workbook = document.workbook();
        if (workbook.worksheetExists(sheetName)) {
            workbook.deleteSheet(sheetName);
        }
        workbook.addWorksheet(sheetName);
        auto sheet = workbook.worksheet(sheetName);

        sheet.mergeCells("A1:" + OpenXLSX::XLCellReference(1, static_cast<uint16_t>(headerRow.size())).address());
        sheet.cell(1, 1).value() = reportName;

        for (int column = 1; column <= static_cast<int>(headerRow.size()); column++) {
            sheet.cell(2, column).value() = headerRow[column - 1];
        }

        for (int row = 0; row < static_cast<int>(data.size()); row++) {
            for (int column = 0; column < static_cast<int>(data[row].size()); column++) {
                sheet.cell(row + 3, column + 1).value() = data[row][column];
            }
        }

        document.save();
        document.close();
    }

    void DeleteSheet(const std::string &filePath, const std::string &sheetName) {
        OpenXLSX::XLDocument document;
        document.open(filePath);

        if (auto workbook = document.workbook(); workbook.worksheetExists(sheetName)) {
            workbook.deleteSheet(sheetName);
        }

        document.save();
        document.close();
    }
}
