#pragma once

#include <vector>
#include "../../Configurations/ReportConfigurations.h"
#include "../../Product/Product.h"

namespace Validation {
    enum class Check {
        MinTotalCount,
        MaxHallCount,
        HasStorageStock,
        HallNotEmpty,
        HallIsEmpty,
        UnderMinCount,
        UnderMinSizeCount
    };

    bool CanProductBeAdded(const Product &product, const std::vector<Check> &options, const ReportConfigurations &configurations);
}
