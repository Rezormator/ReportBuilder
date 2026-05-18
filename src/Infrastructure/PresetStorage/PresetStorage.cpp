#include "PresetStorage.h"
#include <QSettings>
#include <QString>

namespace PresetStorage {
    static constexpr auto ORG = "ReportBuilder";
    static constexpr auto APP = "ReportBuilder";
    static constexpr auto GRP = "presets";

    void Save(const std::vector<StoreSettings> &presets) {
        QSettings s(ORG, APP);
        s.remove(GRP);
        s.beginWriteArray(GRP);

        int idx = 0;
        for (const auto &p: presets) {
            if (p.isPreset) {
                continue;
            }

            s.setArrayIndex(idx++);
            s.setValue("name", QString::fromStdString(p.name));

            s.setValue("texMin", p.textileParams.minCount);
            s.setValue("texMax", p.textileParams.maxCount);
            s.setValue("texLow", p.textileParams.lowCount);

            s.setValue("texAddSizes", p.textileReports.addSizes);
            s.setValue("texAddReplace", p.textileReports.addAndReplaceSizes);
            s.setValue("texAddProducts", p.textileReports.addProducts);
            s.setValue("texLowStore", p.textileReports.lowCountStore);
            s.setValue("texLowHall", p.textileReports.lowCountHall);

            s.setValue("fwMin", p.footwearParams.minCount);
            s.setValue("fwMax", p.footwearParams.maxCount);
            s.setValue("fwLow", p.footwearParams.lowCount);

            s.setValue("fwAddSizes", p.footwearReports.addSizes);
            s.setValue("fwLowStore", p.footwearReports.lowCountStore);
            s.setValue("fwLowHall", p.footwearReports.lowCountHall);
        }

        s.endArray();
    }

    std::vector<StoreSettings> Load() {
        QSettings s(ORG, APP);
        std::vector<StoreSettings> result;

        const int count = s.beginReadArray(GRP);
        for (int i = 0; i < count; ++i) {
            s.setArrayIndex(i);

            StoreSettings p;
            p.isPreset = false;
            p.name = s.value("name", "Кастом").toString().toStdString();

            p.textileParams.minCount = s.value("texMin", 1).toInt();
            p.textileParams.maxCount = s.value("texMax", 6).toInt();
            p.textileParams.lowCount = s.value("texLow", 3).toInt();

            p.textileReports.addSizes = s.value("texAddSizes", true).toBool();
            p.textileReports.addAndReplaceSizes = s.value("texAddReplace", false).toBool();
            p.textileReports.addProducts = s.value("texAddProducts", true).toBool();
            p.textileReports.lowCountStore = s.value("texLowStore", true).toBool();
            p.textileReports.lowCountHall = s.value("texLowHall", true).toBool();

            p.footwearParams.minCount = s.value("fwMin", 1).toInt();
            p.footwearParams.maxCount = s.value("fwMax", 1).toInt();
            p.footwearParams.lowCount = s.value("fwLow", 3).toInt();

            p.footwearReports.addSizes = s.value("fwAddSizes", true).toBool();
            p.footwearReports.lowCountStore = s.value("fwLowStore", true).toBool();
            p.footwearReports.lowCountHall = s.value("fwLowHall", false).toBool();

            result.push_back(p);
        }
        s.endArray();

        return result;
    }
}
