#include "SizeGrid.h"
#include "../../Infrastructure/SizePriority/SizePriority.h"
#include <algorithm>

SizeGrid::SizeGrid(const std::map<std::string, ProductSize> &sizes, const TargetGroup &group) : sizes(sizes) {
    AssignPriority(group);
}

const std::vector<std::string> &SizeGrid::GetPriority() const {
    return priority;
}

void SizeGrid::SetPriority(const std::vector<std::string> &newPriority) {
    this->priority = newPriority;
}

void SizeGrid::AssignPriority(const TargetGroup &group) {
    for (const auto &[targetGroup, candidatePriority]: SizePriority::ALL_PRIORITIES) {
        if (targetGroup != group) {
            continue;
        }

        bool allSizesFound = true;
        for (const auto &[size, _]: sizes) {
            if (std::ranges::find(candidatePriority, size) == candidatePriority.end()) {
                allSizesFound = false;
                break;
            }
        }

        if (allSizesFound) {
            priority = candidatePriority;
            return;
        }
    }

    for (const auto &[size, _]: sizes) {
        priority.push_back(size);
    }
}

std::vector<bool> SizeGrid::Current() const {
    std::vector currentSlots(priority.size(), false);

    for (const auto &[size, productSize]: sizes) {
        if (productSize.hallCount == 0 || std::ranges::find(priority, size) == priority.end()) {
            continue;
        }

        const int extraRows = productSize.hallCount - static_cast<int>(currentSlots.size() / priority.size());
        if (extraRows > 0) {
            currentSlots.insert(currentSlots.end(), extraRows * static_cast<int>(priority.size()), false);
        }

        for (int priorityIndex = 0; priorityIndex < static_cast<int>(priority.size()); priorityIndex++) {
            if (size != priority[priorityIndex]) continue;
            for (int row = 0; row < productSize.hallCount; row++) {
                currentSlots[priorityIndex + row * static_cast<int>(priority.size())] = true;
            }
            break;
        }
    }

    return currentSlots;
}

std::vector<bool> SizeGrid::Target(const int maxCount) const {
    std::vector<bool> targetSlots;
    std::map<std::string, ProductSize> available(sizes);

    int totalAvailable = 0;
    for (const auto &[size, productSize]: sizes) {
        if (std::ranges::find(priority, size) != priority.end()) {
            totalAvailable += productSize.totalCount;
        }
    }

    int added = 0;
    for (int row = 0; added < maxCount && added < totalAvailable; row++) {
        targetSlots.insert(targetSlots.end(), priority.size(), false);
        for (int priorityIndex = 0; priorityIndex < static_cast<int>(priority.size()) && added < maxCount; priorityIndex++) {
            if (available[priority[priorityIndex]].totalCount <= 0) {
                continue;
            }
            available[priority[priorityIndex]].totalCount--;
            targetSlots[row * static_cast<int>(priority.size()) + priorityIndex] = true;
            added++;
        }
    }

    return targetSlots;
}
