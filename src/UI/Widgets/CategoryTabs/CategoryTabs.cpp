#include "CategoryTabs.h"
#include "../../Theme/Theme.h"

CategoryTabs::CategoryTabs(QWidget *parent) : QTabWidget(parent) {
    setDocumentMode(true);
    setTabPosition(QTabWidget::North);
    setStyleSheet(Theme::MainTabStyle());

    m_textileView  = new SheetView(this);
    m_footwearView = new SheetView(this);

    addTab(m_textileView,  "Текстиль");
    addTab(m_footwearView, "Взуття");

    auto connectSheetView = [this](SheetView *sheetView) {
        connect(sheetView, &QTabWidget::currentChanged, this, &CategoryTabs::OnSheetTabChanged);
    };
    connectSheetView(m_textileView);
    connectSheetView(m_footwearView);
}

SheetView *CategoryTabs::ActiveSheetView() const {
    return (currentIndex() == 0) ? m_textileView : m_footwearView;
}

void CategoryTabs::OnSheetTabChanged(int) {
    SheetView *sheetView = ActiveSheetView();
    if (!sheetView) {
        return;
    }
    auto *table = sheetView->ActiveTable();
    emit SheetChanged(sheetView->ActiveTabText(), table ? table->rowCount() : 0);
}
