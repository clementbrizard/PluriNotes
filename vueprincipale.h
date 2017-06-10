#ifndef VUEPRINCIPALE_H
#define VUEPRINCIPALE_H

#include "qt_include.h"
#include "notes.h"

// Vue principale de l'appli (premier onglet)
class VuePrincipale : public QMainWindow {
public:
    VuePrincipale();

    // Message sur l'écran central initial
    void accueil();

    // Charger le fichier XML et afficher les titres dans le dock à gauche
    void remplirDockListeNotes();

private:

    Q_OBJECT

    //
    void createToolbar();
    void createStatusBar();
    void createDockWindows();

    // Attributs pour l'affichage dans les docks
    QListWidget* listeNotes;

    // Docks
    QDockWidget* dockListeNotes;

    NotesManager& notesManager = NotesManager::getManager();

signals :
    public slots :


};

#endif // VUEPRINCIPALE_H
