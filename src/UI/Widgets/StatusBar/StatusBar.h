#pragma once

#include <QStatusBar>
#include <QLabel>

class AppStatusBar : public QStatusBar {
    Q_OBJECT

public:
    explicit AppStatusBar(QWidget *parent = nullptr);

    void SetMessage(const QString &message, bool isError = false) const;

private:
    QLabel *m_label = nullptr;
};
