#include "plurinotes_app.h"
#include "vuesecondaire.h"
#include "couples.h"
///Fonction qui genere la page de base des relations
VueSecondaire::VueSecondaire(): QMainWindow(),listeCouples(nullptr),dockListeCouples(new QDockWidget("Couples", this))
      /*listeNotesLeft(nullptr),
      listeNotesRight(nullptr)*/
{
    CouplesEditeur();
createCouplesDock();
remplirCouplesDock();
    //noteCourante(notesManager.getNoteTitle("Avant Propos"));
}

///Affichage de la partie centrale de la page des relations
void VueSecondaire::CouplesEditeur()
{
        QWidget* centralContainer = new QWidget;
        QGridLayout *layout = new QGridLayout;
        ///Premier QlistWidget : listeNotesLeft
        listeNotesLeft = new QListWidget();
        QListWidgetItem* item1;
        ///Remplissage de listeNotesLeft
        for(NotesManager::Iterator it=notesManager.getIterator(); !it.isDone(); it.next()){
            if(it.current().getStatut()=="active")
                item1= new QListWidgetItem((it.current()).getTitle(),listeNotesLeft);
        }
        ///Second QlistWidget : listeNotesRight
        listeNotesRight = new QListWidget();
        QListWidgetItem* item2;
        ///Remplissage de listeNotesRight
        for(NotesManager::Iterator it=notesManager.getIterator(); !it.isDone(); it.next()){
                 if(it.current().getStatut()=="active")
            item2= new QListWidgetItem((it.current()).getTitle(),listeNotesRight);
        }
        layer = new QVBoxLayout();
        scroller = new QScrollArea();
        ///Ajouts des boutons
        addCouple = new QPushButton("Ajouter un couple");
        addNotOrientedCouple = new QPushButton("Ajouter un couple (NO)");
        supprimer= new QPushButton("Supprimer un couple");
        ///Connexion des boutons aux slots
        QObject::connect(addCouple, SIGNAL(clicked()), this, SLOT(addOrientedCouple()));
        QObject::connect(addNotOrientedCouple, SIGNAL(clicked()), this, SLOT(addCoupleNotOriented()));
        QObject::connect(supprimer, SIGNAL(clicked()), this, SLOT(supprimerCouple()));

        ///Ajout des boutons
       layout->addWidget(listeNotesLeft, 0, 0);

        layout->addWidget(listeNotesRight, 0, 2);

        layout->addWidget(addCouple, 1, 1);

        layout->addWidget(addNotOrientedCouple, 2, 1);

        layout->addWidget(supprimer, 3, 1);


        centralContainer->setLayout(layout);

        this->setCentralWidget(centralContainer);
}
///Fonction pour créer le dock qui affiche les couples
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
   qDebug()<<"dock couple";
   ///On utilise l'iterator de CouplesManager pour afficher les couples existants
   listeCouples->clear();
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

/// Fonction pour enregistrer le CouplesManager dans un XML
void VueSecondaire::enregistrerCouplesManager(){
    couplesManager.save();
    statusBar()->showMessage(tr("Le couplesManager a été enregistré dans le fichier couples.xml"));
    QMessageBox msgBox(QMessageBox::Icon::Information, "Enregistrement du CouplesManager", "Le CouplesManager a été enregistré");
    msgBox.exec();
}

///Fonction qui permet de choisir le fichier XML contenant les couples
void VueSecondaire::choixFichier(){
    QString filename = QFileDialog::getOpenFileName();
    couplesManager.setFilename(filename);
    couplesManager.load();
    statusBar()->showMessage(tr("Chargement du fichier couples.xml"));
    QMessageBox msgBox(QMessageBox::Icon::Information, "Chargement du fichier sélectionné", "Les données du fichier de couples ont été récupérées.");
    msgBox.exec();
}

///Slot permettant d'ajouter un couple orienté
void VueSecondaire::addOrientedCouple(){
    ///On récupère la note n1 dans le QlistWidget listeNotesLeft
    QListWidgetItem* selectedItem1 = listeNotesLeft->currentItem();
    QString title1 = selectedItem1->text();
    Note* n1 = NotesManager::getManager().getNoteActiveByTitle(title1);
    ///On récupère la note n2 dans le QlistWidget listeNotesRight
    QListWidgetItem* selectedItem2 = listeNotesRight->currentItem();
    QString title2 = selectedItem2->text();
    Note* n2 = NotesManager::getManager().getNoteActiveByTitle(title2);
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
    Note* n1 = NotesManager::getManager().getNoteActiveByTitle(title1);
    ///On récupère la note n2 dans le QlistWidget listNotesRight
    QListWidgetItem* selectedItem2 = listeNotesRight->currentItem();
    QString title2 = selectedItem2->text();
    Note* n2 = NotesManager::getManager().getNoteActiveByTitle(title2);
    CouplesManager& cm = CouplesManager::getManager();
    ///Ajout d'un couple de n1 vers n2 dans le CouplesManager
    cm.addCouple(*(n1),*(n2));
    ///Ajout d'un couple de n1 vers n2 dans le CouplesManager
    cm.addCouple(*(n2),*(n1));
    updateDockCouples();
    ///MessageBox attestant du succès de l'ajout de la relation non orientée
    QMessageBox::information(this, "Succès", "Le couple non orienté a bien été ajouté");
}

///Slot permettant de supprimer un couple
void VueSecondaire::supprimerCouple(){
    if(!listeCouples->currentItem() == 0){
    QListWidgetItem* selectedItem = listeCouples->currentItem();
    ///On récupère son texte
            QString temp = selectedItem->text();
            ///On split ce texte à chaque espace
            QStringList templist = temp.split(" ");

            ///Appel d'une instance de CouplesManager
            CouplesManager& cm = CouplesManager::getManager();
            cm.removeCoupleById(templist[0],templist[2]);
            qDebug()<<"Couple supprimé"<<templist[0]<<"->"<<templist[2];
          updateDockCouples();
          statusBar()->showMessage(tr("Couple supprimé"));

    }
}
