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

StoreConfig MakeConceptTextile();
StoreConfig MakeConceptFootwear();
StoreConfig MakeDiscountTextile();
StoreConfig MakeDiscountFootwear();
