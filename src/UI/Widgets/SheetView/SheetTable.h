#pragma once

#include <QTableWidget>
#include "SheetView.h"

namespace SheetTable {
    QTableWidget *Create(const SheetData &sheetData, QWidget *parent = nullptr);
}
