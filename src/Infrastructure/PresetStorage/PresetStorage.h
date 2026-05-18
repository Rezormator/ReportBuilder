#pragma once

#include <vector>
#include "../../Infrastructure/AppSettings.h"

namespace PresetStorage {
    void Save(const std::vector<StoreSettings> &presets);
    std::vector<StoreSettings> Load();
}
