#pragma once

#include <map>
#include <string>
#include <vector>
#include "../Product.h"
#include "../Validation/Validation.h"

using ReportRows = std::vector<std::vector<std::string>>;

namespace Builders {
    ReportRows AddSizes(const std::map<std::string, Product> &products, const ReportParams &params);
    std::pair<ReportRows, ReportRows> AddAndReplaceSizes(const std::map<std::string, Product> &products, const ReportParams &params);
    ReportRows AddProducts(const std::map<std::string, Product> &products, const ReportParams &params);
    ReportRows LowCount(const std::map<std::string, Product> &products, const ReportParams &params, bool atHall = false);
    ReportRows AddFootwearSizes(const std::map<std::string, Product> &products, const ReportParams &params);
}
