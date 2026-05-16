#include "SheetTable.h"
#include "../../Theme/Theme.h"

#include <QHeaderView>
#include <QAbstractItemView>

namespace SheetTable {
    QTableWidget *Create(const SheetData &sheetData, QWidget *parent) {
        const int dataRowCount = static_cast<int>(sheetData.rows.size());
        const int columnCount = static_cast<int>(sheetData.headers.size());

        auto *table = new QTableWidget(dataRowCount, columnCount, parent);
        table->setSelectionBehavior(QAbstractItemView::SelectItems);
        table->setSelectionMode(QAbstractItemView::ExtendedSelection);
        table->setAlternatingRowColors(true);
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table->horizontalHeader()->setStretchLastSection(true);
        table->verticalHeader()->setVisible(true);
        table->verticalHeader()->setDefaultSectionSize(24);
        table->verticalHeader()->setFixedWidth(36);
        table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        table->setStyleSheet(Theme::TableStyle());
        table->verticalHeader()->setStyleSheet(Theme::VerticalHeaderStyle());
        table->horizontalHeader()->setStyleSheet(Theme::HorizontalHeaderStyle());

        QStringList headerLabels;
        for (const auto &header: sheetData.headers) {
            headerLabels << QString::fromStdString(header);
        }
        table->setHorizontalHeaderLabels(headerLabels);

        for (int row = 0; row < dataRowCount; ++row) {
            for (int column = 0; column < columnCount; ++column) {
                QString value;
                if (column < static_cast<int>(sheetData.rows[row].size())) {
                    value = QString::fromStdString(sheetData.rows[row][column]);
                }
                auto *item = new QTableWidgetItem(value);
                item->setFlags((item->flags() & ~Qt::ItemIsEditable) | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                table->setItem(row, column, item);
            }
        }
        table->resizeColumnsToContents();

        return table;
    }
}
