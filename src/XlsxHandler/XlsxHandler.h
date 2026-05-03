#pragma once

#include <map>
#include <string>
#include <vector>

namespace XlsxHandler {
    std::vector<std::vector<std::string>> ReadXlsxFile(const std::string& filePath, int sheetId, int startRow, const std::vector<int> &targetColumns);
    void WriteXlsxFile(const std::string& filePath, int sheetName, const std::vector<std::vector<std::string>> &data, const std::vector<std::string> &headerRow);
}
