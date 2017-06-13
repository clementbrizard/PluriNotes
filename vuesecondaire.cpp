#include "plurinotes_app.h"
#include "vuesecondaire.h"
#include "relations.h"

VueSecondaire::VueSecondaire(): QMainWindow(),listeRelations(nullptr),dockListeRelations(new QDockWidget("Relations", this))
      /*listeNotesLeft(nullptr),
      listeNotesRight(nullptr)*/
{
    RelationEditeur();
createRelationDock();
    //noteCourante(notesManager.getNoteTitle("Avant Propos"));
}

void VueSecondaire::RelationEditeur()
{
        QWidget* centralContainer = new QWidget;
        QGridLayout *layout = new QGridLayout;
        ///Premier QlistWidget : listNotesLeft
        listeNotesLeft = new QListWidget();
        QListWidgetItem* item1;
        ///Remplissage de listeNotesLeft
        for(NotesManager::Iterator it=notesManager.getIterator(); !it.isDone(); it.next()){
            item1= new QListWidgetItem((it.current()).getTitle(),listeNotesLeft);
        }
        ///Second QlistWidget : listeNotesRight
        listeNotesRight = new QListWidget();
        QListWidgetItem* item2;
        ///Remplissage de listNotesRight
        for(NotesManager::Iterator it=notesManager.getIterator(); !it.isDone(); it.next()){
            item2= new QListWidgetItem((it.current()).getTitle(),listeNotesRight);
        }
        layer = new QVBoxLayout();
        scroller = new QScrollArea();
        ///Ajouts des boutons
        add = new QPushButton("Ajouter une relation");
        addNotOriented = new QPushButton("Ajouter une relation (NO)");
        quit = new QPushButton("Quitter");
        ///Connexion des boutons aux slots
        /*QObject::connect(add, SIGNAL(clicked()), this, SLOT(addRelation()));
        QObject::connect(add, SIGNAL(clicked()), this, SLOT(updateRelationManager()));
        QObject::connect(addNotOriented, SIGNAL(clicked()), this, SLOT(addRelationNotOriented()));
        QObject::connect(addNotOriented, SIGNAL(clicked()), this, SLOT(updateRelationManager()));
        QObject::connect(quit, SIGNAL(clicked()), this, SLOT(close()));*/
        ///Ajout des boutons
       layout->addWidget(listeNotesLeft, 0, 0);

        layout->addWidget(listeNotesRight, 0, 2);

        layout->addWidget(add, 1, 1);

        layout->addWidget(addNotOriented, 2, 1);

        layout->addWidget(quit, 3, 1);

        centralContainer->setLayout(layout);

        this->setCentralWidget(centralContainer);
}

void VueSecondaire::createRelationDock()
{
    // Dock de Notes
    dockListeRelations->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    listeRelations = new QListWidget(dockListeRelations); // listeRelations est le fils de dockListeRelations
    dockListeRelations->setWidget(listeRelations);
    this->addDockWidget(Qt::RightDockWidgetArea, dockListeRelations);
}

void VueSecondaire::choixFichier(){
    QString filename = QFileDialog::getOpenFileName();
    relationsManager.setFilename(filename);
    relationsManager.load();
}


