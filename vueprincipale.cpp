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
    QObject::connect(listeNotes, SIGNAL(itemDoubleClicked(QListWidgetItem*)), PluriNotes::getPluriNotesInstance(), SLOT(afficherNoteCourantePN()));

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

    titre = new QLabel;
    id = new QLabel;
    texte = new QLabel;
    statut = new QLabel;
    dateCreation = new QLabel;
    dateLastModif = new QLabel;

    QPushButton* modifier = new QPushButton("Modifier");
    QPushButton* supprimer = new QPushButton("Supprimer");
    QPushButton* afficherVersions = new QPushButton("Anciennes versions");
    layoutHBoutons->addWidget(modifier);
    layoutHBoutons->addWidget(supprimer);
    layoutHBoutons->addWidget(afficherVersions);

    // Tests temp
    titre->setText("Titre de la note");
    id->setText("- ID : 1");
    texte->setText("Ethical irony keffiyeh craft beer pug. Ennui bitters chartreuse, post-ironic aesthetic single-origin coffee lomo shoreditch. VHS schlitz kogi drinking vinegar 3 wolf moon venmo, cloud bread tousled occupy 90's pitchfork artisan health goth. Pickled offal kitsch artisan crucifix, fixie snackwave PBR&B air plant. 8-bit butcher cred, tote bag deep v waistcoat austin. Intelligentsia shabby chic tumblr prism gluten-free, four dollar toast franzen shoreditch vice cloud bread vape four loko. Vexillologist mumblecore before they sold out chicharrones blog distillery 8-bit meggings cliche, flannel taiyaki."
                   "\n\n\n"
                   "Tattooed jianbing actually, hoodie VHS waistcoat mlkshk artisan lo-fi lomo kitsch venmo pour-over raw denim semiotics. Schlitz literally whatever migas edison bulb venmo, tofu selvage activated charcoal pitchfork air plant hoodie. Dreamcatcher portland tumblr, marfa pinterest wolf heirloom asymmetrical lumbersexual vaporware. Twee polaroid hot chicken, trust fund skateboard everyday carry gochujang tote bag deep v aesthetic. Quinoa cred semiotics, wolf neutra poke tilde tote bag brunch live-edge whatever. Single-origin coffee roof party raclette, shabby chic offal intelligentsia humblebrag cliche asymmetrical echo park kitsch gentrify occupy. Slow-carb pickled fixie, four dollar toast rethical."
                   "\n\n\n"
                   "Hella leggings wayfarers listicle, iPhone prism salvia live-edge enamel pin snackwave. Wolf VHS bespoke intelligentsia hammock meditation. Mumblecore tattooed snackwave, mustache DIY jean shorts gluten-free taxidermy seitan twee tumeric gochujang. Franzen man bun shaman wayfarers, you probably haven't heard of them try-hard blog swag hoodie pitchfork organic. Lyft umami banjo, sartorial you probably havent heard of them freegan butcher kale chips before they sold out pok pok snackwave thundercats celiac shaman glossier. Beard taxidermy ugh migas williamsburg swag, franzen narwhal activated charcoal banjo tacos palo santo meh. Typewriter put a bird on it cronut, prism celiac hoodie tbh.");
    texte->setFixedWidth(600);
    texte->setWordWrap(true);
    titre->setStyleSheet("font:italic; font-size:14px; padding:30px");
    statut->setText("Active");
    dateCreation->setText("- Créée le "+QDate::currentDate().toString("d MMMM yyyy"));
    dateLastModif->setText("- Modifiée dernièrement le "+QDate::currentDate().toString("d MMMM yyyy"));
    titre->setStyleSheet("font:bold; font-size:25px; padding:30px");

    layoutVertical->addWidget(titre, 0, Qt::AlignCenter);
    layoutVertical->addWidget(texte, 0, Qt::AlignCenter);
    layoutVertical->addWidget(id);
    layoutVertical->addWidget(statut);
    layoutVertical->addWidget(dateCreation);
    layoutVertical->addWidget(dateLastModif);

    layoutVertical->setAlignment(Qt::AlignTop);
    layoutVertical->addLayout(layoutHBoutons,1);

    centralContainer->setLayout(layoutVertical);
    this->setCentralWidget(centralContainer);
}

// Remplit les champs de note de la classe à partir d'une note passée en paramètre
void VuePrincipale::setNoteCourante(const Note& note)
{
    titre->setText(note.getTitle());
    id->setText("- ID : ");
    dateCreation->setText("- Créée le "+note.getDateCreation().toString("d MMMM yyyy")+".");
    dateLastModif->setText("- Modifiée dernièrement le "+(note.getDateLastModif().toString("d MMMM yyyy")+"."));

    //texte->setText();
    //statut->setText("- Statut : "+note.getStatut());


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
    createToolbar();
    createStatusBar();
    createDockWindows();

    accueil();

    //noteCourante(notesManager.getNoteTitle("Avant Propos"));
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

    statusBar()->showMessage(tr("Chargement du fichier notes.xml"));
    QMessageBox msgBox(QMessageBox::Icon::Information, "Chargement du fichier sélectionné", "Les données du fichier ont été récupérées.");
    msgBox.exec();
}

void VuePrincipale::enregistrerNotesManager(){
    notesManager.save();
    statusBar()->showMessage(tr("Le NotesManager a été enregistré dans le fichier notes.xml"));
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


    statusBar()->showMessage(tr("Docks à jour"));
}

// Fait pointer noteCourante sur la note selectionnée dans un dock
void VuePrincipale::afficherNoteCourante(){
    QListWidgetItem* selectedItem = listeNotes->currentItem();
    QString selectedItemText = selectedItem->text();
    statusBar()->showMessage(tr("Affichage de la note ")+selectedItemText);
    PluriNotes::getPluriNotesInstance()->setNoteCourante(&notesManager.getNoteByTitle(selectedItemText));
    afficher(Notes);
}

//void VuePrincipale::QuitApplication(){
//    NotesManager& nm = NotesManager::getManager();
//    nm.save();
//    qApp->quit();
//    nm.freeManager();
//    MainWindow::libererInstance();
//}
