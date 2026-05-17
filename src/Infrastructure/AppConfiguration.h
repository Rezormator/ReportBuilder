#pragma once

#include <string>
#include <vector>

struct AppConfiguration {
    std::string textilesPath = "../TextileReports.xlsx";
    std::string footwearPath = "../FootwearReports.xlsx";

    int readSheetId = 0;
    int startRow = 10;
};
