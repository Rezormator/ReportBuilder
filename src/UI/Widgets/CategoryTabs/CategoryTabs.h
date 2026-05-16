#pragma once

#include <QTabWidget>
#include "../../Widgets/SheetView/SheetView.h"

class CategoryTabs : public QTabWidget {
    Q_OBJECT

public:
    explicit CategoryTabs(QWidget *parent = nullptr);

    [[nodiscard]] SheetView *TextileView() const { return m_textileView;  }
    [[nodiscard]] SheetView *FootwearView() const { return m_footwearView; }
    [[nodiscard]] SheetView *ActiveSheetView() const;

signals:
    void SheetChanged(const QString &sheetName, int rowCount);

private slots:
    void OnSheetTabChanged(int);

private:
    SheetView *m_textileView = nullptr;
    SheetView *m_footwearView = nullptr;
};
