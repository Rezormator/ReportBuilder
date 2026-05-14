#pragma once

#include <vector>
#include "../../Product/Product.h"

namespace Priority {
    std::vector<bool> GetCurrentSizes(const Product &product);
    std::vector<bool> GetTargetSizes(const Product &product, int maxCount);
}
