#include "SheetView.h"
#include "SheetTable.h"
#include "../../Theme/Theme.h"

#include <QLabel>

SheetView::SheetView(QWidget *parent) : QTabWidget(parent) {
    setTabPosition(QTabWidget::South);
    setStyleSheet(Theme::SheetTabStyle());
}

void SheetView::Clear() {
    while (count()) removeTab(0);
}

void SheetView::Load(const QList<SheetData> &sheets) {
    Clear();

    if (sheets.isEmpty()) {
        auto *label = new QLabel("<center><br><span style='color:#AAA;'>Немає аркушів</span></center>", this);
        label->setAlignment(Qt::AlignCenter);
        addTab(label, "—");
        return;
    }

    for (const auto &sheetData: sheets) {
        if (sheetData.rows.empty()) {
            auto *label = new QLabel("<center><br><span style='color:#AAA;'>Аркуш порожній</span></center>", this);
            label->setAlignment(Qt::AlignCenter);
            addTab(label, sheetData.name);
            continue;
        }

        auto *table = SheetTable::Create(sheetData, this);
        addTab(table, sheetData.name);
    }
}

QTableWidget *SheetView::ActiveTable() const {
    return qobject_cast<QTableWidget *>(currentWidget());
}

QString SheetView::ActiveTabText() const {
    return tabText(currentIndex());
}
