#pragma once

#include "../../UI/MenuOptions.h"

namespace ReportService {
    void FormTextileReports(const MenuOptions::STOR_TYPES &storType);
    void FormFootwearReports(const MenuOptions::STOR_TYPES &storType);
    void ClearFileSheets(const std::string& filePath, const std::vector<std::string>& sheets);
}
