#include "mainwindow.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QListWidget>
#include <QFileDialog>
#include "notes.h"
#include "notefactory.h"

/*Article* ArticleFactory::createNewNote(QString &title){
    unsigned int id = getNewId();
    Article* article = new Article(QString::number(id),title,(QString)"");
    return article;
}*/
/*ArticleFactory::ArticleFactory()
{

    layout = new QVBoxLayout();
    id1 = new QLabel("Identificateur", this);
    titre1 = new QLabel("Titre", this);
    text1 = new QLabel("Texte", this);
    id = new QLineEdit(this);
    date_c1 = new QLabel("Date de création", this);
    date_c = new QLineEdit(this);
    date_m1 = new QLabel("Date de modification", this);
    date_m = new QLineEdit(this);
    titre = new QLineEdit(this);
    text = new QTextEdit(this);
    save = new QPushButton("Sauver", this);
//next = new QPushButton ("next",this);
    setFixedSize(800, 800);

    id->setEnabled(false);
    date_c->setEnabled(false);
    date_m->setEnabled(false);
    save->setEnabled(true);


    layout->addWidget(id1);
    layout->addWidget(id);
    layout->addWidget(titre1);
    layout->addWidget(titre);
    layout->addWidget(date_c1);
    layout->addWidget(date_c);
    layout->addWidget(date_m1);
    layout->addWidget(date_m);
    layout->addWidget(text1);
    layout->addWidget(text);
    layout->addWidget(next);
    layout->addWidget(save);

    QObject::connect(save, SIGNAL(clicked()), this, SLOT(handleCreateArticle()));
    QObject::connect(titre, SIGNAL(textChanged(QString)), this, SLOT(handleChange(QString)));
    QObject::connect(text, SIGNAL(textChanged(QString)), this, SLOT(handleChange(QString)));
    setLayout(layout);
}
void ArticleFactory::handleCreateArticle(){
    qDebug()<<"ajout Article "<<titre->text()<<"\n";
    //Article* a=new Article(titre->text(),text->toPlainText());
    //NotesManager::addNote(a);
    NotesManager& m= NotesManager::getManager();
    m.addArticle(titre->text(),text->toPlainText());
   // NotesManager::addArticle(titre->text(),text->toPlainText());

    QMessageBox msgBox(QMessageBox::Icon::Information, "Sauvegarde", "Le document a été sauvegardé.");
    msgBox.exec();

}*/
