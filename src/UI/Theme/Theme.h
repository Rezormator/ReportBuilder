#pragma once

#include <QString>

namespace Theme {
    constexpr auto BG_DARK    = "#2B2B2B";
    constexpr auto BG_DARKER  = "#222222";
    constexpr auto BG_DARKEST = "#1A1A1A";
    constexpr auto BG_MID     = "#3A3A3A";
    constexpr auto BG_LIGHT   = "#EFEFEF";
    constexpr auto BG_WHITE   = "#FFFFFF";
    constexpr auto BG_ALT_ROW = "#F5F5F5";

    constexpr auto TEXT_BRIGHT = "#EEEEEE";
    constexpr auto TEXT_NORMAL = "#CCCCCC";
    constexpr auto TEXT_DIM    = "#AAAAAA";
    constexpr auto TEXT_DARK   = "#111111";
    constexpr auto TEXT_ERROR  = "#C62828";

    constexpr auto BORDER_DARK  = "#1A1A1A";
    constexpr auto BORDER_MID   = "#505050";
    constexpr auto BORDER_LIGHT = "#DEDEDE";
    constexpr auto GRID_LINE    = "#E8E8E8";

    constexpr auto SELECTION_BACKGROUND = "#D6E4F0";

    QString ActionButtonStyle();
    QString MainTabStyle();
    QString SheetTabStyle();
    QString TableStyle();
    QString StatusBarStyle();
    QString ProgressBarStyle();
    QString StoreTypeDialogStyle();
    QString VerticalHeaderStyle();
    QString HorizontalHeaderStyle();

    QString PresetMainButtonStyle();
    QString PresetArrowButtonStyle();
    QString PresetPopupFrameStyle();
    QString PresetPopupRowStyle(bool isActive);
    QString PresetPopupNameButtonStyle(bool isActive);
    QString PresetPopupDotsButtonStyle();
    QString PresetPopupAddButtonStyle();
    QString PresetPopupSeparatorStyle();

    QString SettingsDialogCardStyle();
    QString SettingsDialogNameLabelStyle();
    QString SettingsDialogNameEditStyle(bool editable);
    QString SettingsDialogScrollAreaStyle();
    QString SettingsDialogSectionLabelStyle();
    QString SettingsDialogSpinBoxStyle(bool editable);
    QString SettingsDialogCheckIndicatorStyle(bool checked);
    QString SettingsDialogCheckLabelButtonStyle();
    QString SettingsDialogCheckLabelReadOnlyStyle();
    QString SettingsDialogActionButtonStyle();
    QString SettingsDialogSaveButtonStyle();
}
