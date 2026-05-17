#include "XlsxReader.h"
#include <XLDocument.hpp>
#include <XLSheet.hpp>
#include <stdexcept>

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

    struct ColumnIndices {
        int id = -1;
        int size = -1;
        int position1 = -1;
        int position2 = -1;
        int description = -1;
        int storage = -1;
        int hall = -1;
    };

    bool ContainsIgnoreCase(const std::string &haystack, const std::string &needle) {
        if (needle.empty()) {
            return true;
        }
        return std::ranges::search(haystack, needle, [](const unsigned char a, const unsigned char b) {
            return std::tolower(a) == std::tolower(b);
        }).begin() != haystack.end();
    }


    std::vector<std::vector<std::string> > Read(
        const std::string &filePath,
        const int sheetId,
        const int startRow) {
        OpenXLSX::XLDocument document;
        document.open(filePath);

        auto workbook = document.workbook();
        const auto sheet = workbook.worksheet(workbook.worksheetNames()[sheetId]);
        const int totalRows = sheet.rowCount();
        const int totalCols = sheet.columnCount();

        int lowerHeaderRow = startRow - 1;
        for (int r = startRow - 1; r >= 1; --r) {
            for (int c = 1; c <= totalCols; ++c) {
                if (ContainsIgnoreCase(CellToString(sheet.cell(r, c).value()), "Артикул")) {
                    lowerHeaderRow = r;
                    goto foundHeader;
                }
            }
        }
    foundHeader:;

        const int upperHeaderRow = lowerHeaderRow - 1;
        std::vector<std::string> mergedHeaders(totalCols + 1);
        for (int c = 1; c <= totalCols; ++c) {
            const std::string upper = (upperHeaderRow >= 1) ? CellToString(sheet.cell(upperHeaderRow, c).value()) : "";
            const std::string lower = CellToString(sheet.cell(lowerHeaderRow, c).value());

            if (!upper.empty() && !lower.empty()) {
                mergedHeaders[c] = upper + " " + lower;
            } else {
                mergedHeaders[c] = upper.empty() ? lower : upper;
            }
        }

        ColumnIndices idx; {
            struct Mapping {
                std::string_view keyword;
                int ColumnIndices::*field;
            };
            constexpr std::array mappings = {
                Mapping{"Артикул", &ColumnIndices::id},
                Mapping{"Розмір", &ColumnIndices::size},
                Mapping{"Полиця 1", &ColumnIndices::position1},
                Mapping{"Полиця 2", &ColumnIndices::position2},
                Mapping{"Найменування", &ColumnIndices::description},
                Mapping{"Основний склад", &ColumnIndices::storage},
                Mapping{"Торговий зал", &ColumnIndices::hall},
            };

            for (int c = 1; c <= totalCols; ++c) {
                if (mergedHeaders[c].empty()) continue;
                for (const auto &[keyword, field]: mappings) {
                    if (idx.*field < 0 && ContainsIgnoreCase(mergedHeaders[c], std::string(keyword))) {
                        idx.*field = c;
                        break;
                    }
                }
            }

            struct Required {
                int ColumnIndices::*field;
                std::string_view label;
            };

            for (const auto &[field, label]: std::array{
                     Required{&ColumnIndices::id, "«Артикул»"},
                     Required{&ColumnIndices::size, "«Розмір»"},
                     Required{&ColumnIndices::description, "«Найменування»"},
                     Required{&ColumnIndices::storage, "«Основний склад»"},
                     Required{&ColumnIndices::hall, "«Торговий зал»"},
                 }) {
                if (idx.*field < 0) {
                    throw std::runtime_error("Не знайдено колонку " + std::string(label) + " у заголовку файлу.");
                }
            }
        }

        std::vector<std::vector<std::string> > data;

        for (int row = startRow; row <= totalRows; ++row) {
            const std::string id = CellToString(sheet.cell(row, idx.id).value());
            if (id.empty()) {
                break;
            }

            data.push_back({
                id,
                CellToString(sheet.cell(row, idx.size).value()),
                idx.position1 > 0 ? CellToString(sheet.cell(row, idx.position1).value()) : "",
                idx.position2 > 0 ? CellToString(sheet.cell(row, idx.position2).value()) : "",
                CellToString(sheet.cell(row, idx.description).value()),
                CellToString(sheet.cell(row, idx.storage).value()),
                CellToString(sheet.cell(row, idx.hall).value()),
            });
        }

        document.close();
        return data;
    }
}
