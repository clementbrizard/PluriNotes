#include "articleediteur.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QListWidget>
#include <QFileDialog>
#include "plurinotes.h"
/* Affichage de la page d'accueil qui affiche les différents notes*/
Accueil::Accueil()
{

    layout = new QVBoxLayout();
    QString filename = QFileDialog::getOpenFileName();

    NotesManager& m = NotesManager::getManager();
    m.setFilename(filename);
    m.load();
    setFixedSize(300, 300);
    //On affiche les titres de tous les articles disponibles
    for(NotesManager::Iterator it=m.getIterator(); !it.isDone(); it.next()){
    new QListWidgetItem((it.current()).getTitle(), listWidget);
    }

    titre1 = new QLabel("Liste des notes", this);
    edit = new QPushButton("Editer",this);





layout->addWidget(titre1);
layout->addWidget(listWidget);

    layout->addWidget(edit);

    //QObject::connect(edit,SIGNAL(clicked()),this,SLOT(article_edit(currentItem())));
    setLayout(layout);
}
ArticleEditeur::ArticleEditeur(Article& a) : article(a)
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
next = new QPushButton ("next",this);
    setFixedSize(800, 800);

    id->setText(a.getId());
    id->setEnabled(false);
    date_c->setEnabled(false);
    date_m->setEnabled(false);
    titre->setText(a.getTitle());
    text->setText(a.getText());
    save->setEnabled(false);


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

    QObject::connect(save, SIGNAL(clicked()), this, SLOT(handleSave()));
    QObject::connect(titre, SIGNAL(textChanged(QString)), this, SLOT(handleChange(QString)));
    QObject::connect(text, SIGNAL(textChanged(QString)), this, SLOT(handleChange(QString)));
    setLayout(layout);
}

void ArticleEditeur::handleSave(){
    article.setTitle(text->toPlainText());
    article.setText(text->toPlainText());

    NotesManager::getManager().save();

    QMessageBox msgBox(QMessageBox::Icon::Information, "Sauvegarde", "Le document a été sauvegardé.");
    msgBox.exec();
    save->setEnabled(false);

}

void ArticleEditeur::handleChange(QString s){
    save->setEnabled(true);
}

ArticleEditeur::~ArticleEditeur()
{

}
Accueil::~Accueil()
{

}
/*void Accueil::article_edit(Article& a){
    //ArticleEditeur::ArticleEditeur(a);

}*/
