#include "MainWindow.h"

#include "../../Application/Config/StoreConfig.h"
#include "../../Application/Pipeline/ReportPipeline.h"
#include "../../Application/XlsxLoader/XlsxLoader.h"
#include "../../Application/PrintService/PrintService.h"
#include "../../Infrastructure/AppConfiguration.h"
#include "../../Infrastructure/AppSettings.h"

#include <QApplication>
#include <QMenuBar>
#include <QAction>
#include <QVBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include <QStyle>
#include <QScreen>
#include <QTimer>
#include <QFileInfo>
#include <QDir>

#include "../../Infrastructure/XlsxWriter/XlsxWriter.h"
#include "../Theme/Theme.h"

static QString ResolvePath(const std::string &relativePath) {
    const QFileInfo fileInfo(QString::fromStdString(relativePath));
    if (fileInfo.exists()) return fileInfo.absoluteFilePath();
    QDir executableDirectory(QApplication::applicationDirPath());
    executableDirectory.cdUp();
    executableDirectory.cdUp();
    QFileInfo resolvedFileInfo(executableDirectory.absoluteFilePath(fileInfo.fileName()));
    if (resolvedFileInfo.exists()) return resolvedFileInfo.absoluteFilePath();
    return QDir::current().absoluteFilePath(QString::fromStdString(relativePath));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("ReportBuilder");
    resize(1400, 800);

    if (const auto *screen = QApplication::primaryScreen()) {
        const auto availableGeometry = screen->availableGeometry();
        move(availableGeometry.center() - rect().center());
    }

    const AppConfiguration appConfiguration;
    m_textilePath  = ResolvePath(appConfiguration.textilesPath);
    m_footwearPath = ResolvePath(appConfiguration.footwearPath);

    m_fileWatcher = new QFileSystemWatcher(this);
    connect(m_fileWatcher, &QFileSystemWatcher::fileChanged, this, &MainWindow::OnXlsxFileChanged);

    SetupUI();
    SetupMenuBar();
    SetupStatusBar();

    QTimer::singleShot(0, this, &MainWindow::RefreshAll);
}

void MainWindow::SetupUI() {
    menuBar()->setVisible(false);

    auto *centralWidget = new QWidget(this);
    centralWidget->setStyleSheet(QString("background: %1;").arg(Theme::BG_DARK));
    setCentralWidget(centralWidget);

    auto *rootLayout = new QVBoxLayout(centralWidget);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);

    m_actionBar = new ActionBar(centralWidget);
    connect(m_actionBar, &ActionBar::GenerateReportRequested, this, &MainWindow::OnGenerateReport);
    connect(m_actionBar, &ActionBar::ClearReportRequested,    this, &MainWindow::OnClearReport);
    connect(m_actionBar, &ActionBar::PrintRequested,          this, &MainWindow::OnPrint);
    connect(m_actionBar, &ActionBar::ReloadRequested,         this, &MainWindow::OnReload);
    connect(m_actionBar, &ActionBar::ExitRequested,           this, &QWidget::close);
    rootLayout->addWidget(m_actionBar);

    m_categoryTabs = new CategoryTabs(centralWidget);
    connect(m_categoryTabs, &CategoryTabs::SheetChanged, this, &MainWindow::OnSheetChanged);
    rootLayout->addWidget(m_categoryTabs, 1);
}

void MainWindow::SetupMenuBar() {
    auto *fileMenu = menuBar()->addMenu("Файл");

    auto *reloadAction = fileMenu->addAction(
        QApplication::style()->standardIcon(QStyle::SP_BrowserReload), "Оновити файли");
    reloadAction->setShortcut(QKeySequence(Qt::Key_F5));
    reloadAction->setShortcutContext(Qt::WindowShortcut);
    this->addAction(reloadAction);
    connect(reloadAction, &QAction::triggered, this, &MainWindow::OnReload);

    fileMenu->addSeparator();
    auto *exitAction = fileMenu->addAction("Вихід");
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    auto *reportsMenu = menuBar()->addMenu("Звіти");

    auto *generateReportAction = reportsMenu->addAction("Сформувати звіти");
    generateReportAction->setShortcut(QKeySequence("Ctrl+R"));
    generateReportAction->setShortcutContext(Qt::WindowShortcut);
    this->addAction(generateReportAction);
    connect(generateReportAction, &QAction::triggered, this, &MainWindow::OnGenerateReport);

    auto *clearReportAction = reportsMenu->addAction("Очистити звіти");
    clearReportAction->setShortcut(QKeySequence("Ctrl+D"));
    clearReportAction->setShortcutContext(Qt::WindowShortcut);
    this->addAction(clearReportAction);
    connect(clearReportAction, &QAction::triggered, this, &MainWindow::OnClearReport);

    auto *printMenu = menuBar()->addMenu("Друк");
    auto *printAction = printMenu->addAction("Друкувати поточний аркуш");
    printAction->setShortcut(QKeySequence("Ctrl+P"));
    printAction->setShortcutContext(Qt::WindowShortcut);
    this->addAction(printAction);
    connect(printAction, &QAction::triggered, this, &MainWindow::OnPrint);
}

