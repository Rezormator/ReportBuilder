#include <QApplication>
#include "UI/MainWindow/MainWindow.h"
#include "UI/Dialogs/StoreTypeDialog/StoreTypeDialog.h"
#include "Application/Pipeline/ReportPipeline.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setApplicationName("ReportBuilder");

    ReportPipeline::ClearSheets();

    StoreTypeDialog dialog;
    if (dialog.exec() != QDialog::Accepted) {
        return 0;
    }

    MainWindow window(dialog.SelectedType());
    window.showMaximized();
    return QApplication::exec();
}


