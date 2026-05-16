#include "PrintService.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QFont>
#include <QRect>

namespace PrintService {
    void Print(const QTableWidget *table, const QString &title, QWidget *parent) {
        if (!table || table->rowCount() == 0) {
            return;
        }

        QPrinter printer(QPrinter::HighResolution);
        printer.setPageOrientation(QPageLayout::Landscape);

        QPrintDialog dialog(&printer, parent);
        dialog.setWindowTitle("Друк звіту");
        if (dialog.exec() != QDialog::Accepted) {
            return;
        }

        QPainter painter(&printer);
        const QRect pageRect = printer.pageRect(QPrinter::DevicePixel).toRect();

        const QFont titleFont("Arial", 14, QFont::Bold);
        painter.setFont(titleFont);
        painter.drawText(pageRect, Qt::AlignHCenter | Qt::AlignTop, title);

        const int columnCount = table->columnCount();
        const int rowCount = table->rowCount();

        const int columnWidth = pageRect.width() / (columnCount > 0 ? columnCount : 1);
        const int rowHeight = pageRect.height() / 30;
        int currentY = rowHeight * 2;

        const QFont cellFont("Arial", 9);
        painter.setFont(cellFont);

        for (int column = 0; column < columnCount; column++) {
            const QRect cellRect(pageRect.left() + column * columnWidth, currentY, columnWidth, rowHeight);
            painter.drawRect(cellRect);
            painter.drawText(cellRect.adjusted(2, 2, -2, -2), Qt::AlignLeft | Qt::AlignVCenter,
                             table->horizontalHeaderItem(column)
                                 ? table->horizontalHeaderItem(column)->text()
                                 : "");
        }
        currentY += rowHeight;

        for (int row = 0; row < rowCount; row++) {
            if (currentY + rowHeight > pageRect.bottom()) {
                printer.newPage();
                currentY = rowHeight;
            }
            for (int column = 0; column < columnCount; column++) {
                const QRect cellRect(pageRect.left() + column * columnWidth, currentY, columnWidth, rowHeight);
                painter.drawRect(cellRect);
                painter.drawText(cellRect.adjusted(2, 2, -2, -2), Qt::AlignLeft | Qt::AlignVCenter,
                                 table->item(row, column) ? table->item(row, column)->text() : "");
            }
            currentY += rowHeight;
        }

        painter.end();
    }
}