void MainWindow::SetupStatusBar() {
    m_statusBar = new AppStatusBar(this);
    setStatusBar(m_statusBar);
}

void MainWindow::RefreshAll() {
    SetBusy(true);
    m_statusBar->SetMessage("Завантаження файлів...");

    if (!m_fileWatcher->files().isEmpty()) {
        m_fileWatcher->removePaths(m_fileWatcher->files());
    }

    RefreshCategory(0);
    RefreshCategory(1);

    if (QFileInfo::exists(m_textilePath))  m_fileWatcher->addPath(m_textilePath);
    if (QFileInfo::exists(m_footwearPath)) m_fileWatcher->addPath(m_footwearPath);

    SetBusy(false);
    m_statusBar->SetMessage("Готово");
}

void MainWindow::RefreshCategory(const int tabIndex) const {
    const QString  &path      = (tabIndex == 0) ? m_textilePath : m_footwearPath;
    SheetView      *sheetView = (tabIndex == 0) ? m_categoryTabs->TextileView() : m_categoryTabs->FootwearView();
    sheetView->Load(XlsxLoader::Load(path));
}

void MainWindow::OnGenerateReport() {
    const auto allSettings = m_actionBar->GetActiveSettings();

    if (allSettings.empty()) {
        QMessageBox::information(this, "Увага", "Немає активних блоків налаштувань.");
        return;
    }

    SetBusy(true);
    m_statusBar->SetMessage("Формування звітів...");
    qApp->processEvents();

    try {
        ReportPipeline::RunAll(allSettings);

        m_statusBar->SetMessage("Звіти успішно сформовано.");
        RefreshCategory(0);
        RefreshCategory(1);
        SetBusy(false);

        QMessageBox::information(this, "Готово", "Звіти сформовано.");
        return;
    } catch (const std::exception &exception) {
        QMessageBox::critical(this, "Помилка",
            QString("Не вдалося сформувати звіти:\n%1").arg(QString::fromStdString(exception.what())));
        m_statusBar->SetMessage("Помилка формування звіту.", true);
    }

    RefreshCategory(0);
    RefreshCategory(1);
    SetBusy(false);
}

void MainWindow::OnClearReport() {
    const int tabIndex = m_categoryTabs->currentIndex();
    const QString category = (tabIndex == 0) ? "текстилю" : "взуття";

    const auto answer = QMessageBox::question(
        this, "Очистити звіти",
        QString("Видалити всі звітні аркуші для %1?").arg(category),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if (answer != QMessageBox::Yes) return;

    SetBusy(true);
    m_statusBar->SetMessage(QString("Очищення звітів по %1...").arg(category));
    qApp->processEvents();

    const AppConfiguration appCfg;
    const std::string &filePath = (tabIndex == 0) ? appCfg.textilesPath : appCfg.footwearPath;

    try {
        for (const auto &sheetName : ReportPipeline::ALL_REPORT_SHEETS) {
            try { XlsxWriter::DeleteSheet(filePath, sheetName); } catch (...) {}
        }

        m_statusBar->SetMessage(QString("Звіти по %1 очищено.").arg(category));
        RefreshCategory(tabIndex);
        SetBusy(false);
        QMessageBox::information(this, "Готово",
            QString("Звітні аркуші по %1 видалено.").arg(category));
        return;
    } catch (const std::exception &exception) {
        QMessageBox::critical(this, "Помилка",
            QString("Не вдалося очистити звіти:\n%1").arg(QString::fromStdString(exception.what())));
        m_statusBar->SetMessage("Помилка очищення.", true);
    }

    RefreshCategory(tabIndex);
    SetBusy(false);
}

void MainWindow::OnPrint() {
    SheetView    *sheetView = m_categoryTabs->ActiveSheetView();
    QTableWidget *table     = sheetView ? sheetView->ActiveTable() : nullptr;

    if (!table || table->rowCount() == 0) {
        QMessageBox::information(this, "Друк", "Немає даних для друку на поточному аркуші.");
        return;
    }

    PrintService::Print(table, sheetView->ActiveTabText(), this);
}

void MainWindow::OnReload() { RefreshAll(); }

void MainWindow::OnXlsxFileChanged(const QString &path) {
    QTimer::singleShot(500, this, [this, path]() {
        const int tabIndex = (path == m_textilePath) ? 0 : 1;
        RefreshCategory(tabIndex);
        if (!m_fileWatcher->files().contains(path) && QFileInfo::exists(path)) {
            m_fileWatcher->addPath(path);
        }
        m_statusBar->SetMessage(QString("Файл оновлено: %1").arg(QFileInfo(path).fileName()));
    });
}

void MainWindow::OnSheetChanged(const QString &sheetName, const int rowCount) {
    m_statusBar->SetMessage(QString("Аркуш: %1  |  Рядків: %2").arg(sheetName, QString::number(rowCount)));
}

void MainWindow::SetBusy(const bool busy) {
    m_actionBar->SetBusy(busy);
    qApp->processEvents();
}
