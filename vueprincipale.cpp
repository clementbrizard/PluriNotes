#include "plurinotes_app.h"
#include "vueprincipale.h"


// Barre d'outils
void VuePrincipale::createToolbar()
{
    QToolBar* toolBar = new QToolBar;

    toolBar = this->addToolBar("Créer une Note");

    // Article
    QAction* ajouterArticle = new QAction("Créer un article", this);
    toolBar->addAction(ajouterArticle);
    toolBar->addSeparator();

    // Article
    QAction* ajouterAudio = new QAction("Créer un audio", this);
    toolBar->addAction(ajouterAudio);
    toolBar->addSeparator();

    // Article
    QAction* ajouterImage = new QAction("Créer une image", this);
    toolBar->addAction(ajouterImage);
    toolBar->addSeparator();

    // Article
    QAction* ajouterTache = new QAction("Créer une tâche", this);
    toolBar->addAction(ajouterTache);
    toolBar->addSeparator();

}

// Barre de Status
void VuePrincipale::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

// Message sur l'écran central initial
void VuePrincipale::accueil()
{
    QLabel* messageAccueil = new QLabel;
    messageAccueil->setText("Bienvenue \n Logiciel PluriNotes");
    messageAccueil->setFont(QFont("Courier", 20, QFont::Bold));
    messageAccueil->setAlignment(Qt::AlignCenter);
    this->setCentralWidget(messageAccueil);
}

// Fonction de création des Docks latéraux
void VuePrincipale::createDockWindows()
{
    // Dock de Notes
    dockListeNotes->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    listeNotes = new QListWidget(dockListeNotes); // listeNotes est le fils de dockListeNotes
    dockListeNotes->setWidget(listeNotes);
    this->addDockWidget(Qt::LeftDockWidgetArea, dockListeNotes);

    // Dock de Taches
    dockListeTaches->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    listeTaches = new QListWidget(dockListeTaches);
    dockListeTaches->setWidget(listeTaches);
    this->addDockWidget(Qt::LeftDockWidgetArea, dockListeTaches);

    // Dock des notes archivées
    dockListeArchives->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    listeArchives = new QListWidget(dockListeArchives);
    dockListeArchives->setWidget(listeArchives);
    this->addDockWidget(Qt::LeftDockWidgetArea, dockListeArchives);

    // Dock des arborescences
    dockArborescence->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    QWidget* conteneurDockArborescence = new QWidget(dockArborescence);
    QVBoxLayout* layoutConteneurDockArborescence = new QVBoxLayout();
    conteneurDockArborescence->setLayout(layoutConteneurDockArborescence);

    arborescenceAscendants = new QTreeWidget(dockArborescence);
    layoutConteneurDockArborescence->addWidget(arborescenceAscendants);
    arborescenceDescendants = new QTreeWidget(dockArborescence);
    layoutConteneurDockArborescence->addWidget(arborescenceDescendants);

    this->addDockWidget(Qt::RightDockWidgetArea, dockArborescence);

}

void VuePrincipale::afficher(const TypeListe type)
{
    // Layouts et positionnement
    QWidget* centralContainer = new QWidget;
    QVBoxLayout* layoutVertical = new QVBoxLayout;
    QHBoxLayout* layoutHBoutons = new QHBoxLayout;

    QLabel* titre = new QLabel;
    QLabel* id = new QLabel;
    QLabel* texte = new QLabel;
    QLabel* statut = new QLabel;
    QLabel* dateCreation = new QLabel;
    QLabel* dateLastModif = new QLabel;

    QPushButton* modifier = new QPushButton("Modifier");
    QPushButton* supprimer = new QPushButton("Supprimer");
    QPushButton* afficherVersions = new QPushButton("Anciennes versions");
    layoutHBoutons->addWidget(modifier);
    layoutHBoutons->addWidget(supprimer);
    layoutHBoutons->addWidget(afficherVersions);

    // Tests temp
    titre->setText("Titre de la note");
    id->setText("1");
    texte->setText("bla bla bla \n nlafsdg dfg dfg dfg dgerg hr rthdfd \n sdfgsdfer ergdfv szfgsd g.");
    statut->setText("Active");
    dateCreation->setText(QDate::currentDate().toString("d MMMM yyyy"));
    dateLastModif->setText(QDate::currentDate().toString("d MMMM yyyy"));

    layoutVertical->addWidget(titre, 0, Qt::AlignCenter);
    layoutVertical->addWidget(id);
    layoutVertical->addWidget(texte);
    layoutVertical->addWidget(statut);
    layoutVertical->addWidget(dateCreation);
    layoutVertical->addWidget(dateLastModif);

    layoutVertical->setAlignment(Qt::AlignTop);
    layoutVertical->addLayout(layoutHBoutons);

    centralContainer->setLayout(layoutVertical);
    this->setCentralWidget(centralContainer);
}

