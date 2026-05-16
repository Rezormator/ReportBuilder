#pragma once

#include <QString>
#include <QList>
#include "../../UI/Widgets/SheetView/SheetView.h"

namespace XlsxLoader {
    QList<SheetData> Load(const QString &filePath);
}
