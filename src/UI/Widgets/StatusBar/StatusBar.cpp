#include "StatusBar.h"
#include "../../Theme/Theme.h"

AppStatusBar::AppStatusBar(QWidget *parent) : QStatusBar(parent) {
    setStyleSheet(Theme::StatusBarStyle());
    m_label = new QLabel("Готово", this);
    addWidget(m_label, 1);
}

void AppStatusBar::SetMessage(const QString &message, const bool isError) const {
    m_label->setText(message);
    m_label->setStyleSheet(isError
        ? QString("color: %1;").arg(Theme::TEXT_ERROR)
        : QString());
}
