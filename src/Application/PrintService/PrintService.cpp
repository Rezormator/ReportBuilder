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

        const int rowNumWidth = pageRect.width() / 30;
        const int columnWidth = (pageRect.width() - rowNumWidth) / (columnCount > 0 ? columnCount : 1);
        const int rowHeight = pageRect.height() / 50;
        int currentY = rowHeight * 2;

        const QFont cellFont("Arial", 9);
        painter.setFont(cellFont);

        const QRect numHeaderRect(pageRect.left(), currentY, rowNumWidth, rowHeight);
        painter.drawRect(numHeaderRect);

        for (int column = 0; column < columnCount; column++) {
            const QRect cellRect(pageRect.left() + rowNumWidth + column * columnWidth, currentY, columnWidth, rowHeight);
            painter.drawRect(cellRect);
            painter.drawText(cellRect.adjusted(2, 2, -2, -2), Qt::AlignLeft | Qt::AlignVCenter,
                table->horizontalHeaderItem(column) ? table->horizontalHeaderItem(column)->text() : "");
        }
        currentY += rowHeight;

        for (int row = 1; row < rowCount; row++) {
            if (currentY + rowHeight > pageRect.bottom()) {
                printer.newPage();
                currentY = rowHeight;
            }

            const QRect numRect(pageRect.left(), currentY, rowNumWidth, rowHeight);
            painter.drawRect(numRect);
            painter.drawText(numRect.adjusted(2, 2, -2, -2), Qt::AlignHCenter | Qt::AlignVCenter, QString::number(row + 1));

            for (int column = 0; column < columnCount; column++) {
                const QRect cellRect(pageRect.left() + rowNumWidth + column * columnWidth, currentY, columnWidth,rowHeight);
                painter.drawRect(cellRect);
                painter.drawText(cellRect.adjusted(2, 2, -2, -2), Qt::AlignLeft | Qt::AlignVCenter,
                                 table->item(row, column) ? table->item(row, column)->text() : "");
            }
            currentY += rowHeight;
        }

        painter.end();
    }
}
