#include "plurinotes_app.h"
#include "vueprincipale.h"


//***** CREATION ARTICLE *****//
/// Constructeur de CreationArticleWindow
CreationArticleWindow::CreationArticleWindow()
    : titre(new QLineEdit(this)),
      texte(new QTextEdit(this)),
      creer(new QPushButton("Créer",this))
{
    QVBoxLayout* layoutV = new QVBoxLayout;
    QFormLayout* layoutForm = new QFormLayout;

    QLabel* nomFenetre = new QLabel;
    nomFenetre->setText("Créer un article");
    nomFenetre->setAlignment(Qt::AlignCenter);
    nomFenetre->setStyleSheet("font-size:16px; padding:30px; text-align:center;");

    layoutForm->addRow("Titre", titre);
    layoutForm->addRow("Texte", texte);

    layoutV->addWidget(nomFenetre);
    layoutV->addLayout(layoutForm);
    layoutV->addWidget(creer, 0, Qt::AlignCenter);

    QObject::connect(creer, SIGNAL(clicked()), this, SLOT(enregistrer()));

    setLayout(layoutV);
}

/// Slot de CreationArticleWindow permettant d'enregistrer l'article créé dans le NoteManager
void CreationArticleWindow::enregistrer()
{
    QString titreStr = titre->text();
    if(!titreStr.isEmpty()){
        NotesManager::getManager().addArticle(titreStr, tr("active"),texte->toPlainText());
        NotesManager::getManager().save();
        this->close();
        emit fermer();
    }
}

//***** CREATION TACHE *****//
/// Constructeur de CreationTacheWIndow
CreationTacheWindow::CreationTacheWindow()
    : titre(new QLineEdit(this)),
      action(new QLineEdit(this)),
      priority(new QLineEdit(this)),
      deadline(new QDateEdit(this)),
      creer(new QPushButton("Créer",this))
{
    QVBoxLayout* layoutV = new QVBoxLayout;
    QFormLayout* layoutForm = new QFormLayout;

    QLabel* nomFenetre = new QLabel;
    nomFenetre->setText("Créer une tâche");
    nomFenetre->setAlignment(Qt::AlignCenter);
    nomFenetre->setStyleSheet("font-size:16px; padding:30px; text-align:center;");

    deadline->setMinimumDate(QDate::currentDate());
    deadline->calendarWidget();

    layoutForm->addRow("Titre", titre);
    layoutForm->addRow("Action", action);
    layoutForm->addRow("Pirorité", priority);
    layoutForm->addRow("Deadline (optionnel)", deadline);

    layoutV->addWidget(nomFenetre);
    layoutV->addLayout(layoutForm);
    layoutV->addWidget(creer, 0, Qt::AlignCenter);

    QObject::connect(creer, SIGNAL(clicked()), this, SLOT(enregistrer()));

    setLayout(layoutV);
}

/// Slot de CreationArticleWindow permettant d'enregistrer la tâche créée dans le NoteManager
void CreationTacheWindow::enregistrer()
{
    QString titreStr = titre->text();
    if(!titreStr.isEmpty() && !action->text().isEmpty()){
        NotesManager::getManager().addTask(titreStr, tr("active"), action->text(), priority->text(),deadline->date());
        NotesManager::getManager().save();
        this->close();
        emit fermer();
    }
}

//***** CREATION *****//


//***** VUE PRINCIPALE *****//

// Barre d'outils
void VuePrincipale::createToolbar()
{
    QToolBar* toolBar = new QToolBar;

    toolBar = this->addToolBar("Créer une Note");

    // Article
    QAction* ajouterArticle = new QAction("Créer un article", this);
    toolBar->addAction(ajouterArticle);
    toolBar->addSeparator();
    QObject::connect(ajouterArticle, SIGNAL(triggered()), PluriNotes::getPluriNotesInstance(), SLOT(afficherCreationArticlePN()));

    // Audio
    QAction* ajouterAudio = new QAction("Créer un audio", this);
    toolBar->addAction(ajouterAudio);
    toolBar->addSeparator();

    // Video
    QAction* ajouterVideo = new QAction("Créer une vidéo", this);
    toolBar->addAction(ajouterVideo);
    toolBar->addSeparator();

    // Image
    QAction* ajouterImage = new QAction("Créer une image", this);
    toolBar->addAction(ajouterImage);
    toolBar->addSeparator();

    // Tache
    QAction* ajouterTache = new QAction("Créer une tâche", this);
    toolBar->addAction(ajouterTache);
    toolBar->addSeparator();
    QObject::connect(ajouterTache, SIGNAL(triggered()), PluriNotes::getPluriNotesInstance(), SLOT(afficherCreationTachePN()));

}

