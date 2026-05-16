#include "Validation.h"

namespace Validation {
    bool CanProductBeAdded(const Product &product, const std::vector<Check> &checks, const ReportParams &params) {
        for (const auto &check: checks) {
            bool passes = true;

            switch (check) {
                case Check::MinTotalCount:
                    passes = product.totalCount >= params.minCount;
                    break;
                case Check::MaxHallCount:
                    passes = product.hallCount < params.maxCount;
                    break;
                case Check::HasStorageStock:
                    passes = product.totalCount > product.hallCount;
                    break;
                case Check::HallNotEmpty:
                    passes = product.hallCount != 0;
                    break;
                case Check::HallIsEmpty:
                    passes = product.hallCount == 0;
                    break;
                case Check::UnderMinCount:
                    passes = product.totalCount < params.minCount;
                    break;
                case Check::UnderMinSizeCount:
                    passes = static_cast<int>(product.sizes.size()) < params.minSizeCount;
                    break;
                case Check::AboveMinSizeCount:
                    passes = static_cast<int>(product.sizes.size()) >= params.minSizeCount;
                    break;
                case Check::LowCount:
                    passes = product.totalCount <= params.lowCount;
                    break;
            }

            if (!passes) {
                return false;
            }
        }

        return true;
    }
}
