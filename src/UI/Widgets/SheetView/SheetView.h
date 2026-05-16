#pragma once

#include <QWidget>
#include <QTabWidget>
#include <QTableWidget>
#include <QString>
#include <QList>
#include <vector>
#include <string>

struct SheetData {
    QString name;
    std::vector<std::string> headers;
    std::vector<std::vector<std::string>> rows;
};

class SheetView : public QTabWidget {
    Q_OBJECT

public:
    explicit SheetView(QWidget *parent = nullptr);

    void Load(const QList<SheetData> &sheets);
    void Clear();

    [[nodiscard]] QTableWidget *ActiveTable() const;
    [[nodiscard]] QString ActiveTabText() const;
};