VuePrincipale::VuePrincipale()
    : QMainWindow(),
      listeNotes(nullptr),
      listeTaches(nullptr),
      listeArchives(nullptr),
      arborescenceAscendants(nullptr),
      arborescenceDescendants(nullptr),
      dockListeNotes(new QDockWidget("Notes", this)),
      dockListeTaches(new QDockWidget("Taches", this)),
      dockListeArchives(new QDockWidget("Archives", this)),
      dockArborescence(new QDockWidget("Arborescence", this))
{

    //QWidget* zoneCentrale = new QWidget;


    createToolbar();
    createStatusBar();
    createDockWindows();

    accueil();
    afficher(Note);
}


/********* SLOTS **********/

void VuePrincipale::remplirDockListeNotes(){

    QString filename = QFileDialog::getOpenFileName();
    notesManager.setFilename(filename);
    notesManager.load();

    QListWidgetItem* item;
    for(NotesManager::Iterator it=notesManager.getIterator(); !it.isDone(); it.next()){
        item= new QListWidgetItem((it.current()).getTitle(),listeNotes);
    }

    //dockListeNotes->setWidget(listeNotes);

    QMessageBox msgBox(QMessageBox::Icon::Information, "Chargement du fichier sélectionné", "Les données du fichier ont été récupérées.");
    msgBox.exec();
}

void VuePrincipale::enregistrerNotesManager(){
    notesManager.save();
    QMessageBox msgBox(QMessageBox::Icon::Information, "Enregistrement du NotesManager", "Le NotesManager a été enregistré");
    msgBox.exec();
}

// Fonction qui permet d'actualiser tous les docks après la création d'une nouvelle note

void VuePrincipale::actualiserLesDocks(){
    //notesManager.addTask("TestTask","manger","3",QDate(2017, 04, 11));
    // Dock des Notes
    dockListeNotes->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    listeNotes = new QListWidget(dockListeNotes); // listeNotes est le fils de dockListeNotes
    dockListeNotes->setWidget(listeNotes);
    this->addDockWidget(Qt::LeftDockWidgetArea, dockListeNotes);

    //On reremplit avec les notes du notesManager
    QListWidgetItem* item;
    for(NotesManager::Iterator it=notesManager.getIterator(); !it.isDone(); it.next()){
        item= new QListWidgetItem((it.current()).getTitle(),listeNotes);
    }

    // Dock des Taches
    dockListeTaches->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    listeTaches = new QListWidget(dockListeTaches);
    dockListeTaches->setWidget(listeTaches);
    this->addDockWidget(Qt::LeftDockWidgetArea, dockListeTaches);

    // Reremplir avec les éventuelles nouvelles taches

    // Dock des notes archivées
    dockListeArchives->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    listeArchives = new QListWidget(dockListeArchives);
    dockListeArchives->setWidget(listeArchives);
    this->addDockWidget(Qt::LeftDockWidgetArea, dockListeArchives);

    // Reremplir avec les éventuelles nouvelles notes archivées
}


//void VuePrincipale::QuitApplication(){
//    NotesManager& nm = NotesManager::getManager();
//    nm.save();
//    qApp->quit();
//    nm.freeManager();
//    MainWindow::libererInstance();
//}
