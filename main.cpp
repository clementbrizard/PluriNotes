#include <QApplication>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include "notes.h"
#include "mainwindow.h"
int main(int argc, char* argv[]) {

        QApplication app(argc, argv);
        MainWindow& mw = MainWindow::getInstance();
        mw.showNotesManager();
        mw.show();

        return app.exec();

}
