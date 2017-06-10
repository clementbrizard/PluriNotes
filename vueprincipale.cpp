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

// Fonction de création des Docks lattéraux
void VuePrincipale::createDockWindows()
{
    QDockWidget* dockListeNotes = new QDockWidget("Notes", this);
    dockListeNotes->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    listeNotes = new QListWidget(dockListeNotes); // listeNotes est le fils de dockListeNotes

    dockListeNotes->setWidget(listeNotes);
    this->addDockWidget(Qt::LeftDockWidgetArea, dockListeNotes);
}

VuePrincipale::VuePrincipale()
    : QMainWindow(), listeNotes(nullptr)
{

    //QWidget* zoneCentrale = new QWidget;


    createToolbar();
    createStatusBar();
    createDockWindows();

    accueil();
}

/********* SLOTS **********/


//void VuePrincipale::showNotesManager(){
//    dockNotesManager = new NotesManagerWindow(tr("Liste des Notes"), this);
//    dockNotesManager->setAllowedAreas(Qt::LeftDockWidgetArea);
//    addDockWidget(Qt::LeftDockWidgetArea, dockNotesManager);
//}

//void VuePrincipale::LoadData(){
//    NotesManager& m = NotesManager::getManager();
//    QString filename = QFileDialog::getOpenFileName();
//    m.setFilename(filename);
//    m.load();
//    MainWindow::updateNotes();
//    QMessageBox msgBox(QMessageBox::Icon::Information, "Ajout données", "Les données ont été récupérées du fichier.");
//    msgBox.exec();
//MainWindow::loadNotes->setEnabled(false);
//}

//void VuePrincipale::QuitApplication(){
//    NotesManager& nm = NotesManager::getManager();
//    nm.save();
//    qApp->quit();
//    nm.freeManager();
//    MainWindow::libererInstance();
//}

//void VuePrincipale::updateNotes(){
//    dockListeNotes->close();
//    showNotesManager();
//}
