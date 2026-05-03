#pragma once

#include <string>
#include <vector>

namespace MenuOptions {
    inline const std::vector<std::string> STOR_TYPES = {"Концепт", "Дисконт"};
    inline const std::vector<std::string> REPORT_TYPES {"Текстиль", "Взуття"};

    enum STOR_TYPES {
        Concept,
        Discount
    };

    enum REPORT_TYPES {
        Textile,
        Footwear
    };

    constexpr int Exit = 2;
}
