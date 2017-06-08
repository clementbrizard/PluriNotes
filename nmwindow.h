#ifndef NMWINDOW_H
#define NMWINDOW_H
#include <QDockWidget>
#include <QWidget>
#include <QListWidget>

class NotesManagerWindow : public QDockWidget {
    Q_OBJECT
private:
    QListWidget* listNotes;
public:
    NotesManagerWindow(QString title, QWidget* parent = 0);
signals :
    public slots :
     //*  void afficherNote();
};

#endif // NMWINDOW_H
