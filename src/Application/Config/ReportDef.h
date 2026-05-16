#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>
#include "../../Domain/Product.h"
#include "../../Domain/Builders/Builders.h"

struct ReportDef {
    std::string sheetName;
    std::string header;
    std::vector<std::string> columns;

    std::function<ReportRows(const std::map<std::string, Product> &, const ReportParams &)> builder;
};
