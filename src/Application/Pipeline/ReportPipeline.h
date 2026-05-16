#pragma once

#include "../Config/StoreConfig.h"

namespace ReportPipeline {
    void Run(const StoreConfig &config);
    void ClearSheets();
}
