#include "DataHandler.h"
#include "../../Domain/TargetGroup.h"
#include <cctype>
#include <map>

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

    const std::map<std::string, TargetGroup> TARGET_GROUP_MAP = {
        {"чол.", TargetGroup::Men},
        {"жiн.", TargetGroup::Women},
        {"дит.", TargetGroup::Kids},
        {"дор.", TargetGroup::Unisex}
    };

    TargetGroup GetTargetGroup(const std::string &description) {
        const std::string key = description.substr(description.find_last_of(' ') + 1);
        if (const auto iterator = TARGET_GROUP_MAP.find(key); iterator != TARGET_GROUP_MAP.end()) {
            return iterator->second;
        }
        return TargetGroup::Men;
    }

    std::string ParseSize(const std::string &raw) {
        std::string result;
        bool foundAlpha = false;

        for (const char character: raw) {
            const auto unsignedChar = static_cast<unsigned char>(character);
            if (std::isalpha(unsignedChar)) {
                result += character;
                foundAlpha = true;
            } else if (std::isdigit(unsignedChar) && !foundAlpha) {
                result += character;
            } else if (character == '-') {
                result += character;
            } else {
                break;
            }
        }

        return result;
    }

    std::map<std::string, Product> Parse(const std::vector<std::vector<std::string> > &data) {
        std::map<std::string, Product> products;

        for (const auto &row: data) {
            const std::string &id = row[Id];

            if (!products.contains(id)) {
                Product product;
                product.id = id;
                product.description = row[Description];
                product.position = row[PositionSecondary].empty()
                                       ? row[Position]
                                       : row[Position] + '/' + row[PositionSecondary];
                product.targetGroup = GetTargetGroup(row[Description]);
                products[id] = product;
            }

            ProductSize productSize;
            productSize.size = ParseSize(row[Size]);
            productSize.hallCount = row[HallCount].empty() ? 0 : std::stoi(row[HallCount]);
            productSize.storageCount = row[StorageCount].empty() ? 0 : std::stoi(row[StorageCount]);
            productSize.totalCount = productSize.hallCount + productSize.storageCount;

            auto &product = products[id];

            if (product.sizes.contains(productSize.size)) {
                product.sizes[productSize.size].hallCount += productSize.hallCount;
                product.sizes[productSize.size].storageCount += productSize.storageCount;
                product.sizes[productSize.size].totalCount += productSize.totalCount;
            } else {
                product.sizes[productSize.size] = productSize;
            }

            product.hallCount += productSize.hallCount;
            product.storageCount += productSize.storageCount;
            product.totalCount += productSize.totalCount;
        }

        return products;
    }
}