// Barre de Status
void VuePrincipale::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

// Message sur l'écran central initial
void VuePrincipale::accueil()
{
    messageAccueil = new QLabel;
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
    QObject::connect(listeTaches, SIGNAL(itemDoubleClicked(QListWidgetItem*)), PluriNotes::getPluriNotesInstance(), SLOT(afficherTacheCourantePN()));

    // Dock des notes archivées
    dockListeArchives->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    listeArchives = new QListWidget(dockListeArchives);
    dockListeArchives->setWidget(listeArchives);
    this->addDockWidget(Qt::LeftDockWidgetArea, dockListeArchives);
    QObject::connect(listeArchives, SIGNAL(itemDoubleClicked(QListWidgetItem*)), PluriNotes::getPluriNotesInstance(), SLOT(afficherArchiveCourantePN()));


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

    // Création des Layouts et positionnement
    QWidget* centralContainer = new QWidget;
    QVBoxLayout* layoutVertical = new QVBoxLayout;
    QFormLayout* layoutForm = new QFormLayout;
    layoutForm->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
    layoutForm->setLabelAlignment(Qt::AlignLeft);
    QHBoxLayout* layoutHorizontal= new QHBoxLayout;
    QHBoxLayout* layoutHBoutons = new QHBoxLayout;

    // Création des widgets attributs
    titre = new QLineEdit;
    id = new QLineEdit;
    statut = new QLineEdit;
    dateCreation = new QLineEdit;
    dateLastModif = new QLineEdit;

    texte = new QTextEdit;
    texteT = new QLabel;
    description = new QLineEdit;
    imageFileName = new QLineEdit;
    action = new QLineEdit;
    priority = new QLineEdit;
    deadline = new QLineEdit;

    // On cache les attributs qui dépendent du type de la note
    texte->hide();
    action->hide();
    priority->hide();
    deadline->hide();
    description->hide();
    imageFileName->hide();

    // On interdit la modification des champs pour l'affichage de la note
    id->setEnabled(false);
    statut->setEnabled(false);
    dateCreation->setEnabled(false);
    dateLastModif->setEnabled(false);

    // On interdit la modification de tous les champs si la note est archivée
    if(type == Archives) {
        titre->setEnabled(false);
        // Le reste des interdit se fait dans les conditions dépendant des types de Note
    }

    // Feuille de style
    id->setStyleSheet("font-size:16px; padding:30px; text-align:center;");
    statut->setStyleSheet("font-size:13px; padding:30px; text-align:center;");
    dateCreation->setStyleSheet("font-size:13px; padding:30px; text-align:center;");
    dateLastModif->setStyleSheet("font-size:13px; padding:30px; text-align:center;");
    titre->setStyleSheet("font:bold; font-size:24px; padding:30px; text-align:center;");

    // Positionnement des boutons modifier / supprimer / aficherVersions
    QPushButton* modifier = new QPushButton("Modifier");
    QPushButton* supprimer = new QPushButton("Supprimer");
    QPushButton* afficherVersions = new QPushButton("Anciennes versions");
    layoutHBoutons->addWidget(modifier);
    layoutHBoutons->addWidget(supprimer);
    layoutHBoutons->addWidget(afficherVersions);

    layoutForm->addRow("Titre", titre);

    // Gestion du risque de bad_cast à cause du polymorphisme
    if(PluriNotes::getPluriNotesInstance()->getNoteCourante()->getType() == tr("art")) {
        const Note* note = new const Article("","","");
    } else if(PluriNotes::getPluriNotesInstance()->getNoteCourante()->getType() == tr("task")) {
        const Note* note = new const Task("","","","",QDate::currentDate());
    } else if(PluriNotes::getPluriNotesInstance()->getNoteCourante()->getType() == tr("vid")) {
        const Note* note = new const Video("","","","");
    } else if(PluriNotes::getPluriNotesInstance()->getNoteCourante()->getType() == tr("aud")) {
        const Note* note = new const Audio("","","","");
    } else if(PluriNotes::getPluriNotesInstance()->getNoteCourante()->getType() == tr("img")) {
        const Note* note = new const Image("","","","");
    }

    const Note* note = PluriNotes::getPluriNotesInstance()->getNoteCourante();

    // On definit et on positionne les widgets communs à tout type de note
    titre->setText(note->getTitle());
    id->setText(note->getId());
    statut->setText(note->getStatut());
    dateCreation->setText(note->getDateCreation().toString("d MMMM yyyy"));
    dateLastModif->setText(note->getDateLastModif().toString("d MMMM yyyy"));

    // On complète les attributs en fonction du type de Note
    if(note->getType() == tr("art")) {
        // Articles
        const Article* article = dynamic_cast<const Article*>(note);
        texte->setText(article->getText());
        texte->setStyleSheet("font-size:16px; padding:30px; text-align:center;");
        texte->show();
        texteT->setText("Texte");

        // On interdit la modification de tous les champs si la note est archivée
        if(type == Archives) {
            texte->setEnabled(false);
        }

        layoutHorizontal->addWidget(texteT);
        layoutHorizontal->addWidget(texte);

    } else if(note->getType() == "task" || type == Taches) {
        // Tâches
        action->setText(dynamic_cast<const Task*>(note)->getAction());
        priority->setText(dynamic_cast<const Task*>(note)->getPriority());
        deadline->setText(dynamic_cast<const Task*>(note)->getDeadline().toString("d MMMM yyyy"));
        action->setStyleSheet("font:bold; font-size:24px; padding:30px; text-align:center;");
        priority->setStyleSheet("font:bold; font-size:24px; padding:30px; text-align:center;");
        deadline->setStyleSheet("font:bold; font-size:24px; padding:30px; text-align:center;");
        action->show();
        priority->show();
        deadline->show();

        // On interdit la modification de tous les champs si la note est archivée
        if(type == Archives) {
            action->setEnabled(false);
            priority->setEnabled(false);
            deadline->setEnabled(false);
        }

        layoutForm->addRow("Action", action);
        layoutForm->addRow("Priorité", priority);
        layoutForm->addRow("Deadline (optionnelle)", deadline);

    } else if(note->getType() == "aud") {
        // Audios
        description->setText(dynamic_cast<const Audio*>(note)->getDescription());
        imageFileName->setText(dynamic_cast<const Audio*>(note)->getImageFileName());
        description->setStyleSheet("font-size:16px; padding:30px; text-align:center;");
        imageFileName->setStyleSheet("font-size:16px; padding:30px; text-align:center;");
        description->show();
        imageFileName->show();

        // On interdit la modification de tous les champs si la note est archivée
        if(type == Archives) {
            description->setEnabled(false);
            imageFileName->setEnabled(false);
        }

        layoutForm->addRow("Description", description);
        layoutForm->addRow("Nom du fichier audio", imageFileName);

    } else if(note->getType() == "vid") {
        // Vidéos
        description->setText(dynamic_cast<const Video*>(note)->getDescription());
        imageFileName->setText(dynamic_cast<const Video*>(note)->getImageFileName());
        description->setStyleSheet("font-size:16px; padding:30px; text-align:center;");
        imageFileName->setStyleSheet("font-size:16px; padding:30px; text-align:center;");
        description->show();
        imageFileName->show();

        // On interdit la modification de tous les champs si la note est archivée
        if(type == Archives) {
            description->setEnabled(false);
            imageFileName->setEnabled(false);
        }

        layoutForm->addRow("Description", description);
        layoutForm->addRow("Nom du fichier vidéo", imageFileName);

    } else if(note->getType() == "img") {
        // Images
        description->setText(dynamic_cast<const Image*>(note)->getDescription());
        imageFileName->setText(dynamic_cast<const Image*>(note)->getImageFileName());
        description->setStyleSheet("font-size:16px; padding:30px; text-align:center;");
        imageFileName->setStyleSheet("font-size:16px; padding:30px; text-align:center;");
        description->show();
        imageFileName->show();

        // On interdit la modification de tous les champs si la note est archivée
        if(type == Archives) {
            description->setEnabled(false);
            imageFileName->setEnabled(false);
        }

        layoutForm->addRow("Description", description);
        layoutForm->addRow("Nom du fichier image", imageFileName);
    }

    // On remplit nos layouts avant de les mettre dans le centralContainer
    layoutForm->addRow("ID", id);
    layoutForm->addRow("Statut", statut);
    layoutForm->addRow("Crée le", dateCreation);
    layoutForm->addRow("Dernière modification le", dateLastModif);

    layoutVertical->addLayout(layoutForm);
    if(note->getType() == "art")
        layoutVertical->addLayout(layoutHorizontal);
    layoutVertical->addLayout(layoutHBoutons);

    layoutVertical->setAlignment(Qt::AlignTop);

    centralContainer->setLayout(layoutVertical);
    this->setCentralWidget(centralContainer);
}

