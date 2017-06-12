#ifndef VUEPRINCIPALE_H
#define VUEPRINCIPALE_H

#include "qt_include.h"
#include "notes.h"

typedef enum {Notes, Taches, Archives} TypeListe;

// Vue principale de l'appli (premier onglet)
class VuePrincipale : public QMainWindow {
public:
    VuePrincipale();

    // Message sur l'écran central initial
    void accueil();

    // Charge le fichier XML et afficher les titres dans le dock à gauche
    void remplirDockListeNotes();

    // Enregistre le NotesManager dans un fichier XML
    void enregistrerNotesManager();

    // Fonction d'affichage dans la zone centrale dépendant du type entré en paramètre
    void afficher(const TypeListe type);

    // Remplit les champs de note de la classe à partir d'une note passée en paramètre
    void setNoteCourante(const Note& note);


    //***** Fonctions de slots *****//

    //Actualise les notes affichées
    void actualiserLesDocks();

    // Fait pointer noteCourante sur la note selectionnée dans un dock
    void afficherNoteCourante();

private:

    Q_OBJECT

    //
    void createToolbar();
    void createStatusBar();
    void createDockWindows();

    // Attributs de la note courante
    QLabel* titre;
    QLabel* id;
    QLabel* texte;
    QLabel* statut;
    QLabel* dateCreation;
    QLabel* dateLastModif;

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

    NotesManager& notesManager = NotesManager::getManager();

public slots :

};

#endif // VUEPRINCIPALE_H
