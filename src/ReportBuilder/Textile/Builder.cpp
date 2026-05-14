#include "Builder.h"
#include <algorithm>
#include <iostream>

#include "../../Configurations/SizePriority.h"
#include "../Priority/Priority.h"
#include "../Validation/Validation.h"

namespace Builder {
    std::vector<std::vector<std::string>> AddSizes(const std::map<std::string, Product> &products, const ReportConfigurations &configurations) {
        std::vector<std::vector<std::string>> addSizes;
        const auto validation = std::vector{Validation::Check::MinTotalCount, Validation::Check::HallNotEmpty, Validation::Check::MaxHallCount, Validation::Check::HasStorageStock};

        for (const auto &[id, product]: products) {
            if (!CanProductBeAdded(product, validation, configurations)) {
                continue;
            }

            const auto maxCount = product.totalCount < configurations.maxCount
                                      ? product.totalCount
                                      : configurations.maxCount;

            auto currentSizes = Priority::GetCurrentSizes(product);
            auto targetSizes = Priority::GetTargetSizes(product, maxCount);

            std::map<std::string, int> addSizesCount;
            for (const auto &[size, _]: product.sizes) {
                addSizesCount[size] = 0;
            }

            int hallCount = product.hallCount;
            for (int i = 0; i < targetSizes.size() && hallCount < maxCount; i++) {
                if (targetSizes[i] && !currentSizes[i]) {
                    addSizesCount[product.priority[i % product.priority.size()]]++;
                    hallCount++;
                }
            }

            for (const auto &[size, count]: addSizesCount) {
                if (count <= 0) {
                    continue;
                }
                addSizes.push_back({product.id, size, product.description, product.position, std::to_string(count)});
            }
        }

        std::ranges::sort(addSizes, [](const auto &a, const auto &b) {
            return std::tie(a[3], a[0]) < std::tie(b[3], b[0]);
        });

        return addSizes;
    }

    std::pair<std::vector<std::vector<std::string>>, std::vector<std::vector<std::string> >> AddAndReplaceSizes(
        const std::map<std::string, Product> &products, const ReportConfigurations &configurations) {

        std::vector<std::vector<std::string>> addSizes;
        std::vector<std::vector<std::string>> replaceSizes;
        const auto validation = std::vector{Validation::Check::MinTotalCount, Validation::Check::HasStorageStock, Validation::Check::HallNotEmpty};

        for (const auto &[id, product]: products) {
            if (!CanProductBeAdded(product, validation, configurations)) {
                continue;
            }

            const auto maxCount = product.totalCount < configurations.maxCount
                                      ? product.totalCount
                                      : configurations.maxCount;

            auto currentSizes = Priority::GetCurrentSizes(product);
            auto targetSizes = Priority::GetTargetSizes(product, maxCount);

            std::map<std::string, std::pair<int, int>> processSizesCount;
            for (const auto &[size, _]: product.sizes) {
                processSizesCount[size].first = 0;
                processSizesCount[size].second = 0;
            }

            // TODO Questionable
            if (std::count(currentSizes.end() - static_cast<long>(product.priority.size()), currentSizes.end(), true) ==
                std::count(targetSizes.end() - static_cast<long>(product.priority.size()), targetSizes.end(), true) &&
                currentSizes.size() == targetSizes.size() &&
                product.hallCount == maxCount) {
                continue;
            }

            int hallCount = 0;
            for (int i = 0; i < targetSizes.size(); i++) {
                if (targetSizes[i] && !currentSizes[i]) {
                    processSizesCount[product.priority[i % product.priority.size()]].first++;
                    hallCount++;
                }
                if (!targetSizes[i] && currentSizes[i]) {
                    processSizesCount[product.priority[i % product.priority.size()]].second++;
                }
                if (targetSizes[i] && currentSizes[i]) {
                    hallCount++;
                }
            }

            for (const auto &[size, count]: processSizesCount) {
                if (count.first <= 0 && count.second <= 0) {
                    continue;
                }
                if (count.first > 0) {
                    addSizes.push_back({
                        product.id, size, product.description, product.position, std::to_string(count.first)
                    });
                } else {
                    replaceSizes.push_back({
                        product.id, size, product.description, product.position, std::to_string(count.second)
                    });
                }
            }
        }

        std::ranges::sort(addSizes, [](const auto &a, const auto &b) {
            return std::tie(a[3], a[0]) < std::tie(b[3], b[0]);
        });

        std::ranges::sort(replaceSizes, [](const auto &a, const auto &b) {
            return std::tie(a[3], a[0]) < std::tie(b[3], b[0]);
        });

        return {addSizes, replaceSizes};
    }

