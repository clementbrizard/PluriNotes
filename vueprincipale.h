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
    //void updateNoteCourante(const Note& note);

    //Remplit le dock qui affiche la corbeille
    void remplirDockCorbeille();
    //Remplit le dock archive
    void remplirDockArchive();
    //***** Fonctions de slots *****//

    //Actualise les notes affichées
    void actualiserLesDocks();

    // Fait pointer noteCourante sur la note selectionnée dans un dock et l'affiche
    void afficherNoteCourante();

    // Fait pointer noteCourante sur la tache selectionnée dans un dock et l'affiche
    void afficherTacheCourante();

    //void afficherNoteEditeur();
    //Affiche le createur de note
    //void noteCreator(const QString& type);

private:

    Q_OBJECT

    // Fonctions de lancement de l'affichage
    void createToolbar();
    void createStatusBar();
    void createDockWindows();

    // Message d'accueil
    QLabel* messageAccueil;

    // Attributs de la note courante
    QLineEdit* titre;
    QLineEdit* id;
    QTextEdit* texte;
    QLabel* texteT;
    QLineEdit* statut;
    QLineEdit* description;
    QLineEdit* imageFileName;
    QLineEdit* dateCreation;
    QLineEdit* dateLastModif;
    QLineEdit* action;
    QLineEdit* priority;
    QLineEdit* deadline;

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
