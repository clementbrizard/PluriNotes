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

    // getters
    static PluriNotes* getPluriNotesInstance(){ return plurinotesUniqueInstance; }
    const Note* getNoteCourante() { return noteCourante; }

    // setters
    void setNoteCourante(Note* noteC){ noteCourante = noteC; }


private:
    Q_OBJECT

    const QString& name;

    VuePrincipale* vuePrincipale;
    VueSecondaire* vueSecondaire;

    QTabWidget* barreOnglets;

    Note* noteCourante;

    // On initialise nos managers :
    NotesManager& notesManager = NotesManager::getManager();

    static PluriNotes* plurinotesUniqueInstance;


    QMenuBar* createMenu();

    PluriNotes(int &argc, char **argv, const QString& _name);

public slots:

    // Actualiser les docks après qu'on ait créé une nouvelle Note
    void actualiserListes(){
        vuePrincipale->actualiserLesDocks();
        vueSecondaire->RelationEditeur();
    }
    // Charge un fichier XML
    void chargerXML(){
        vuePrincipale->choixFichier();
        vuePrincipale->remplirDockListeNotes();
        vuePrincipale->remplirDockTaches();
        vuePrincipale->remplirDockCorbeille();
        vueSecondaire->RelationEditeur();
    }
    //Charge le XML des relations
    void chargerXMLCouples(){
        vueSecondaire->choixFichier();
    }

    // Enregistre le NotesManager dans un XML
    void enregistrer(){
        vuePrincipale->enregistrerNotesManager();
    }
    // Slot de PluriNotes (PN) gérant l'appel de la fonction d'affichage de note
        void afficherNoteCourantePN(){
            vuePrincipale->afficherNoteCourante();
        }
};

#endif // PLURINOTES_APP_H
