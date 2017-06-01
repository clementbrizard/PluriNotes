#ifndef ARTICLEEDITEUR_H
#define ARTICLEEDITEUR_H

#include <QWidget>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QListWidget>
#include <QFileDialog>
#include "plurinotes.h"
class Accueil : public QWidget
{
    Q_OBJECT
public:
    Accueil();
    ~Accueil();

private:

    QVBoxLayout* layout;

    QLabel* titre1;

QPushButton* edit;
/*QPushButton* button2;
QPushButton* button3;
    QPushButton* save;
    QPushButton* quit;*/
    QListWidget *listWidget = new QListWidget(this);
public slots:
    //void article_edit(Article& a);



};

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

#endif // ARTICLEEDITEUR_H
