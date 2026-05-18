#pragma once

#include <QFrame>
#include <QPushButton>
#include <QProgressBar>
#include <vector>

#include "../../../Infrastructure/AppSettings.h"
#include "../PresetButton/PresetButton.h"

class ActionBar : public QFrame {
    Q_OBJECT

public:
    explicit ActionBar(QWidget *parent = nullptr);

    void SetBusy(bool busy) const;

    [[nodiscard]] std::vector<StoreSettings> GetActiveSettings() const;

signals:
    void GenerateReportRequested();
    void ClearReportRequested();
    void PrintRequested();
    void ReloadRequested();
    void ExitRequested();

private:
    PresetButton *m_presetButton   = nullptr;
    QPushButton  *m_buttonGenerate = nullptr;
    QPushButton  *m_buttonClear    = nullptr;
    QPushButton  *m_buttonPrint    = nullptr;
    QPushButton  *m_buttonReload   = nullptr;
    QPushButton  *m_buttonExit     = nullptr;
    QProgressBar *m_progressBar    = nullptr;
};
