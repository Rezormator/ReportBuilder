#pragma once

#include <QWidget>
#include <QPushButton>
#include <QFrame>
#include <vector>
#include "../../../Infrastructure/AppSettings.h"
#include "../../../Infrastructure/PresetStorage/PresetStorage.h"

class PresetButton : public QWidget {
    Q_OBJECT

public:
    explicit PresetButton(QWidget *parent = nullptr);

    [[nodiscard]] std::vector<StoreSettings> GetActiveSettings() const;

signals:
    void ActivePresetChanged();

private slots:
    void OnArrowClicked();
    void OnAddNewPreset();
    void ClosePopup();

private:
    void ShowPopup();
    void SelectPreset(int index);
    void SavePresets() const;

    QPushButton *m_mainButton  = nullptr;
    QPushButton *m_arrowButton = nullptr;

    std::vector<StoreSettings> m_presets;
    int m_activeIndex = 0;

    QFrame *m_popup = nullptr;
};

