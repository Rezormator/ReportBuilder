#pragma once

#include <map>
#include <string>
#include "ProductSize.h"
#include "TargetGroup.h"

struct Product {
    std::string id;
    std::string description;
    std::string position;

    TargetGroup targetGroup = TargetGroup::Unisex;

    int hallCount = 0;
    int storageCount = 0;
    int totalCount = 0;

    std::map<std::string, ProductSize> sizes;

    std::vector<std::string> priority;
};
