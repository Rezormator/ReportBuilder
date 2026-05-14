#include "Priority.h"

#include <algorithm>
#include <numeric>

namespace Priority {
    std::vector<bool> GetCurrentSizes(const Product &product) {
        std::vector currentSizes(product.priority.size(), false);

        for (const auto &[size, productSize]: product.sizes) {
            if (productSize.hallCount == 0 || std::ranges::find(product.priority, size) == product.priority.end()) {
                continue;
            }

            const int extendBy = productSize.hallCount - currentSizes.size() / product.priority.size();
            if (extendBy > 0) {
                currentSizes.insert(currentSizes.end(), extendBy * product.priority.size(), false);
            }

            for (int i = 0; i < product.priority.size(); i++) {
                if (size != product.priority[i]) {
                    continue;
                }

                for (int j = 0; j < productSize.hallCount; j++) {
                    currentSizes[i + j * product.priority.size()] = true;
                }

                break;
            }
        }

        return currentSizes;
    }

    std::vector<bool> GetTargetSizes(const Product &product, const int maxCount) {
        std::vector<bool> targetSizes;
        std::map sizes(product.sizes.begin(), product.sizes.end());

        auto totalAvailable = 0;
        for (const auto &[size, productSize]: product.sizes) {
            if (std::ranges::find(product.priority, size) != product.priority.end()) {
                totalAvailable += productSize.totalCount;
            }
        }

        auto targetSizesAdded = 0;
        for (int i = 0; targetSizesAdded < maxCount && targetSizesAdded < totalAvailable; i++) {
            targetSizes.insert(targetSizes.end(), product.priority.size(), false);
            for (int j = 0; j < product.priority.size() && targetSizesAdded < maxCount; j++) {
                if (sizes[product.priority[j]].totalCount <= 0) {
                    continue;
                }

                sizes[product.priority[j]].totalCount--;
                targetSizes[i * product.priority.size() + j] = true;
                targetSizesAdded++;
            }
        }

        return targetSizes;
    }
}
