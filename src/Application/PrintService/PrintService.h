#pragma once

#include <QString>
#include <QWidget>
#include <QTableWidget>

namespace PrintService {
    void Print(const QTableWidget *table, const QString &title, QWidget *parent = nullptr);
}
