#include "mainwindow.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QListWidget>
#include <QFileDialog>
#include "notes.h"
#include <QApplication>
#include <QMessageBox>
#include <QDockWidget>
MainWindow::MWHandler MainWindow::mw_handler=MWHandler();

MainWindow& MainWindow::getInstance() {
  // Si le pointeur vers l'instance unique pointe vers 0
  if(!mw_handler.instance) {
    mw_handler.instance=new MainWindow;
  }
  // Retour par ref vers l'instance unique
  return *mw_handler.instance;
}

void MainWindow::libererInstance() {
  // Liberation de la memoire allouee a l'instance unique
  delete mw_handler.instance;
  // Repasse le pointeur a null/nullptr/0 pour que le prochain appel a getInstance recree bien une instance
  mw_handler.instance=0;
}
MainWindow::MainWindow () {
    setWindowTitle("PluriNotes");
    setWindowState(Qt::WindowMaximized);
    centralArea = new QWidget;
    setCentralWidget(centralArea);
    centralLayout = new QGridLayout;
    centralArea->setLayout(centralLayout);

    QMenu* fichier = new QMenu;
    fichier = menuBar()->addMenu("&Fichier");
    QAction* showNotes = fichier->addAction("&Show Notes");
    QAction* updateNotes = fichier->addAction("&Actualiser Notes");
    QAction* loadNotes = fichier->addAction("&Load Notes");
    QAction* save = fichier->addAction("&Save");
    QAction* quit = fichier->addAction("&Quit");
loadNotes->setEnabled(true);
    QMenu* notes = new QMenu;
    notes = menuBar()->addMenu("&Notes");

    QMenu* menuEdition = new QMenu;
    menuEdition = menuBar()->addMenu("&Edition");

    QMenu* menuNote = new QMenu;
    menuNote = menuBar()->addMenu("&Add Note");
    QAction* createArticle = menuNote->addAction("&Article");
    QAction* createAudio = menuNote->addAction("&Audio");
    QAction* createImage = menuNote->addAction("&Image");
    QAction* createTask = menuNote->addAction("&Task");

    QMenu* menuDustbin = new QMenu;
    menuDustbin = menuBar()->addMenu("&Corbeille");

    //SLOTS
    QObject::connect(quit, SIGNAL(triggered()), this, SLOT(QuitApplication()));
    QObject::connect(loadNotes, SIGNAL(triggered()), this, SLOT(LoadData()));
    QObject::connect(showNotes, SIGNAL(triggered()), this, SLOT(showNotesManager()));
    QObject::connect(updateNotes, SIGNAL(triggered()), this, SLOT(updateNotes()));

}
void MainWindow::showNotesManager(){
    dockNotesManager = new NotesManagerWindow(tr("Liste des Notes"), this);
    dockNotesManager->setAllowedAreas(Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, dockNotesManager);
}
void MainWindow::LoadData(){
    NotesManager& m = NotesManager::getManager();
    QString filename = QFileDialog::getOpenFileName();
    m.setFilename(filename);
    m.load();
    MainWindow::updateNotes();
    QMessageBox msgBox(QMessageBox::Icon::Information, "Ajout données", "Les données ont été récupérées du fichier.");
    msgBox.exec();
//MainWindow::loadNotes->setEnabled(false);
}
void MainWindow::QuitApplication(){
    NotesManager& nm = NotesManager::getManager();
    nm.save();
    qApp->quit();
    nm.freeManager();
    MainWindow::libererInstance();
}
void MainWindow::updateNotes(){
    dockNotesManager->close();
    showNotesManager();
}
/* Affichage de la page d'accueil qui affiche les différents notes*/
/*Accueil::Accueil()
{
    NotesManager& m = NotesManager::getManager();
    QString filename = QFileDialog::getOpenFileName();
    m.setFilename(filename);
    m.load();
    //m.addArticle("Test2","Hello");
    //m.removeNote(m.getM_notes()[5]);
    layout1 = new QVBoxLayout();
    layout2 = new QVBoxLayout();
    Hlayout= new QHBoxLayout();
    setFixedSize(400, 400);
    //On affiche les titres de tous les articles disponibles
   //listNotes = new QListWidget();
    QListWidgetItem* item1;
    for(NotesManager::Iterator it=m.getIterator(); !it.isDone(); it.next()){
        item1 = new QListWidgetItem((it.current()).getId(), listNotes);
    }

    //QObject::connect(listWidget,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(afficherNote(QListWidgetItem*)));
    titre1 = new QLabel("Liste des notes", this);
    edit = new QPushButton("Editer",this);





layout1->addWidget(titre1);
layout1->addWidget(listNotes);
layout1->addWidget(edit);*/

