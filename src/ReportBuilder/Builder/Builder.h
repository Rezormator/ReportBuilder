#pragma once

#include <map>
#include <string>
#include <vector>
#include "../ReportConfigurations.h"
#include "../../Product/Product.h"

namespace Builder {
    std::vector<std::vector<std::string>> AddSizes(const std::map<std::string, Product> &products, const ReportConfigurations &configurations);
    std::pair<std::vector<std::vector<std::string>>, std::vector<std::vector<std::string>>> AddAndReplaceSizes(
                const std::map<std::string, Product> &products, const ReportConfigurations &configurations);
    std::vector<std::vector<std::string>> AddProducts(const std::map<std::string, Product> &products, const ReportConfigurations &configurations);
    std::vector<std::vector<std::string>> LowCountProducts(const std::map<std::string, Product> &products, const ReportConfigurations &configurations, bool atHall = false);
    std::vector<std::vector<std::string>> LowSizeCountProducts(const std::map<std::string, Product> &products, const ReportConfigurations &configurations, bool atHall = false);
    std::vector<std::vector<std::string>> AddFootwearSizes(std::map<std::string, Product> &products, const ReportConfigurations &configurations);
}
