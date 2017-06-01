#include <QApplication>
#include <QString>
#include <QFileDialog>
#include "plurinotes.h"
#include "articleediteur.h"
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);


    //Accueil* fenetre = new Accueil();
    //ArticleEditeur* fenetre = new ArticleEditeur(a);
    QString filename = QFileDialog::getOpenFileName();

       NotesManager& m = NotesManager::getManager();
       m.setFilename(filename);
       m.load();

       Article& a = m.getIterator().current();
       ArticleEditeur* fenetre = new ArticleEditeur(a);

    fenetre->show();
    return app.exec();

}
