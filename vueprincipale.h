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

private:

    Q_OBJECT

    //
    void createToolbar();
    void createStatusBar();
    void createDockWindows();

    // Attributs pour l'affichage dans les docks
    QListWidget* listeNotes;


    NotesManager& notesManager = NotesManager::getManager();

signals :
    public slots :


};

#endif // VUEPRINCIPALE_H