/****Menu****/
 /*   titre2 = new QLabel("Menu", this);
    newArticle = new QPushButton("Créer un article",this);
    newImage = new QPushButton("Ajouter une image",this);
    viewRelation = new QPushButton("Voir les relations",this);
    quit = new QPushButton("Quitter",this);
    layout2->addWidget(titre2);
    layout2->addWidget(newArticle);
    layout2->addWidget(newImage);
    layout2->addWidget(viewRelation);
    layout2->addWidget(quit);
    Hlayout->addLayout(layout2);
    Hlayout->addLayout(layout1);
    QObject::connect(edit,SIGNAL(clicked()),this,SLOT(ArticleEdit()));
    QObject::connect(quit,SIGNAL(clicked()),this,SLOT(quit()));
    setLayout(Hlayout);
}*/
ArticleEditeur::ArticleEditeur(Article& a) : article(a)
{

    layout = new QVBoxLayout();
    id1 = new QLabel("Identificateur", this);
    titre1 = new QLabel("Titre", this);
    text1 = new QLabel("Texte", this);
    id = new QLineEdit(this);
    date_c1 = new QLabel("Date de création", this);
    date_c = new QLineEdit(this);
    date_m1 = new QLabel("Date de modification", this);
    date_m = new QLineEdit(this);
    titre = new QLineEdit(this);
    text = new QTextEdit(this);
    save = new QPushButton("Sauver", this);
next = new QPushButton ("next",this);
    setFixedSize(800, 800);

    id->setText(a.getId());
    id->setEnabled(false);
    date_c->setEnabled(false);
    date_m->setEnabled(false);
    titre->setText(a.getTitle());
    text->setText(a.getText());
    save->setEnabled(false);


    layout->addWidget(id1);
    layout->addWidget(id);
    layout->addWidget(titre1);
    layout->addWidget(titre);
    layout->addWidget(date_c1);
    layout->addWidget(date_c);
    layout->addWidget(date_m1);
    layout->addWidget(date_m);
    layout->addWidget(text1);
    layout->addWidget(text);
    layout->addWidget(next);
    layout->addWidget(save);

    QObject::connect(save, SIGNAL(clicked()), this, SLOT(handleSave()));
    QObject::connect(titre, SIGNAL(textChanged(QString)), this, SLOT(handleChange(QString)));
    QObject::connect(text, SIGNAL(textChanged(QString)), this, SLOT(handleChange(QString)));
    setLayout(layout);
}

void ArticleEditeur::handleSave(){
    article.setTitle(titre->text());
    article.setText(text->toPlainText());

    //NotesManager::getManager().save();

    QMessageBox msgBox(QMessageBox::Icon::Information, "Sauvegarde", "Le document a été sauvegardé.");
    msgBox.exec();
    save->setEnabled(false);

}

void ArticleEditeur::handleChange(QString s){
    save->setEnabled(true);
}

ArticleEditeur::~ArticleEditeur()
{

}
/*Accueil::~Accueil()
{

}*/
/*void Accueil::ArticleEdit(){
    QListWidgetItem* selectedItem1 = listNotes->currentItem();
    QString id = selectedItem1->text();
    NotesManager& m= NotesManager::getManager();
    for(NotesManager::Iterator it=m.getIterator(); !it.isDone(); it.next()){
        if (it.current().getId()==id){
            Article& a = it.current();
            ArticleEditeur* fenetre = new ArticleEditeur(a);
    }}*/

        /*if(!listNotes->currentItem() == 0){
            Note* n = NotesManager::getInstance().getNoteWithTitle(title);
            NoteEditeur* ne = NotesManager::getInstance().callEditeur(n,n->getClassName());
            MainWindow::getInstance().setEditeur(ne);
            ne = MainWindow::getInstance().getEditeur();
            MainWindow::getInstance().showEditeur(ne);
        }
        else {throw NotesException("Couldn't show the note..");}*/

//}

/*void Accueil::article_edit(Article& a){
    //ArticleEditeur::ArticleEditeur(a);

}*/
