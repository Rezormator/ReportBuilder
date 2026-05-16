#pragma once

#include <string>
#include <vector>
#include "../../Domain/TargetGroup.h"

namespace SizePriority {
    extern const std::vector<std::string> MEN_TEXTILE;
    extern const std::vector<std::string> MEN_PANTS;
    extern const std::vector<std::string> MEN_JEANS;

    extern const std::vector<std::string> WOMEN_TEXTILE;
    extern const std::vector<std::string> WOMEN_BRA;
    extern const std::vector<std::string> WOMEN_JEANS_1;
    extern const std::vector<std::string> WOMEN_JEANS_2;

    extern const std::vector<std::string> KIDS_TEXTILE_1;
    extern const std::vector<std::string> KIDS_TEXTILE_2;
    extern const std::vector<std::string> KIDS_TEXTILE_3;
    extern const std::vector<std::string> KIDS_TEXTILE_4;
    extern const std::vector<std::string> KIDS_TEXTILE_5;

    extern const std::vector<std::string> MEN_FOOTWEAR;
    extern const std::vector<std::string> MEN_UNISEX_FOOTWEAR;
    extern const std::vector<std::string> WOMEN_FOOTWEAR;
    extern const std::vector<std::string> WOMEN_UNISEX_FOOTWEAR;
    extern const std::vector<std::string> UNISEX_FOOTWEAR;

    extern const std::vector<std::string> KIDS_FOOTWEAR_1;
    extern const std::vector<std::string> KIDS_FOOTWEAR_2;
    extern const std::vector<std::string> KIDS_FOOTWEAR_3;

    extern const std::vector<std::pair<TargetGroup, std::vector<std::string>>> ALL_PRIORITIES;
}
