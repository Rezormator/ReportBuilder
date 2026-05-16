#pragma once

#include <map>
#include <string>
#include <vector>
#include "../../Domain/Product.h"

namespace DataHandler {
    std::map<std::string, Product> Parse(const std::vector<std::vector<std::string>> &data);
}
