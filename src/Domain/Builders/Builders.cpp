#include "Builders.h"
#include "../SizeGrid/SizeGrid.h"
#include "../../Infrastructure/SizePriority/SizePriority.h"

#include <algorithm>

namespace Builders {
    ReportRows AddSizes(const std::map<std::string, Product> &products, const ReportParams &params) {
        ReportRows result;

        const auto checks = std::vector{
            Validation::Check::MinTotalCount,
            Validation::Check::HallNotEmpty,
            Validation::Check::MaxHallCount,
            Validation::Check::HasStorageStock
        };

        for (const auto &[id, product]: products) {
            if (!CanProductBeAdded(product, checks, params)) {
                continue;
            }

            SizeGrid sizeGrid(product.sizes, product.targetGroup);
            const int maxCount = std::min(product.totalCount, params.maxCount);

            auto currentSlots = sizeGrid.Current();
            auto targetSlots = sizeGrid.Target(maxCount);

            if (currentSlots.size() < targetSlots.size()) {
                currentSlots.resize(targetSlots.size(), false);
            }

            std::map<std::string, int> sizesToAdd;
            for (const auto &[size, _]: product.sizes) {
                sizesToAdd[size] = 0;
            }

            int hallCount = product.hallCount;
            for (int index = 0; index < static_cast<int>(targetSlots.size()) && hallCount < maxCount; index++) {
                if (targetSlots[index] && !currentSlots[index]) {
                    sizesToAdd[sizeGrid.GetPriority()[index % sizeGrid.GetPriority().size()]]++;
                    hallCount++;
                }
            }

            for (const auto &[size, count]: sizesToAdd) {
                if (count > 0) {
                    result.push_back({
                        product.id, size, product.description,
                        product.position, std::to_string(count)
                    });
                }
            }
        }

        std::ranges::sort(result, [](const auto &rowA, const auto &rowB) {
            return std::tie(rowA[3], rowA[0]) < std::tie(rowB[3], rowB[0]);
        });

        return result;
    }

    std::pair<ReportRows, ReportRows> AddAndReplaceSizes(const std::map<std::string, Product> &products,
                                                         const ReportParams &params) {
        ReportRows toAdd;
        ReportRows toRemove;

        const auto checks = std::vector{
            Validation::Check::MinTotalCount,
            Validation::Check::HasStorageStock,
            Validation::Check::HallNotEmpty
        };

        for (const auto &[id, product]: products) {
            if (!CanProductBeAdded(product, checks, params)) {
                continue;
            }

            SizeGrid sizeGrid(product.sizes, product.targetGroup);
            const int maxCount = std::min(product.totalCount, params.maxCount);

            auto currentSlots = sizeGrid.Current();
            auto targetSlots = sizeGrid.Target(maxCount);
            if (currentSlots.size() < targetSlots.size()) {
                currentSlots.resize(targetSlots.size(), false);
            }

            std::map<std::string, std::pair<int, int> > sizeCounts;
            for (const auto &[size, _]: product.sizes) {
                sizeCounts[size] = {0, 0};
            }

            for (int index = 0; index < static_cast<int>(targetSlots.size()); index++) {
                const auto &size = sizeGrid.GetPriority()[index % sizeGrid.GetPriority().size()];
                if (targetSlots[index] && !currentSlots[index]) {
                    sizeCounts[size].first++;
                }
                if (!targetSlots[index] && currentSlots[index]) {
                    sizeCounts[size].second++;
                }
            }


            for (const auto &[size, counts]: sizeCounts) {
                if (counts.first > 0) {
                    toAdd.push_back({
                        product.id, size, product.description,
                        product.position, std::to_string(counts.first)
                    });
                } else if (counts.second > 0) {
                    toRemove.push_back({
                        product.id, size, product.description,
                        product.position, std::to_string(counts.second)
                    });
                }
            }
        }

        auto sortByPositionThenId = [](const auto &rowA, const auto &rowB) {
            return std::tie(rowA[3], rowA[0]) < std::tie(rowB[3], rowB[0]);
        };

        std::ranges::sort(toAdd, sortByPositionThenId);
        std::ranges::sort(toRemove, sortByPositionThenId);

        return {toAdd, toRemove};
    }

