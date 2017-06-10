
#include "notes.h"
#include "mainwindow.h"
#include "plurinotes_app.h"

/*int main(int argc, char* argv[]) {

        QApplication app(argc, argv);
        MainWindow& mw = MainWindow::getInstance();
        mw.showNotesManager();
        mw.show();

        return app.exec();

}*/

int main(int argc, char* argv[]) {

    PluriNotes& app = PluriNotes::donnePluriNotesInstance(argc,argv);

    return app.exec();
}
