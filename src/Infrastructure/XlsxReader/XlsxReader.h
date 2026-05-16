#pragma once

#include <string>
#include <vector>

namespace XlsxReader {
    std::vector<std::vector<std::string>> Read(const std::string &filePath, int sheetId, int startRow, const std::vector<int> &targetColumns);
}
