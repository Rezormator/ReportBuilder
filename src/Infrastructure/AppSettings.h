#pragma once

#include <string>
#include <vector>
#include "../Application/Config/StoreConfig.h"

struct TextileReportFlags {
    bool addSizes = true;
    bool addAndReplaceSizes = true;
    bool addProducts = true;
    bool lowCountStore = true;
    bool lowCountHall = true;
};

struct FootwearReportFlags {
    bool addSizes = true;
    bool lowCountStore = true;
    bool lowCountHall = true;
};

struct StoreSettings {
    std::string name;

    ReportParams textileParams;
    ReportParams footwearParams;

    TextileReportFlags textileReports;
    FootwearReportFlags footwearReports;

    bool isPreset = false;
};

inline StoreSettings MakeConceptPreset() {
    StoreSettings s;
    s.name = "Концепт";
    s.isPreset = true;

    s.textileParams = ReportParams{.minCount = 4, .maxCount = 6, .lowCount = 3};
    s.footwearParams = ReportParams{.minCount = 1, .maxCount = 1, .lowCount = 3};

    s.textileReports = TextileReportFlags{true, true, true, true, true};
    s.footwearReports = FootwearReportFlags{true, true, true};

    return s;
}

inline StoreSettings MakeDiscountPreset() {
    StoreSettings s;
    s.name = "Дисконт";
    s.isPreset = true;

    s.textileParams = ReportParams{.minCount = 1, .maxCount = 10, .lowCount = 3};
    s.footwearParams = ReportParams{.minCount = 1, .maxCount = 1, .lowCount = 3};

    s.textileReports = TextileReportFlags{true, false, true, true, true};
    s.footwearReports = FootwearReportFlags{true, true, false};

    return s;
}
