#include "PrintService.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QFont>
#include <QRect>
#include <QFontMetrics>

namespace PrintService {
    void Print(const QTableWidget *table, const QString &title, QWidget *parent) {
        if (!table || table->rowCount() == 0) return;

        QPrinter printer(QPrinter::HighResolution);
        printer.setPageOrientation(QPageLayout::Landscape);

        QPrintDialog dialog(&printer, parent);
        dialog.setWindowTitle("Друк звіту");
        if (dialog.exec() != QDialog::Accepted) return;

        QPainter painter(&printer);
        const QRect pageRect = printer.pageRect(QPrinter::DevicePixel).toRect();

        const QFont titleFont("Arial", 14, QFont::Bold);
        const QFont cellFont("Arial", 9);

        const QFontMetrics cellMetrics(cellFont);
        const int rowHeight = cellMetrics.height() + 6;

        const QFontMetrics titleMetrics(titleFont);
        const QString maxRowNum = QString::number(table->rowCount());
        const int numColWidth = cellMetrics.horizontalAdvance(maxRowNum) + 12;

        const int columnCount = table->columnCount();
        const int rowCount = table->rowCount();
        const int dataWidth = pageRect.width() - numColWidth;
        const int columnWidth = dataWidth / (columnCount > 0 ? columnCount : 1);

        painter.setFont(titleFont);
        painter.drawText(pageRect, Qt::AlignHCenter | Qt::AlignTop, title);
        int currentY = titleMetrics.height() + 12;

        painter.setFont(cellFont);

        auto drawCell = [&](int x, int y, int w, const QString &text, bool bold = false) {
            const QRect rect(x, y, w, rowHeight);
            painter.drawRect(rect);
            if (bold) {
                QFont f = cellFont;
                f.setBold(true);
                painter.setFont(f);
            }
            painter.drawText(rect.adjusted(3, 0, -3, 0), Qt::AlignLeft | Qt::AlignVCenter, text);
            if (bold) painter.setFont(cellFont);
        };

        drawCell(pageRect.left(), currentY, numColWidth, "#", true);
        for (int col = 0; col < columnCount; ++col) {
            const QString label = table->horizontalHeaderItem(col)
                                      ? table->horizontalHeaderItem(col)->text()
                                      : "";
            drawCell(pageRect.left() + numColWidth + col * columnWidth, currentY, columnWidth, label, true);
        }
        currentY += rowHeight;

        for (int row = 0; row < rowCount; ++row) {
            if (currentY + rowHeight > pageRect.bottom()) {
                printer.newPage();
                currentY = rowHeight;

                drawCell(pageRect.left(), currentY, numColWidth, "#", true);
                for (int col = 0; col < columnCount; ++col) {
                    const QString label = table->horizontalHeaderItem(col)
                                              ? table->horizontalHeaderItem(col)->text()
                                              : "";
                    drawCell(pageRect.left() + numColWidth + col * columnWidth, currentY, columnWidth, label, true);
                }
                currentY += rowHeight;
            }

            drawCell(pageRect.left(), currentY, numColWidth, QString::number(row + 1));
            for (int col = 0; col < columnCount; ++col) {
                const QString text = table->item(row, col) ? table->item(row, col)->text() : "";
                drawCell(pageRect.left() + numColWidth + col * columnWidth, currentY, columnWidth, text);
            }
            currentY += rowHeight;
        }

        painter.end();
    }
}
