#pragma once

#include <map>
#include <string>
#include <vector>
#include "../ProductSize.h"
#include "../TargetGroup.h"

class SizeGrid {
public:
    SizeGrid(const std::map<std::string, ProductSize> &sizes, const TargetGroup &group);

    [[nodiscard]] const std::vector<std::string> &GetPriority() const;
    void SetPriority(const std::vector<std::string> &priority);

    [[nodiscard]] std::vector<bool> Current() const;
    [[nodiscard]] std::vector<bool> Target(int maxCount) const;

private:
    std::vector<std::string> priority;
    std::map<std::string, ProductSize> sizes;

    void AssignPriority(const TargetGroup &group);
};