// Remplit les champs de note de la classe à partir d'une note passée en paramètre
/*void VuePrincipale::updateNoteCourante(const Note& note)
{
    titre->setText(note.getTitle());
    id->setText("- ID : ");
    dateCreation->setText("- Créée le "+note.getDateCreation().toString("d MMMM yyyy")+".");
    dateLastModif->setText("- Modifiée dernièrement le "+(note.getDateLastModif().toString("d MMMM yyyy")+"."));
    statusBar()->showMessage(note.getType());
    QMessageBox msgBox(QMessageBox::Icon::Information, "  df", note.getType());
    msgBox.exec();

    //statut->setText("- Statut : "+note.getStatut());
}*/

/*void VuePrincipale::noteCreator(const QString& type)
{
    // Layouts et positionnement
    QWidget* centralContainer = new QWidget;
    QVBoxLayout* layoutVertical = new QVBoxLayout;
    QHBoxLayout* layoutHorizontal1 = new QHBoxLayout;
    QHBoxLayout* layoutHorizontal2 = new QHBoxLayout;
    QHBoxLayout* layoutHorizontal3 = new QHBoxLayout;
    QHBoxLayout* layoutHorizontal4 = new QHBoxLayout;
    QHBoxLayout* layoutHorizontal5 = new QHBoxLayout;
    QHBoxLayout* layoutHorizontal= new QHBoxLayout;
    QHBoxLayout* layoutHBoutons = new QHBoxLayout;
    //Affichage nom du widget
    titreT = new QLabel;
    idT = new QLabel;
    if(type=="art"){
    texteT = new QLabel;
    texte = new QTextEdit;
    }
    statutT = new QLabel;
    dateCreationT = new QLabel;
    dateLastModifT = new QLabel;
    //Affichage note dans zone édition
    titre = new QLineEdit;
    id = new QLineEdit;

    statut = new QLineEdit;
    dateCreation = new QLineEdit;
    dateLastModif = new QLineEdit;
    QPushButton* modifier = new QPushButton("Modifier");
    QPushButton* supprimer = new QPushButton("Supprimer");
    QPushButton* afficherVersions = new QPushButton("Anciennes versions");
    layoutHBoutons->addWidget(modifier);
    layoutHBoutons->addWidget(supprimer);
    layoutHBoutons->addWidget(afficherVersions);

    // Tests temp
    titreT->setText("Titre");
    titre->setText(PluriNotes::getPluriNotesInstance()->getNoteCourante()->getTitle());
    idT->setText("ID");
    id->setText(PluriNotes::getPluriNotesInstance()->getNoteCourante()->getId());
    texteT->setText("Texte");
    texte->setText("PluriNotes::getNoteCourante()->getfghd");
    statutT->setText("Statut");
    statut->setText(PluriNotes::getPluriNotesInstance()->getNoteCourante()->getStatut());
    dateCreationT->setText("Créée le ");
    dateCreation->setText(PluriNotes::getPluriNotesInstance()->getNoteCourante()->getDateCreation().toString("d MMMM yyyy"));
    dateLastModifT->setText("Modifiée dernièrement le ");
    dateLastModif->setText(PluriNotes::getPluriNotesInstance()->getNoteCourante()->getDateLastModif().toString("d MMMM yyyy"));
    titre->setStyleSheet("font:bold; font-size:25px; padding:30px; text-align:center;");
    //on interdit la modification des champs pour l'affichage de la note
    titre->setEnabled(true);
    id->setEnabled(true);
    texte->setEnabled(true);
    statut->setEnabled(true);
    dateCreation->setEnabled(true);
    dateLastModif->setEnabled(true);

    layoutHorizontal->addWidget(titreT);
    layoutHorizontal->addWidget(titre);
    layoutHorizontal1->addWidget(texteT);
    layoutHorizontal1->addWidget(texte);
    layoutHorizontal2->addWidget(idT);
    layoutHorizontal2->addWidget(id);
    layoutHorizontal3->addWidget(statutT);
    layoutHorizontal3->addWidget(statut);
    layoutHorizontal4->addWidget(dateCreationT);
    layoutHorizontal4->addWidget(dateCreation);
    layoutHorizontal5->addWidget(dateLastModifT);
    layoutHorizontal5->addWidget(dateLastModif);

    layoutVertical->addLayout(layoutHorizontal);
    layoutVertical->addLayout(layoutHorizontal1);
    layoutVertical->addLayout(layoutHorizontal2);
    layoutVertical->addLayout(layoutHorizontal3);
    layoutVertical->addLayout(layoutHorizontal4);
    layoutVertical->addLayout(layoutHorizontal5);
    layoutVertical->addLayout(layoutHBoutons,1);



    layoutVertical->setAlignment(Qt::AlignTop);


    centralContainer->setLayout(layoutVertical);
    this->setCentralWidget(centralContainer);
}*/
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
}



