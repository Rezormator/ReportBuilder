#include "ActionBar.h"
#include "../../Theme/Theme.h"
#include <QHBoxLayout>

ActionBar::ActionBar(QWidget *parent) : QFrame(parent) {
    setFixedHeight(50);
    setStyleSheet(QString("QFrame { background: %1; border-bottom: 1px solid %2; }").arg(Theme::BG_DARK).arg(Theme::BG_DARKEST));

    auto *leftLayout = new QHBoxLayout();
    leftLayout->setContentsMargins(0, 0, 0, 0);
    leftLayout->setSpacing(8);

    const QString buttonStyle = Theme::ActionButtonStyle();

    m_buttonGenerate = new QPushButton("Сформувати звіти", this);
    m_buttonGenerate->setMinimumHeight(32);
    m_buttonGenerate->setStyleSheet(buttonStyle);
    connect(m_buttonGenerate, &QPushButton::clicked, this, &ActionBar::GenerateReportRequested);
    leftLayout->addWidget(m_buttonGenerate);

    m_buttonClear = new QPushButton("Очистити звіти", this);
    m_buttonClear->setMinimumHeight(32);
    m_buttonClear->setStyleSheet(buttonStyle);
    connect(m_buttonClear, &QPushButton::clicked, this, &ActionBar::ClearReportRequested);
    leftLayout->addWidget(m_buttonClear);

    m_buttonPrint = new QPushButton("Друкувати", this);
    m_buttonPrint->setMinimumHeight(32);
    m_buttonPrint->setStyleSheet(buttonStyle);
    connect(m_buttonPrint, &QPushButton::clicked, this, &ActionBar::PrintRequested);
    leftLayout->addWidget(m_buttonPrint);

    m_buttonReload = new QPushButton("Оновити", this);
    m_buttonReload->setMinimumHeight(32);
    m_buttonReload->setStyleSheet(buttonStyle);
    connect(m_buttonReload, &QPushButton::clicked, this, &ActionBar::ReloadRequested);
    leftLayout->addWidget(m_buttonReload);

    m_progressBar = new QProgressBar(this);
    m_progressBar->setRange(0, 0);
    m_progressBar->setFixedSize(160, 18);
    m_progressBar->setVisible(false);
    m_progressBar->setStyleSheet(Theme::ProgressBarStyle());

    m_buttonExit = new QPushButton("Вихід", this);
    m_buttonExit->setMinimumHeight(32);
    m_buttonExit->setStyleSheet(buttonStyle);
    connect(m_buttonExit, &QPushButton::clicked, this, &ActionBar::ExitRequested);

    auto *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(14, 7, 14, 7);
    mainLayout->setSpacing(8);

    mainLayout->addLayout(leftLayout);
    mainLayout->addStretch(1);
    mainLayout->addWidget(m_progressBar);
    mainLayout->addWidget(m_buttonExit);
}

void ActionBar::SetBusy(const bool busy) const {
    m_progressBar->setVisible(busy);
    m_buttonGenerate->setEnabled(!busy);
    m_buttonClear->setEnabled(!busy);
    m_buttonPrint->setEnabled(!busy);
    m_buttonReload->setEnabled(!busy);
}
