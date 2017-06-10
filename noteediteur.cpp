/*#include "mainwindow.h"
#include "noteediteur.h"

NoteEditeur::NoteEditeur(Note* n, QWidget* parent){
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
*/