    ReportRows AddProducts(const std::map<std::string, Product> &products, const ReportParams &params) {
        ReportRows result;

        const auto checks = std::vector{
            Validation::Check::MinTotalCount,
            Validation::Check::HallIsEmpty
        };

        for (const auto &[id, product]: products) {
            if (!CanProductBeAdded(product, checks, params)) {
                continue;
            }
            result.push_back({
                product.id, product.description,
                product.position, std::to_string(product.totalCount)
            });
        }

        std::ranges::sort(result, [](const auto &rowA, const auto &rowB) {
            return std::tie(rowA[2], rowA[0]) < std::tie(rowB[2], rowB[0]);
        });

        return result;
    }

    ReportRows LowCount(const std::map<std::string, Product> &products, const ReportParams &params, const bool atHall) {
        ReportRows result;

        auto checks = std::vector{Validation::Check::LowCount};
        if (atHall) {
            checks.push_back(Validation::Check::HallNotEmpty);
        }

        for (const auto &[id, product]: products) {
            if (!CanProductBeAdded(product, checks, params)) {
                continue;
            }
            result.push_back({
                product.id, product.description, product.position,
                std::to_string(product.hallCount),
                std::to_string(product.storageCount),
                std::to_string(product.totalCount)
            });
        }

        std::ranges::sort(result, [](const auto &rowA, const auto &rowB) {
            return std::tie(rowA[2], rowA[0]) < std::tie(rowB[2], rowB[0]);
        });

        return result;
    }

    ReportRows AddFootwearSizes(const std::map<std::string, Product> &products, const ReportParams &params) {
        ReportRows result;

        const auto checks = std::vector{
            Validation::Check::MinTotalCount,
            Validation::Check::MaxHallCount,
            Validation::Check::HasStorageStock,
            Validation::Check::AboveMinSizeCount
        };

        for (auto &[id, product]: products) {
            if (!CanProductBeAdded(product, checks, params)) {
                continue;
            }

            const int maxCount = std::min(product.totalCount, params.maxCount);

            std::vector<std::vector<std::string> > priorityGroups;
            if (product.targetGroup == TargetGroup::Unisex) {
                priorityGroups = {
                    SizePriority::MEN_UNISEX_FOOTWEAR,
                    SizePriority::WOMEN_UNISEX_FOOTWEAR
                };
            } else {
                SizeGrid sizeGrid(product.sizes, product.targetGroup);
                priorityGroups = {sizeGrid.GetPriority()};
            }

            for (const auto &priority: priorityGroups) {
                SizeGrid sizeGrid(product.sizes, product.targetGroup);
                sizeGrid.SetPriority(priority);

                auto currentSlots = sizeGrid.Current();
                auto targetSlots = sizeGrid.Target(maxCount);

                std::map<std::string, int> sizesToAdd;
                for (const auto &[size, _]: product.sizes) {
                    if (std::ranges::find(priority, size) != priority.end()) {
                        sizesToAdd[size] = 0;
                    }
                }

                int hallCount = product.hallCount;
                for (int index = 0; index < static_cast<int>(targetSlots.size()) && hallCount < maxCount; index++) {
                    if (targetSlots[index] && !currentSlots[index]) {
                        sizesToAdd[priority[index % priority.size()]]++;
                        hallCount++;
                    }
                }

                for (const auto &[size, count]: sizesToAdd) {
                    if (count > 0) {
                        result.push_back({
                            product.id, size, product.description,
                            product.position, std::to_string(count)
                        });
                    }
                }
            }
        }

        std::ranges::sort(result, [](const auto &rowA, const auto &rowB) {
            return std::tie(rowA[3], rowA[0]) < std::tie(rowB[3], rowB[0]);
        });

        return result;
    }
}
