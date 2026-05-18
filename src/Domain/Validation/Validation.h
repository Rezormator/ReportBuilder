#pragma once

#include <vector>
#include "../Product.h"

struct ReportParams {
    int minCount = 4;
    int maxCount = 6;
    int lowCount = 3;
};

namespace Validation {
    enum class Check {
        MinTotalCount,
        MaxHallCount,
        HasStorageStock,
        HallNotEmpty,
        HallIsEmpty,
        UnderMinCount,
        AboveMinCount,
        LowCount
    };

    bool CanProductBeAdded(const Product &product, const std::vector<Check> &checks, const ReportParams &params);
}
