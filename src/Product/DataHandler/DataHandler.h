#pragma once

#include <vector>
#include "../Product.h"

namespace DataHandler {
    std::map<std::string, Product> ConvertDataToProduct(const std::vector<std::vector<std::string>> &data);
}
