#include "Theme.h"

namespace Theme {
    QString ActionButtonStyle() {
        return
                "QPushButton {"
                "  background: #3A3A3A; color: #CCCCCC;"
                "  border: 1px solid #505050; border-radius: 2px;"
                "  padding: 5px 16px; font-size: 12px; font-weight: bold;"
                "}"
                "QPushButton:hover  { background: #4A4A4A; color: #EEEEEE; border-color: #666666; }"
                "QPushButton:pressed { background: #252525; color: #BBBBBB; }"
                "QPushButton:disabled { background: #2A2A2A; color: #505050; border-color: #333333; }";
    }

    QString MainTabStyle() {
        return
                "QTabWidget::pane { border: none; background: transparent; }"
                "QTabBar { background: #2B2B2B; }"
                "QTabBar::tab {"
                "  background: #222222; color: #888888;"
                "  min-width: 160px; padding: 10px 28px;"
                "  font-size: 13px; font-weight: bold;"
                "  border: none; border-right: 1px solid #1A1A1A;"
                "}"
                "QTabBar::tab:selected {"
                "  background: #3A3A3A; color: #EEEEEE;"
                "  border-bottom: 2px solid #777777;"
                "}"
                "QTabBar::tab:hover:!selected { background: #2F2F2F; color: #BBBBBB; }";
    }

    QString SheetTabStyle() {
        return
                "QTabWidget::pane { border: none; background: #FFFFFF; }"
                "QTabBar { background: #2B2B2B; }"
                "QTabBar::tab {"
                "  background: #333333; color: #AAAAAA;"
                "  padding: 6px 18px; font-size: 11px;"
                "  border: none; border-right: 1px solid #222222;"
                "  margin-right: 1px;"
                "}"
                "QTabBar::tab:selected {"
                "  background: #484848; color: #EEEEEE; font-weight: bold;"
                "}"
                "QTabBar::tab:hover:!selected { background: #3D3D3D; color: #CCCCCC; }";
    }

    QString TableStyle() {
        return
                "QTableWidget {"
                "  font-size: 12px; color: #111;"
                "  gridline-color: #E8E8E8;"
                "  background: #FFFFFF;"
                "  alternate-background-color: #F5F5F5;"
                "  border: none;"
                "}"
                "QHeaderView::section {"
                "  background: #EFEFEF; color: #111; font-weight: bold;"
                "  padding: 4px 6px; border: none;"
                "  border-right: 1px solid #DEDEDE;"
                "  border-bottom: 1px solid #DEDEDE;"
                "}"
                "QHeaderView[orientation='2']::section {"
                "  background: #3A3A3A; color: #CCCCCC;"
                "  font-size: 10px; font-weight: normal;"
                "  border: none; border-bottom: 1px solid #2A2A2A;"
                "  border-right: 1px solid #2A2A2A;"
                "  padding: 0 4px;"
                "}"
                "QTableWidget::item { color: #111; border: none; }"
                "QTableWidget::item:selected { background: #D6E4F0; color: #111; }";
    }

    QString StatusBarStyle() {
        return
                "QStatusBar { background: #222222; color: #AAAAAA; font-size: 11px;"
                "  border-top: 1px solid #111111; }"
                "QStatusBar QLabel { color: #AAAAAA; }";
    }

    QString ProgressBarStyle() {
        return
                "QProgressBar { background: #1A1A1A; border: 1px solid #555; border-radius: 3px; }"
                "QProgressBar::chunk { background: #888888; }";
    }

    QString StoreTypeDialogStyle() {
        return
                "QPushButton {"
                "  background-color: #1976D2; color: white;"
                "  border-radius: 4px; font-weight: bold; font-size: 13px;"
                "  padding: 4px 16px; }"
                "QPushButton:hover { background-color: #1565C0; }"
                "QPushButton:pressed { background-color: #0D47A1; }";
    }

    QString VerticalHeaderStyle() {
        return
                "QHeaderView::section {"
                "  background: #3A3A3A; color: #CCCCCC;"
                "  font-size: 10px; font-weight: normal;"
                "  border: none;"
                "  border-bottom: 1px solid #2A2A2A;"
                "  border-right: 1px solid #2A2A2A;"
                "  padding: 0 4px; }";
    }
    QString HorizontalHeaderStyle() {
        return
                "QHeaderView::section {"
                "  background: #EFEFEF; color: #111; font-weight: bold;"
                "  padding: 4px 6px; border: none;"
                "  border-right: 1px solid #DEDEDE;"
                "  border-bottom: 1px solid #DEDEDE; }";
    }
}
