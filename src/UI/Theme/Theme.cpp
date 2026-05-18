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

QString PresetMainButtonStyle() {
    return QString(
        "QPushButton {"
        "  background: %1; color: %2;"
        "  border: 1px solid %3; border-right: none;"
        "  border-radius: 2px; border-top-right-radius: 0; border-bottom-right-radius: 0;"
        "  padding: 5px 12px; font-size: 12px; font-weight: bold;"
        "}"
        "QPushButton:hover { background: #4A4A4A; color: %4; border-color: #666666; }"
        "QPushButton:pressed { background: #252525; }"
    ).arg(BG_MID, TEXT_NORMAL, BORDER_MID, TEXT_BRIGHT);
}

QString PresetArrowButtonStyle() {
    return QString(
        "QPushButton {"
        "  background: %1; color: %2;"
        "  border: 1px solid %3;"
        "  border-radius: 2px; border-top-left-radius: 0; border-bottom-left-radius: 0;"
        "  font-size: 11px; padding: 0;"
        "}"
        "QPushButton:hover { background: #4A4A4A; color: %4; border-color: #666666; }"
        "QPushButton:pressed { background: #252525; }"
    ).arg(BG_MID, TEXT_NORMAL, BORDER_MID, TEXT_BRIGHT);
}

QString PresetPopupFrameStyle() {
    return QString(
        "QFrame {"
        "  background: %1;"
        "  border: 1px solid %2;"
        "  border-radius: 5px;"
        "}"
    ).arg(BG_DARK, BORDER_MID);
}

QString PresetPopupRowStyle(bool isActive) {
    return QString(
        "QFrame { background: %1; border-radius: 3px; border: none; }"
    ).arg(isActive ? BG_MID : "transparent");
}

QString PresetPopupNameButtonStyle(bool isActive) {
    return QString(
        "QPushButton {"
        "  background: transparent; color: %1; border: none;"
        "  text-align: left; font-size: 12px; %2"
        "  padding: 4px 4px;"
        "}"
        "QPushButton:hover { color: %3; }"
    ).arg(
        isActive ? TEXT_BRIGHT : TEXT_NORMAL,
        isActive ? "font-weight: bold;" : "",
        TEXT_BRIGHT
    );
}

QString PresetPopupDotsButtonStyle() {
    return QString(
        "QPushButton {"
        "  background: transparent; color: %1; border: none;"
        "  font-size: 10px; letter-spacing: 1px;"
        "}"
        "QPushButton:hover { background: %2; color: %3; border-radius: 3px; }"
    ).arg(TEXT_DIM, BG_MID, TEXT_BRIGHT);
}

QString PresetPopupAddButtonStyle() {
    return QString(
        "QPushButton {"
        "  background: transparent; color: %1; border: none;"
        "  text-align: left; font-size: 11px; padding: 6px 10px;"
        "  border-radius: 3px;"
        "}"
        "QPushButton:hover { background: %2; color: %3; }"
    ).arg(TEXT_DIM, BG_MID, TEXT_BRIGHT);
}

QString PresetPopupSeparatorStyle() {
    return QString(
        "color: %1; border: none; background: %1; max-height: 1px;"
    ).arg(BORDER_DARK);
}

QString SettingsDialogCardStyle() {
    return QString(
        "QFrame#card {"
        "  background: %1;"
        "  border: 1px solid %2;"
        "  border-radius: 6px;"
        "}"
    ).arg(BG_DARK, BORDER_MID);
}

QString SettingsDialogNameLabelStyle() {
    return QString(
        "color: %1; font-size: 11px; background: transparent;"
    ).arg(TEXT_DIM);
}

QString SettingsDialogNameEditStyle(bool editable) {
    return QString(
        "QLineEdit {"
        "  background: %1; color: %2; border: 1px solid %3;"
        "  border-radius: 3px; padding: 3px 6px; font-size: 12px; font-weight: bold;"
        "}"
        "QLineEdit:read-only { background: %4; color: %5; border-color: %6; }"
    ).arg(
        editable ? BG_MID : BG_DARK,
        TEXT_BRIGHT,
        editable ? BORDER_MID : BORDER_DARK,
        BG_DARK, TEXT_BRIGHT, BORDER_DARK
    );
}

QString SettingsDialogScrollAreaStyle() {
    return "QScrollArea { background: transparent; border: none; }";
}

QString SettingsDialogSectionLabelStyle() {
    return QString(
        "color: %1; font-size: 10px; font-weight: bold;"
        " text-transform: uppercase; margin-top: 4px; background: transparent;"
    ).arg(TEXT_DIM);
}

QString SettingsDialogSpinBoxStyle(bool editable) {
    return QString(
        "QSpinBox {"
        "  background: %1; color: %2; border: 1px solid %3;"
        "  border-radius: 2px; padding: 2px 4px; font-size: 11px;"
        "}"
    ).arg(
        editable ? BG_MID : BG_DARK,
        TEXT_NORMAL,
        editable ? BORDER_MID : BORDER_DARK
    );
}

QString SettingsDialogCheckIndicatorStyle(bool checked) {
    return QString(
        "QPushButton {"
        "  background: transparent;"
        "  border: 1px solid %1;"
        "  border-radius: 2px;"
        "  font-size: 7px;"
        "  color: #DDDDDD;"
        "  padding: 0px;"
        "  text-align: center;"
        "}"
        "QPushButton:hover:enabled { border-color: #AAAAAA; }"
        "QPushButton:disabled { border-color: #3A3A3A; color: #444444; }"
    ).arg(checked ? "#888888" : "#555555");
}

QString SettingsDialogCheckLabelButtonStyle() {
    return QString(
        "QPushButton {"
        "  background: transparent; border: none;"
        "  color: %1; font-size: 11px; text-align: left; padding: 0px;"
        "}"
        "QPushButton:hover { color: %2; }"
    ).arg(TEXT_NORMAL, TEXT_BRIGHT);
}

QString SettingsDialogCheckLabelReadOnlyStyle() {
    return QString(
        "color: %1; font-size: 11px; background: transparent;"
    ).arg(TEXT_DIM);
}

QString SettingsDialogActionButtonStyle() {
    return QString(
        "QPushButton {"
        "  background: %1; color: %2; border: 1px solid %3;"
        "  border-radius: 3px; padding: 5px 14px; font-size: 11px;"
        "}"
        "QPushButton:hover { background: %4; color: %5; }"
    ).arg(BG_MID, TEXT_NORMAL, BORDER_MID, BG_DARK, TEXT_BRIGHT);
}

QString SettingsDialogSaveButtonStyle() {
    return QString(
        "QPushButton {"
        "  background: %1; color: %2; border: 1px solid %3;"
        "  border-radius: 3px; padding: 5px 14px; font-size: 11px; font-weight: bold;"
        "}"
        "QPushButton:hover { background: #4A4A4A; color: %4; }"
        "QPushButton:pressed { background: #252525; }"
    ).arg(BG_MID, TEXT_BRIGHT, BORDER_MID, TEXT_BRIGHT);
}

}