//***** SLOTS : VUE PRINCIPALE *****//
void VuePrincipale::choixFichier(){
    QString filename = QFileDialog::getOpenFileName();
    notesManager.setFilename(filename);
    notesManager.load();
}

void VuePrincipale::remplirDockListeNotes(){
    QListWidgetItem* item;
    for(NotesManager::Iterator it=notesManager.getIterator(); !it.isDone(); it.next()){
        if((it.current()).getType()!="task" && (it.current()).getStatut()=="active"){
            item= new QListWidgetItem((it.current()).getTitle(),listeNotes);}
    }
}

void VuePrincipale::remplirDockTaches(){

    QListWidgetItem* item;
    for(NotesManager::Iterator it=notesManager.getIterator(); !it.isDone(); it.next()){
        if((it.current()).getType()=="task" && (it.current()).getStatut()=="active"){
            item= new QListWidgetItem((it.current()).getTitle(),listeTaches);}
    }
}

void VuePrincipale::remplirDockCorbeille(){

    QListWidgetItem* item;
    for(unsigned int i=0;i<Corbeille::getInstance().getPoubelleSize();i++){
            Note* n = Corbeille::getInstance().getNoteByPosition(i);
            QString title = n->getTitle();
            item = new QListWidgetItem(title,listeArchives);
        }
    statusBar()->showMessage(tr("Chargement du fichier notes.xml"));
    QMessageBox msgBox(QMessageBox::Icon::Information, "Chargement du fichier sélectionné", "Les données du fichier de notes ont été récupérées.");
    msgBox.exec();
}