    std::vector<std::vector<std::string>> AddProducts(const std::map<std::string, Product> &products,
                                                       const ReportConfigurations &configurations) {
        std::vector<std::vector<std::string>> addProducts;
        const auto validation = std::vector{Validation::Check::MinTotalCount, Validation::Check::HallIsEmpty};

        for (const auto &[id, product]: products) {
            if (!CanProductBeAdded(product, validation, configurations)) {
                continue;
            }

            addProducts.push_back({
                product.id, product.description, product.position, std::to_string(product.totalCount)
            });
        }

        std::ranges::sort(addProducts, [](const auto &a, const auto &b) {
            return std::tie(a[2], a[0]) < std::tie(b[2], b[0]);
        });

        return addProducts;
    }

    std::vector<std::vector<std::string>> LowCountProducts(const std::map<std::string, Product> &products,
                                                            const ReportConfigurations &configurations, const bool atHall) {
        std::vector<std::vector<std::string>> lowCountProducts;

        auto validation = std::vector{Validation::Check::UnderMinCount};
        if (atHall) {
            validation.push_back(Validation::Check::HallNotEmpty);
        }

        for (const auto &[id, product]: products) {
            if (!CanProductBeAdded(product, validation, configurations)) {
                continue;
            }

            lowCountProducts.push_back({
                product.id, product.description, product.position,
                std::to_string(product.hallCount), std::to_string(product.storageCount),
                std::to_string(product.totalCount)
            });
        }

        std::ranges::sort(lowCountProducts, [](const auto &a, const auto &b) {
            return std::tie(a[2], a[0]) < std::tie(b[2], b[0]);
        });

        return lowCountProducts;
    }

    std::vector<std::vector<std::string>> LowSizeCountProducts(const std::map<std::string, Product> &products, const ReportConfigurations &configurations, const bool atHall) {
        std::vector<std::vector<std::string>> lowCountSizeProducts;

        auto validation = std::vector{Validation::Check::UnderMinSizeCount};
        if (atHall) {
            validation.push_back(Validation::Check::HallNotEmpty);
        }

        for (const auto &[id, product]: products) {
            if (!CanProductBeAdded(product, validation, configurations)) {
                continue;
            }

            lowCountSizeProducts.push_back({
                product.id, product.description, product.position,
                std::to_string(product.hallCount), std::to_string(product.storageCount),
                std::to_string(product.totalCount)
            });
        }

        std::ranges::sort(lowCountSizeProducts, [](const auto &a, const auto &b) {
            return std::tie(a[2], a[0]) < std::tie(b[2], b[0]);
        });

        return lowCountSizeProducts;
    }

    std::vector<std::vector<std::string>> AddFootwearSizes(std::map<std::string, Product> &products, const ReportConfigurations &configurations) {
        std::vector<std::vector<std::string>> addSizes;
        const auto validation = std::vector{Validation::Check::MinTotalCount, Validation::Check::MaxHallCount, Validation::Check::HasStorageStock};

        for (auto &[id, product]: products) {
            if (!CanProductBeAdded(product, validation, configurations)) {
                continue;
            }

            if (id == "GZ5891") {
                auto d = 0;
            }

            const auto maxCount = product.totalCount < configurations.maxCount
                                      ? product.totalCount
                                      : configurations.maxCount;

            std::vector<std::vector<std::string>> priorities;
            if (product.targetGroup == TargetGroup::Unisex) {
                priorities = {SizePriority::MEN_UNISEX_FOOTWEAR, SizePriority::WOMEN_UNISEX_FOOTWEAR};
            }
            else {
                priorities = {product.priority};
            }

            for (const auto& priority : priorities) {
                product.priority = priority;
                auto currentSizes = Priority::GetCurrentSizes(product);
                auto targetSizes = Priority::GetTargetSizes(product, maxCount);

                std::map<std::string, int> addSizesCount;
                for (const auto &[size, _]: product.sizes) {
                    if (std::ranges::find(product.priority, size) != product.priority.end()) {
                        addSizesCount[size] = 0;
                    }
                }

                int hallCount = product.hallCount;
                for (int i = 0; i < targetSizes.size() && hallCount < maxCount; i++) {
                    if (targetSizes[i] && !currentSizes[i]) {
                        addSizesCount[product.priority[i % product.priority.size()]]++;
                        hallCount++;
                    }
                }

                for (const auto &[size, count]: addSizesCount) {
                    if (count <= 0) {
                        continue;
                    }
                    addSizes.push_back({product.id, size, product.description, product.position, std::to_string(count)});
                }
            }

            if (product.targetGroup == TargetGroup::Unisex) {
                product.priority = SizePriority::UNISEX_FOOTWEAR;
            }
        }

        std::ranges::sort(addSizes, [](const auto &a, const auto &b) {
            return std::tie(a[3], a[0]) < std::tie(b[3], b[0]);
        });

        return addSizes;
    }
}
