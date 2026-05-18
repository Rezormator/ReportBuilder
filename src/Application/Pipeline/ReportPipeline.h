#pragma once

#include "../Config/StoreConfig.h"
#include "../../Infrastructure/AppSettings.h"
#include <vector>
#include <string>

namespace ReportPipeline {
    extern const std::vector<std::string> ALL_REPORT_SHEETS;

    void Run(const StoreConfig &config);
    void RunAll(const std::vector<StoreSettings> &allSettings);
}