void VuePrincipale::remplirDockArchive(){

    QListWidgetItem* item;
    for(NotesManager::Iterator it=notesManager.getIterator(); !it.isDone(); it.next()){
        if((it.current()).getStatut()=="archivee"){
            item= new QListWidgetItem((it.current()).getTitle(),listeArchives);}
    }
    statusBar()->showMessage(tr("Chargement du fichier notes.xml"));
    QMessageBox msgBox(QMessageBox::Icon::Information, "Chargement du fichier sélectionné dock archive", "Les données du fichier de notes ont été récupérées.");
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
    createDockWindows();
    remplirDockListeNotes();
    remplirDockTaches();
    remplirDockCorbeille();
    statusBar()->showMessage(tr("Docks à jour"));
}

// Fait pointer noteCourante sur la note selectionnée dans un dock et l'affiche
void VuePrincipale::afficherNoteCourante(){
    QListWidgetItem* selectedItem = listeNotes->currentItem();
    QString selectedItemText = selectedItem->text();
    Note* noteCourante = notesManager.getNoteByTitle(selectedItemText);

    statusBar()->showMessage(tr("Affichage de la note ")+selectedItemText+(tr(" de type "))+noteCourante->getType());

    PluriNotes::getPluriNotesInstance()->setNoteCourante(noteCourante);
    afficher(Notes);
}

// Fait pointer noteCourante sur la tache selectionnée dans un dock et l'affiche
void VuePrincipale::afficherTacheCourante(){
    QListWidgetItem* selectedItem = listeTaches->currentItem();
    QString selectedItemText = selectedItem->text();
    Note* noteCourante = notesManager.getNoteByTitle(selectedItemText);

    statusBar()->showMessage(tr("Affichage de la tâche ")+selectedItemText);

    PluriNotes::getPluriNotesInstance()->setNoteCourante(noteCourante);
    afficher(Taches);
}

// Fait pointer noteCourante sur l'archive selectionnée dans un dock et l'affiche
void VuePrincipale::afficherArchiveCourante(){
    QListWidgetItem* selectedItem = listeArchives->currentItem();
    QString selectedItemText = selectedItem->text();
    Note* noteCourante = notesManager.getNoteByTitle(selectedItemText);

    statusBar()->showMessage(tr("Affichage de la note archivée ")+selectedItemText+(tr(" de type "))+noteCourante->getType());

    PluriNotes::getPluriNotesInstance()->setNoteCourante(noteCourante);
    afficher(Archives);
}

/*void VuePrincipale::afficherNoteEditeur(){
    statusBar()->showMessage(tr("Création Article "));
    //statusBar()->showMessage(tr("Affichage de la note ")+noteCourante->getTitle());
    PluriNotes::getPluriNotesInstance()->noteCreator("art");
    afficher(Notes);
}*/
