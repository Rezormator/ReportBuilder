#include "Validation.h"

namespace Validation {
    bool CanProductBeAdded(const Product &product, const std::vector<Check> &options, const ReportConfigurations &configurations) {
        bool canBeAdded = true;

        for (const auto &option : options) {
            switch (option) {
                case Check::MinTotalCount:
                    canBeAdded = product.totalCount >= configurations.minCount;
                    break;
                case Check::MaxHallCount:
                    canBeAdded = product.hallCount < configurations.maxCount;
                    break;
                case Check::HasStorageStock:
                    canBeAdded = product.totalCount > product.hallCount;
                    break;
                case Check::HallNotEmpty:
                    canBeAdded = product.hallCount != 0;
                    break;
                case Check::HallIsEmpty:
                    canBeAdded = product.hallCount == 0;
                    break;
                case Check::UnderMinCount:
                    canBeAdded = product.totalCount < configurations.minCount;
                    break;
                case Check::UnderMinSizeCount:
                    canBeAdded = product.sizes.size() < configurations.minSizeCount;
                    break;
                case Check::AboveMinSizeCount:
                    canBeAdded = product.sizes.size() >= configurations.minSizeCount;
                break;
                default:
                    break;
            }

            if (!canBeAdded) {
                return canBeAdded;
            }
        }

        return canBeAdded;
    }
}
