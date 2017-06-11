#ifndef PLURINOTES_APP_H
#define PLURINOTES_APP_H

#include "qt_include.h"
#include "notes.h"
#include "vueprincipale.h"
#include "vuesecondaire.h"

typedef enum {Principale, Secondaire} NomVue;

// Application
class PluriNotes : public QApplication {

public:

    // Fonction donneInstance du Design Pattern Singleton :
    static PluriNotes& donnePluriNotesInstance(int &argc, char **argv, const QString& _name="PluriNotes");

    ~PluriNotes(){
        delete barreOnglets;
    }

    // Affichage de la vue qui correspond à l'argument d'entrée :
    void focusOn(NomVue nom);

private:
    Q_OBJECT

    const QString& name;

    VuePrincipale* vuePrincipale;
    VueSecondaire* vueSecondaire;

    QTabWidget* barreOnglets;

    // On initialise nos managers :
    NotesManager& notesManager = NotesManager::getManager();

    static PluriNotes* plurinotesUniqueInstance;

    QMenuBar* createMenu();

    PluriNotes(int &argc, char **argv, const QString& _name);

public slots:

    // Actualiser les docks après qu'on ait créé une nouvelle Note
    void actualiserListes(){
        vuePrincipale->actualiserLesDocks();
    }
    // Charge un fichier XML
    void chargerXML(){
        vuePrincipale->remplirDockListeNotes();
    }

    // Enregistre le NotesManager dans un XML
    void enregistrer(){
        vuePrincipale->enregistrerNotesManager();
    }

    /*void montrerNote(){
        vuePrincipale->showNote();
    }*/
};

#endif // PLURINOTES_APP_H
