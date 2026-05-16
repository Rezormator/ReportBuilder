#include "XlsxReader.h"
#include <XLDocument.hpp>
#include <XLSheet.hpp>

namespace XlsxReader {
    std::string CellToString(const OpenXLSX::XLCellValue &value) {
        switch (value.type()) {
            case OpenXLSX::XLValueType::String: return value.get<std::string>();
            case OpenXLSX::XLValueType::Integer: return std::to_string(value.get<int64_t>());
            case OpenXLSX::XLValueType::Float: return std::to_string(value.get<double>());
            case OpenXLSX::XLValueType::Boolean: return value.get<bool>() ? "true" : "false";
            default: return "";
        }
    }

    std::vector<std::vector<std::string> > Read(const std::string &filePath, const int sheetId, const int startRow,
                                                const std::vector<int> &targetColumns) {
        OpenXLSX::XLDocument document;
        document.open(filePath);

        auto workbook = document.workbook();
        const auto sheet = workbook.worksheet(workbook.worksheetNames()[sheetId]);

        std::vector<std::vector<std::string> > data;

        for (int row = startRow; row <= sheet.rowCount() - 1; row++) {
            std::vector<std::string> rowData;
            rowData.reserve(targetColumns.size());

            for (const auto column: targetColumns) {
                rowData.push_back(CellToString(sheet.cell(row, column).value()));
            }

            if (rowData.empty() || rowData[0].empty()) {
                break;
            }

            data.push_back(std::move(rowData));
        }

        document.close();
        return data;
    }
}
