#include "plurinotes_app.h"


PluriNotes* PluriNotes::plurinotesUniqueInstance = nullptr;

// Lancement de l'application :
PluriNotes::PluriNotes(int &argc, char **argv, const QString& _name)
    : QApplication(argc,argv), name(_name)
{

    plurinotesUniqueInstance = this;
    vuePrincipale = new VuePrincipale();
    vuePrincipale->setMenuBar(createMenu());
    vueSecondaire = new VueSecondaire();
    vueSecondaire->setMenuBar(createMenu());

    barreOnglets = new QTabWidget();
    barreOnglets->setWindowTitle(name);
    barreOnglets->addTab(vuePrincipale, "Notes");
    barreOnglets->addTab(vueSecondaire,"Relations");
    barreOnglets->showMaximized();
}

// Fonction donneInstance du Design Pattern Singleton
PluriNotes& PluriNotes::donnePluriNotesInstance(int &argc, char **argv, const QString& _name) {
    if(plurinotesUniqueInstance == nullptr)
        plurinotesUniqueInstance = new PluriNotes(argc, argv,_name);
    return *plurinotesUniqueInstance;
}

// Création de la barre de menu :
QMenuBar* PluriNotes::createMenu() {

    QMenuBar* menubar = new QMenuBar();

    // Menu Fichier :
    QMenu* fichier = menubar->addMenu("&Fichier");
    QAction* showNotes = fichier->addAction("&Afficher les notes");
    QAction* updateNotes = fichier->addAction("&Actualiser les notes");

    QAction* loadNotes = fichier->addAction("&Charger les notes");
    loadNotes->setEnabled(true);
    QObject::connect(loadNotes, SIGNAL(triggered()), this, SLOT(chargerXML()));

    QAction* save = fichier->addAction("&Enregistrer");
    save->setShortcut(Qt::Key_S | Qt::CTRL);

    QAction* quit = fichier->addAction("&Quitter");
    quit->setShortcut(Qt::Key_Q | Qt::CTRL);
    QObject::connect(quit, SIGNAL(triggered()), this, SLOT(quit()));
    //QObject::connect(this, SIGNAL(aboutToQuit()), this SLOT(saveBeforeExit()));

    // Menu Edition :
    QMenu* menuEdition = new QMenu;
    menuEdition = menubar->addMenu("&Edition");

    // Menu Notes ????????
    QMenu* notes = new QMenu;
    notes = menubar->addMenu("&Notes");

    // Menu Corbeille :
    QMenu* menuDustbin = new QMenu;
    menuDustbin = menubar->addMenu("&Corbeille");

    //SLOTS
    QObject::connect(quit, SIGNAL(triggered()), this, SLOT(QuitApplication()));

    QObject::connect(showNotes, SIGNAL(triggered()), this, SLOT(showNotesManager()));
    QObject::connect(updateNotes, SIGNAL(triggered()), this, SLOT(updateNotes()));

    return menubar;
}

void PluriNotes::focusOn(NomVue nom){
    switch (nom) {
        case Principale:
            barreOnglets->setCurrentIndex(0);
            break;
        case Secondaire:
            barreOnglets->setCurrentIndex(1);
            break;
        default:
            break;
    }
}
