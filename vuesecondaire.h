#ifndef VUESECONDAIRE_H
#define VUESECONDAIRE_H

#include "qt_include.h"
#include "notes.h"

// Vue secondaire de l'appli (deuxieme onglet)
class VueSecondaire : public QMainWindow {
public:
    VueSecondaire();
    //Affichage de l'editeur de relation
void RelationEditeur();
//Creation dock relations
void createRelationDock();
private:

    Q_OBJECT

    // Attributs affichage relation editeur
   QWidget* centralContainer;
    QGridLayout *layout;
      QListWidget* listeNotesLeft;
      QListWidget* listeNotesRight;
      QVBoxLayout* layer;
      QScrollArea* scroller;
      QPushButton* add;
      QPushButton* addNotOriented;
      QPushButton* quit;
QListWidget* listeRelations;
    // Docks
      QDockWidget* dockListeRelations;
   // QDockWidget* dockRelation;

    NotesManager& notesManager = NotesManager::getManager();

signals :
    public slots :

};


#endif // VUESECONDAIRE_H
