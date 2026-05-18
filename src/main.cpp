#include <QApplication>
#include "UI/MainWindow/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setApplicationName("ReportBuilder");

    MainWindow window;
    window.showMaximized();
    return QApplication::exec();
}
