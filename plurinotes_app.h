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
        vueSecondaire->CouplesEditeur();
    }
    // Charge un fichier XML
    void chargerXML(){
        vuePrincipale->choixFichier();
        vuePrincipale->remplirDockListeNotes();
        vuePrincipale->remplirDockTaches();
        vuePrincipale->remplirDockArchive();
        vueSecondaire->CouplesEditeur();
    }

    //Charge le XML des couples
    void chargerXMLCouples(){
        vueSecondaire->choixFichier();
        vueSecondaire->remplirCouplesDock();
    }

    // Enregistre le NotesManager et le CouplesManager dans leur XML respectif
    void enregistrer(){
        vuePrincipale->enregistrerNotesManager();
        vueSecondaire->enregistrerCouplesManager();
    }

    // Slot de PluriNotes (PN) gérant l'appel de la fonction d'affichage de Note
    void afficherNoteCourantePN(){
        vuePrincipale->afficherNoteCourante();
    }

    // Slot de PluriNotes (PN) gérant l'appel de la fonction d'affichage de Task
    void afficherTacheCourantePN(){
        vuePrincipale->afficherTacheCourante();
    }

    // Slot de PluriNotes (PN) gérant l'appel de la fonction d'affichage de Task
    void afficherArchiveCourantePN(){
        vuePrincipale->afficherArchiveCourante();
    }

    // Slot de PluriNotes (PN) gérant l'appel de la fonction d'affichage de la fenetre de creation d'article
    void afficherCreationArticlePN(){
        QObject::connect(&CreationArticleWindow::getCreationArticleWindow(), SIGNAL(fermer()), vuePrincipale, SLOT(actualiserListes()));
    }

    // Slot de PluriNotes (PN) gérant l'appel de la fonction d'affichage de la fenetre de creation de tache
    void afficherCreationTachePN(){
        QObject::connect(&CreationTacheWindow::getCreationTacheWindow(), SIGNAL(fermer()), vuePrincipale, SLOT(actualiserListes()));
    }

    /// Slot de PluriNotes(PN) gérant la modification d'une note
    void enregistrerModifsOfNotePN(){
        vuePrincipale->enregistrerModifsOfNote();
    }

    /// Slot de PluriNotes (PN) gérant la suppression d'une note
    void supprimerNotePN(){
        vuePrincipale->supprimerNote();
    }

    //void afficherVersionsPN(Note *n);
};

#endif // PLURINOTES_APP_H
