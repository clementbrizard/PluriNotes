#ifndef VUESECONDAIRE_H
#define VUESECONDAIRE_H

#include "qt_include.h"
#include "notes.h"
//#include "couples.h"
// Vue secondaire de l'appli (deuxieme onglet)
class VueSecondaire : public QMainWindow {
public:
    VueSecondaire();
    ///Affichage de l'editeur de relation
void CouplesEditeur();
///Creation dock relations
void createCouplesDock();
///Charge le fichier XML
void choixFichier();
///Ajouter les couples dans le dock couple
void remplirCouplesDock();
///Actualiser le dock de couples
void updateDockCouples();
private:

    Q_OBJECT

    // Attributs affichage relation editeur
   QWidget* centralContainer;
    QGridLayout *layout;
      QListWidget* listeNotesLeft;
      QListWidget* listeNotesRight;
      QVBoxLayout* layer;
      QScrollArea* scroller;
      QPushButton* addCouple;
      QPushButton* addNotOrientedCouple;
QListWidget* listeCouples;
    // Docks
      QDockWidget* dockListeCouples;
   // QDockWidget* dockRelation;
    //RelationsManager& relationsManager = RelationsManager::getManager();
    NotesManager& notesManager = NotesManager::getManager();

signals :
    public slots :
        ///Ajoute un Couple orienté
        void addOrientedCouple();
        ///Ajoute un couple non orienté
        void addCoupleNotOriented();

};


#endif // VUESECONDAIRE_H
