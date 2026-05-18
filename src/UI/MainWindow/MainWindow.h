#pragma once

#include <QMainWindow>
#include <QFileSystemWatcher>
#include <QString>

#include "../Widgets/ActionBar/ActionBar.h"
#include "../Widgets/CategoryTabs/CategoryTabs.h"
#include "../Widgets/StatusBar/StatusBar.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

private slots:
    void OnGenerateReport();
    void OnClearReport();
    void OnPrint();
    void OnReload();
    void OnXlsxFileChanged(const QString &path);
    void OnSheetChanged(const QString &sheetName, int rowCount);

private:
    void SetupUI();
    void SetupMenuBar();
    void SetupStatusBar();
    void RefreshAll();
    void RefreshCategory(int tabIndex) const;
    void SetBusy(bool busy);

    QString m_textilePath;
    QString m_footwearPath;

    ActionBar    *m_actionBar    = nullptr;
    CategoryTabs *m_categoryTabs = nullptr;
    AppStatusBar *m_statusBar    = nullptr;
    QFileSystemWatcher *m_fileWatcher = nullptr;
};
