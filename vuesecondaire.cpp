#include "plurinotes_app.h"
#include "vuesecondaire.h"
#include "couples.h"

VueSecondaire::VueSecondaire(): QMainWindow(),listeCouples(nullptr),dockListeCouples(new QDockWidget("Couples", this))
      /*listeNotesLeft(nullptr),
      listeNotesRight(nullptr)*/
{
    CouplesEditeur();
createCouplesDock();
remplirCouplesDock();
    //noteCourante(notesManager.getNoteTitle("Avant Propos"));
}

void VueSecondaire::CouplesEditeur()
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
        addCouple = new QPushButton("Ajouter un couple");
        addNotOrientedCouple = new QPushButton("Ajouter un couple (NO)");
        ///Connexion des boutons aux slots
        QObject::connect(addCouple, SIGNAL(clicked()), this, SLOT(addOrientedCouple()));
        QObject::connect(addNotOrientedCouple, SIGNAL(clicked()), this, SLOT(addCoupleNotOriented()));
        /*QObject::connect(add, SIGNAL(clicked()), this, SLOT(updateRelationManager()));

        QObject::connect(addNotOriented, SIGNAL(clicked()), this, SLOT(updateRelationManager()));
        */
        ///Ajout des boutons
       layout->addWidget(listeNotesLeft, 0, 0);

        layout->addWidget(listeNotesRight, 0, 2);

        layout->addWidget(addCouple, 1, 1);

        layout->addWidget(addNotOrientedCouple, 2, 1);



        centralContainer->setLayout(layout);

        this->setCentralWidget(centralContainer);
}

void VueSecondaire::createCouplesDock()

{
    // Dock de Notes
    dockListeCouples->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    listeCouples = new QListWidget(dockListeCouples); // listeRelations est le fils de dockListeRelations
    dockListeCouples->setWidget(listeCouples);
    this->addDockWidget(Qt::RightDockWidgetArea, dockListeCouples);
}
///Fonction qui remplit le dock de couples
void VueSecondaire::remplirCouplesDock(){
   QListWidgetItem* item;
   QString temp;
   ///On utilise l'iterator de CouplesManager pour afficher les couples existants
   for(CouplesManager::Iterator it=couplesManager.getIterator(); !it.isDone(); it.next()){
            ///On utilise un QString temporaire pour afficher les deux notes référencées
            temp = (it.current()).getReferencingNote().getId() + " -> " + (it.current()).getReferencedNote().getId();
            ///On affiche le couple dans le dock
            item= new QListWidgetItem(temp,listeCouples);
    }
}
///Fonction pour actualiser le dock de couples
void VueSecondaire::updateDockCouples(){
    createCouplesDock();
    remplirCouplesDock();
}

///Fonction qui permet de choisir le fichier XML contenant les couples
void VueSecondaire::choixFichier(){
    QString filename = QFileDialog::getOpenFileName();
    couplesManager.setFilename(filename);
    couplesManager.load();
    remplirCouplesDock();

}
///Slot permettant d'ajouter un couple orienté
void VueSecondaire::addOrientedCouple(){
    ///On récupère la note n1 dans le QlistWidget listeNotesLeft
    QListWidgetItem* selectedItem1 = listeNotesLeft->currentItem();
    QString title1 = selectedItem1->text();
    Note* n1 = NotesManager::getManager().getNoteByTitle(title1);
    ///On récupère la note n2 dans le QlistWidget listeNotesRight
    QListWidgetItem* selectedItem2 = listeNotesRight->currentItem();
    QString title2 = selectedItem2->text();
    Note* n2 = NotesManager::getManager().getNoteByTitle(title2);
    ///Insertion du couple dans CouplesManager
    CouplesManager& cm = CouplesManager::getManager();
    cm.addCouple(*(n1),*(n2));
    updateDockCouples();
    ///MessageBox attestant du succès de l'ajout de la relation
    QMessageBox::information(this, "Succès", "Le couple a bien été ajouté");

}

///Slot permettant d'ajouter un couple non orienté
void VueSecondaire::addCoupleNotOriented(){
    ///On récupère la note n1 dans le QlistWidget listNotesLeft
    QListWidgetItem* selectedItem1 = listeNotesLeft->currentItem();
    QString title1 = selectedItem1->text();
    Note* n1 = NotesManager::getManager().getNoteByTitle(title1);
    ///On récupère la note n2 dans le QlistWidget listNotesRight
    QListWidgetItem* selectedItem2 = listeNotesRight->currentItem();
    QString title2 = selectedItem2->text();
    Note* n2 = NotesManager::getManager().getNoteByTitle(title2);
    CouplesManager& cm = CouplesManager::getManager();
    ///Ajout d'un couple de n1 vers n2 dans le CouplesManager
    cm.addCouple(*(n1),*(n2));
    ///Ajout d'un couple de n1 vers n2 dans le CouplesManager
    cm.addCouple(*(n2),*(n1));
    updateDockCouples();
    ///MessageBox attestant du succès de l'ajout de la relation non orientée
    QMessageBox::information(this, "Succès", "Le couple non orienté a bien été ajouté");
}


