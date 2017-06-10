#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qt_include.h"
#include "nmwindow.h"
#include "noteediteur.h"

// Vue principale de l'application
class MainWindow : public QMainWindow {

private:
    Q_OBJECT

    QWidget* centralArea;
    QGridLayout* centralLayout;
    //NoteEditeur* mainEditeur;
    //RelationEditeur* mainRelationEditor;
    //CorbeilleEditeur *myDustbin;
    QWidget* pageEdition;
    QVBoxLayout* layerEdition;
    NotesManagerWindow* dockNotesManager;
    //relationsmanagerwindow* dockRelationsManager;
    //ArchivesManagerWindow* dockArchivesManager;


    MainWindow();
    struct MWHandler{
        MainWindow* instance;
        MWHandler() : instance(0){}
        ~MWHandler(){if(instance) delete instance; instance = 0;}
    };
    static MWHandler mw_handler;
public:
    static MainWindow& getInstance();
    static void libererInstance();
    //void showEditeur(NoteEditeur* ne);
    //NoteEditeur* getEditeur(){return mainEditeur;}
    //void setEditeur(NoteEditeur* ne){mainEditeur = ne;}



signals :
    public slots :
       void showNotesManager();
       void QuitApplication();
       void LoadData();
       void updateNotes();
       /*void showArchivesManager();
       void updateNotesManager();
       void newArticle();
       void newTask();
       void newAudio();
       void newImage();
       void newVideo();
       void showDustbin();


       void QuitWithoutSaving();
       void showRelationsManager();
       void showRelationsManagerActive();*/
       //NoteEditeur* getNewEditeur(Note* n, QString& type);
};
/*class Accueil : public QWidget
{
    Q_OBJECT
public:
    Accueil();
    ~Accueil();

private:

    QVBoxLayout* layout1;
    QVBoxLayout* layout2;
    QHBoxLayout* Hlayout;
    QLabel* titre1;
    QLabel* titre2;

QPushButton* edit;

    QListWidget *listNotes = new QListWidget(this);
    QPushButton* newArticle;
    QPushButton* newImage;
        QPushButton* viewRelation;
        QPushButton* quit;
   // QListWidget *getListNotes(){return listNotes;}
public slots:
    //void ArticleEdit();
    //void article_edit(Article& a);
    void afficherNote(QListWidgetItem* selected){
        selected->text();

    }


};*/

class ArticleEditeur : public QWidget
{
    Q_OBJECT
public:
    ArticleEditeur(Article& a);
    ~ArticleEditeur();


private:
    Article& article;
    QVBoxLayout* layout;

    QLabel* id1;
    QLabel* titre1;
    QLabel *date_c1;
     QLabel *date_m1;
    QLabel* text1;

    QLineEdit* id;
    QLineEdit* titre;
    QLineEdit *date_c;
    QLineEdit *date_m;
    QTextEdit* text;

    QPushButton* save;
    QPushButton* next;

signals:

private slots:
    void handleSave();
    void handleChange(QString);
};

#endif // MAINWINDOW_H
