#include "XlsxHandler.h"
#include <XLDocument.hpp>
#include <XLSheet.hpp>

namespace XlsxHandler {
    auto CellToString(const OpenXLSX::XLCellValue &value) -> std::string {
        switch (value.type()) {
            case OpenXLSX::XLValueType::String: return value.get<std::string>();
            case OpenXLSX::XLValueType::Integer: return std::to_string(value.get<int64_t>());
            case OpenXLSX::XLValueType::Float: return std::to_string(value.get<double>());
            case OpenXLSX::XLValueType::Boolean: return value.get<bool>() ? "true" : "false";
            default: return "";
        }
    }

    std::vector<std::vector<std::string> > ReadXlsxFile(const std::string &filePath, const int sheetId,
                                                        const int startRow, const std::vector<int> &targetColumns) {
        OpenXLSX::XLDocument document;
        document.open(filePath);

        auto book = document.workbook();
        const auto sheet = book.worksheet(book.worksheetNames()[sheetId]);

        std::vector<std::vector<std::string> > data;

        for (int row = startRow; row <= sheet.rowCount() - 1; row++) {
            std::vector<std::string> rowData;

            for (const auto col: targetColumns) {
                rowData.push_back(CellToString(sheet.cell(row, col).value()));
            }

            if (rowData.empty() || rowData[0].empty()) {
                break;
            }

            data.push_back(std::move(rowData));
        }

        document.close();

        return data;
    }

    void WriteXlsxFile(const std::string &filePath, const std::string &sheetName, std::vector<std::vector<std::string> > &data,
                       const std::vector<std::string> &headerRow, const std::string &reportName) {
        OpenXLSX::XLDocument document;
        document.open(filePath);

        auto book = document.workbook();
        if (book.worksheetExists(sheetName)) {
            book.deleteSheet(sheetName);
        }
        book.addWorksheet(sheetName);
        auto sheet = book.worksheet(sheetName);

        sheet.mergeCells("A1:" + OpenXLSX::XLCellReference(1, static_cast<uint16_t>(headerRow.size())).address());
        sheet.cell(1, 1).value() = reportName;

        data.insert(data.begin(), headerRow);

        for (int row = 1; row <= data.size(); row++) {
            for (int column = 1; column <= data[row - 1].size(); column++) {
                sheet.cell(row + 1, column).value() = data[row - 1][column - 1];
            }
        }

        document.save();
        document.close();
    }

    void DeleteSheet(const std::string &filePath, const std::string &sheetName) {
        OpenXLSX::XLDocument document;
        document.open(filePath);

        if (auto book = document.workbook(); book.worksheetExists(sheetName)) {
            book.deleteSheet(sheetName);
        }

        document.save();
        document.close();
    }
}
