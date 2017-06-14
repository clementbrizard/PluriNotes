#ifndef VUEPRINCIPALE_H
#define VUEPRINCIPALE_H

#include "qt_include.h"
#include "notes.h"
#include "couples.h"

typedef enum {Notes, Taches, Archives} TypeListe;

// Vue principale de l'appli (premier onglet)
class VuePrincipale : public QMainWindow {
public:
    VuePrincipale();

    // Message sur l'écran central initial
    void accueil();

    //Charge le fichier XML
    void choixFichier();

    // afficher les titres dans le dock à gauche
    void remplirDockListeNotes();

    //Remplit le dock avec les taches
    void remplirDockTaches();

    // Enregistre le NotesManager dans un fichier XML
    void enregistrerNotesManager();

    // Fonction d'affichage dans la zone centrale dépendant du type entré en paramètre
    void afficher(const TypeListe type);

    // Remplit les champs de note de la classe à partir d'une note passée en paramètre
    void setNoteCourante(const Note& note);

    //Remplit le dock qui affiche la corbeille
    void remplirDockCorbeille();

    //***** Fonctions de slots *****//

    //Actualise les notes affichées
    void actualiserLesDocks();

    // Fait pointer noteCourante sur la note selectionnée dans un dock
    void afficherNoteCourante();
    //void afficherNoteEditeur();
    //Affiche le createur de note
    //void noteCreator(const QString& type);

private:

    Q_OBJECT

    //
    void createToolbar();
    void createStatusBar();
    void createDockWindows();


    // Attributs de la note courante
    QLabel* titreT;
    QLabel* idT;
    QLabel* texteT;
    QLabel* statutT;
    QLabel* dateCreationT;
    QLabel* dateLastModifT;
    QLineEdit* titre;
    QLineEdit* id;
    QTextEdit* texte;
    QLineEdit* statut;
    QLineEdit* dateCreation;
    QLineEdit* dateLastModif;

    // Attributs pour l'affichage dans les docks
    QListWidget* listeNotes;
    QListWidget* listeTaches;
    QListWidget* listeArchives;
    QTreeWidget* arborescenceAscendants;
    QTreeWidget* arborescenceDescendants;

    // Docks
    QDockWidget* dockListeNotes;
    QDockWidget* dockListeTaches;
    QDockWidget* dockListeArchives;
    QDockWidget* dockArborescence;

    // initialisation des Managers
    NotesManager& notesManager = NotesManager::getManager();
    CouplesManager& couplesManager = CouplesManager::getManager();

public slots :
  //void noteCreator(const QString& type);
};

#endif // VUEPRINCIPALE_H
