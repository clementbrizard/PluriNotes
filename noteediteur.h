/*#ifndef NOTEEDITEUR_H
#define NOTEEDITEUR_H

#include "qt_include.h"

class NoteEditeur : public QWidget {
    Q_OBJECT
    friend class NotesManager;
public:
    NoteEditeur(Note& n);
    ~NoteEditeur();

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
    //void handleSave();
    //void handleChange(QString);
};

#endif // NOTEEDITEUR_H
*/
