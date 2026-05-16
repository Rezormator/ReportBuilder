#pragma once

#include <QFrame>
#include <QPushButton>
#include <QProgressBar>

class ActionBar : public QFrame {
    Q_OBJECT

public:
    explicit ActionBar(QWidget *parent = nullptr);

    void SetBusy(bool busy) const;

signals:
    void GenerateReportRequested();
    void ClearReportRequested();
    void PrintRequested();
    void ReloadRequested();
    void ExitRequested();

private:
    QPushButton *m_buttonGenerate = nullptr;
    QPushButton *m_buttonClear = nullptr;
    QPushButton *m_buttonPrint = nullptr;
    QPushButton *m_buttonReload = nullptr;
    QPushButton *m_buttonExit = nullptr;
    QProgressBar *m_progressBar = nullptr;
};
