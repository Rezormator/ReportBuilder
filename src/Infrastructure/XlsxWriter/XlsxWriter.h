#pragma once

#include <string>
#include <vector>

namespace XlsxWriter {
    void Write(const std::string &filePath, const std::string &sheetName, const std::string &reportName,
               const std::vector<std::string> &headerRow, const std::vector<std::vector<std::string>> &data);
    void DeleteSheet(const std::string &filePath, const std::string &sheetName);
}
