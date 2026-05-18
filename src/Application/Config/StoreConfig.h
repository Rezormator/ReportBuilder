#pragma once

#include <string>
#include <vector>
#include "ReportDef.h"
#include "../../Domain/Validation/Validation.h"

struct StoreConfig {
    std::string filePath;
    ReportParams params;
    std::vector<ReportDef> reports;
};

StoreConfig MakeTextileConfig(const ReportParams &params, struct TextileReportFlags flags);
StoreConfig MakeFootwearConfig(const ReportParams &params, struct FootwearReportFlags flags);
