#pragma once

#include <vector>

namespace XlsxConfiguration {
    constexpr auto TEXTILE_PATH = "../../TextileReports.xlsx";
    constexpr auto FOOTWEAR_PATH = "../../FootwearReports.xlsx";
    constexpr int READ_SHEET_ID = 0;
    constexpr int START_ROW = 10;
    inline const std::vector<int> TARGET_COLUMNS = {1, 4, 6, 7, 8, 11, 12};
}