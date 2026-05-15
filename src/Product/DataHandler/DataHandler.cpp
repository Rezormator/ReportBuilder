#include "DataHandler.h"
#include <iostream>
#include <set>
#include "../TargetGroup.h"
#include "../../ReportBuilder/Priority/SizePriority.h"

namespace DataHandler {
    enum Columns {
        Id,
        Size,
        Position,
        PositionSecondary,
        Description,
        StorageCount,
        HallCount
    };

    const std::map<std::string, TargetGroup> targetGroupMap = {
        {"чол.", TargetGroup::Men},
        {"жiн.", TargetGroup::Women},
        {"дит.", TargetGroup::Kids},
        {"дор.", TargetGroup::Unisex}
    };

    TargetGroup GetTargetGroupByDescription(const std::string &description) {
        const std::string targetGroupName = description.substr(description.find_last_of(' ') + 1);
        if (const auto it = targetGroupMap.find(targetGroupName); it != targetGroupMap.end()) {
            return it->second;
        }
        return TargetGroup::Men;
    }

    void GetPriority(Product &product) {
        bool correctPriority = false;

        for (const auto &[group, priority]: SizePriority::ALL_PRIORITIES) {
            if (group != product.targetGroup) {
                continue;
            }

            correctPriority = true;
            for (const auto& [productSize, _] : product.sizes) {
                auto it = std::ranges::find(priority, productSize);
                if (it == priority.end()) {
                    correctPriority = false;
                    break;
                }
            }

            if (correctPriority) {
                product.priority = priority;
                break;
            }
        }

        if (!correctPriority) {
            std::vector<std::string> newPriority;
            for (const auto &[productSize, _]: product.sizes) {
                newPriority.push_back(productSize);
            }
            product.priority = newPriority;
        }
    }

    std::string GetSize(const std::string &size) {
        std::string newSize;
        bool foundAlpha = false;

        for (const char c : size) {
            auto uc = static_cast<unsigned char>(c);

            if (std::isalpha(uc)) {
                newSize += c;
                foundAlpha = true;
            }
            else if (std::isdigit(uc) && !foundAlpha) {
                newSize += c;
            }
            else if (c == '-') {
                newSize += c;
            }
            else {
                break;
            }
        }

        return newSize;
    }

    std::map<std::string, Product> ConvertDataToProduct(const std::vector<std::vector<std::string> > &data) {
        std::map<std::string, Product> products;

        for (auto dataRow: data) {
            if (!products.contains(dataRow[Id])) {
                Product product;
                product.id = dataRow[Id];
                product.description = dataRow[Description];
                product.position = dataRow[PositionSecondary].empty()
                                       ? dataRow[Position]
                                       : dataRow[Position] + '/' + dataRow[PositionSecondary];
                product.targetGroup = GetTargetGroupByDescription(dataRow[Description]);
                products[dataRow[Id]] = product;
            }

            ProductSize productSize;
            productSize.size = GetSize(dataRow[Size]);
            productSize.hallCount = dataRow[HallCount].empty() ? 0 : std::stoi(dataRow[HallCount]);
            productSize.storageCount = dataRow[StorageCount].empty() ? 0 : std::stoi(dataRow[StorageCount]);
            productSize.totalCount = productSize.hallCount + productSize.storageCount;

            if (products[dataRow[Id]].sizes.contains(productSize.size)) {
                products[dataRow[Id]].sizes[productSize.size].hallCount += productSize.hallCount;
                products[dataRow[Id]].sizes[productSize.size].storageCount += productSize.storageCount;
                products[dataRow[Id]].sizes[productSize.size].totalCount += productSize.totalCount;

                products[dataRow[Id]].hallCount += productSize.hallCount;
                products[dataRow[Id]].storageCount += productSize.storageCount;
                products[dataRow[Id]].totalCount += productSize.totalCount;
            } else {
                products[dataRow[Id]].sizes[productSize.size] = productSize;
                products[dataRow[Id]].hallCount += productSize.hallCount;
                products[dataRow[Id]].storageCount += productSize.storageCount;
                products[dataRow[Id]].totalCount += productSize.totalCount;
            }
        }

        for (auto &[_, product] : products) {
            GetPriority(product);

            if (product.priority == SizePriority::UNISEX_FOOTWEAR) {
                product.targetGroup = TargetGroup::Unisex;
            }
        }

        return products;
    }
}
