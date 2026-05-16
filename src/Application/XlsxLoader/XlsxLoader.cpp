#include "XlsxLoader.h"
#include "../../UI/Widgets/SheetView/SheetView.h"
#include <XLDocument.hpp>
#include <XLSheet.hpp>

namespace XlsxLoader {
    QString CellToQString(const OpenXLSX::XLCellValue &value) {
        switch (value.type()) {
            case OpenXLSX::XLValueType::String: return QString::fromStdString(value.get<std::string>());
            case OpenXLSX::XLValueType::Integer: return QString::number(value.get<int64_t>());
            case OpenXLSX::XLValueType::Float: return QString::number(value.get<double>(), 'f', 2);
            case OpenXLSX::XLValueType::Boolean: return value.get<bool>() ? "true" : "false";
            default: return {};
        }
    }

    QList<SheetData> Load(const QString &filePath) {
        QList<SheetData> result;

        try {
            OpenXLSX::XLDocument document;
            document.open(filePath.toStdString());
            auto workbook = document.workbook();

            for (const auto &name: workbook.worksheetNames()) {
                const auto sheet = workbook.worksheet(name);
                SheetData sheetData;
                sheetData.name = QString::fromStdString(name);

                const int rowCount = sheet.rowCount();
                const int columnCount = sheet.columnCount();

                bool headersRead = false;
                for (int row = 1; row <= rowCount; row++) {
                    std::vector<std::string> rowValues;
                    bool hasData = false;

                    for (int column = 1; column <= columnCount; column++) {
                        const auto value = CellToQString(sheet.cell(row, column).value());
                        rowValues.push_back(value.toStdString());
                        if (!value.isEmpty()) {
                            hasData = true;
                        }
                    }

                    if (!hasData) {
                        continue;
                    }

                    if (!headersRead) {
                        sheetData.headers = rowValues;
                        headersRead = true;
                    } else {
                        sheetData.rows.push_back(rowValues);
                    }
                }

                result.append(sheetData);
            }

            document.close();
        } catch (...) {
        }

        return result;
    }
}
