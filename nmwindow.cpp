#include "nmwindow.h"
//#include "notemanager.h"
#include "QBoxLayout"
#include "QPushButton"
#include "notes.h"
//#include "noteediteur.h"
#include "mainwindow.h"
#include "QObject"


NotesManagerWindow::NotesManagerWindow(QString title, QWidget* parent) : QDockWidget(title, parent){
    listNotes = new QListWidget();
    QListWidgetItem* item;
    NotesManager& m = NotesManager::getManager();
    for(NotesManager::Iterator it=m.getIterator(); !it.isDone(); it.next()){
        item= new QListWidgetItem((it.current()).getTitle(),listNotes);
    }
    QWidget* multiWidget = new QWidget();
    QPushButton* afficherNote = new QPushButton("Afficher");
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(listNotes);
    layout->addWidget(afficherNote);
    multiWidget->setLayout(layout);
    this->setWidget(multiWidget);

    //Connexions au slots
    QObject::connect(afficherNote,SIGNAL(clicked()),this,SLOT(afficherNote()));
}

/*void NotesManagerWindow::afficherNote(){
    if(!listNotes->currentItem() == 0){
        QListWidgetItem* selectedItem = listNotes->currentItem();
        QString title = selectedItem->text();
        Note* n = NotesManager::getManager().getNoteTitle(title);
        NoteEditeur* ne = NotesManager::getManager().callEditeur(n,n->getClassName());
        MainWindow::getInstance().setEditeur(ne);
        ne = MainWindow::getInstance().getEditeur();
        MainWindow::getInstance().showEditeur(ne);
    }
    else {throw NotesException("Couldn't show the note..");}
}*/
