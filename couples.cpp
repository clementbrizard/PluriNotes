/*#include "relations.h"

using namespace std;*/

/******************COUPLE************************/

/*Couple::Couple(Note& referencingNote, Note& referencedNote, const QString &id, const QString& label):
    m_id(id),m_referencingNote(referencingNote),m_referencedNote(referencedNote),m_label(label)
{}

void Couple::setId(const QString &id){
    m_id=id;
}

void Couple::setReferencingNote(const Note& referencingNote){
    m_referencingNote=referencingNote;
 }

void Couple::setReferencedNote(const Note& referencedNote){
    m_referencedNote=referencedNote;
}

void Couple::setLabel(const QString& label){
    m_label=label;
}*/

/*****************RELATION************************/
/*
Relation::Relation(const QString& title, const QString& description, Couple** couples, const int& nbCouples, const int& nbMaxCouples, const QString &id, bool isOriented):
    m_id(id),m_title(title),m_description(description),m_couples(couples), m_nbCouples(nbCouples), m_nbMaxCouples(nbMaxCouples),m_isOriented(isOriented)
{}

void Relation::setId(const QString& id){
    m_id=id;
}

void Relation::setNbCouples(const int& nbCouples){
    m_nbCouples = nbCouples;
}

void Relation::setNbMaxCouples(const int& nbMaxCouples){
    m_nbMaxCouples=nbMaxCouples;
}

void Relation::setTitle(const QString& title){
    m_title=title;
}

void Relation::setDescription (const QString& description){
    m_description=description;
}

void Relation::addCouple(Note& referencingNote, Note& referencedNote, const QString &id, const QString& label){

    if (m_nbCouples==m_nbMaxCouples){
        Couple** newM_couples= new Couple*[m_nbMaxCouples+5];
        for(int i=0; i<m_nbCouples; i++) newM_couples[i]=m_couples[i];
        Couple** oldM_couples=m_couples;
        m_couples=newM_couples;
        m_nbMaxCouples+=5;
        if (oldM_couples) delete[] oldM_couples;
    }

    Couple* c=new Couple(referencingNote,referencedNote,id,label);
    QString s = QString::number(m_nbCouples);
    c->setId(s);
    m_couples[m_nbCouples++]=c;
}

void Relation::removeCouple(const QString &id){
    int i=0;

    while(i<m_nbCouples && m_couples[i]->getId()!=id) i++;
    if (i==m_nbCouples) throw Exception("erreur : Couple inexistant");

    delete m_couples[i];
    m_couples[i]=m_couples[--m_nbCouples];
}

void Relation::removeNote(Note *n){
    for (Iterator it=getIterator(); !it.isDone(); it.next())
        if(it.current().getReferencingNote().getId()==n->getId() || it.current().getReferencedNote().getId()==n->getId()) removeCouple(it.current().getId());
}
*/

/*************RELATIONSMANAGER************/
/*
RelationsManager::RelationsManager():m_relations(nullptr),m_nbRelations(0),m_nbMaxRelations(0),m_filename("Relations.dat"){}

RelationsManager::~RelationsManager(){
    //save();
    for(int i=0; i<m_nbRelations; i++) delete m_relations[i];
    delete[] m_relations;
}

RelationsManager::Handler RelationsManager::handler=Handler();

RelationsManager& RelationsManager::getManager(){
    if (!handler.instance) handler.instance=new RelationsManager;
    return *handler.instance;
}

void RelationsManager::freeManager(){
    delete handler.instance;
    handler.instance=nullptr;
}

void RelationsManager::addRelation(const QString& title, const QString& description, Couple** couples, const int& nbCouples, const int& nbMaxCouples, const QString &id, bool isOriented){
    for(int i=0; i<m_nbRelations; i++){
        if (m_relations[i]->getTitle()==title) throw Exception("error, creation of an already existent Relation");
    } // à réécrire avec l'itérateur
    if (m_nbRelations==m_nbMaxRelations){
        Relation** newM_relations= new Relation*[m_nbMaxRelations+5];
        for(int i=0; i<m_nbRelations; i++) newM_relations[i]=m_relations[i];
        Relation** oldM_relations=m_relations;
        m_relations=newM_relations;
        m_nbMaxRelations+=5;
        if (oldM_relations) delete[] oldM_relations;
    }
    Relation* r=new Relation(title,description,couples,nbCouples,nbMaxCouples,id,isOriented);
    QString s = QString::number(m_nbRelations);
    r->setId(s);
    m_relations[m_nbRelations++]=r;
}

void RelationsManager::addCouple(const QString& idRelation, Note& note1, Note& note2, const QString& id, const QString label){
    Iterator it=getIterator();
    while(!it.isDone() && it.current().getId()!=idRelation) it.next();
    if(it.isDone()) throw Exception("La relation à laquelle vous voulez ajouter un couple n'existe pas encore");
    else{
        it.current().addCouple(note1,note2,id,label);
        if(!it.current().getIsOriented())
             it.current().addCouple(note2,note1,id,label);
    }
}


void RelationsManager::removeRelation(Relation *r){
    int i=0;
    while(i<m_nbRelations && m_relations[i]->getId()!=r->getId()) i++;
    if (i==m_nbRelations) throw Exception("erreur : Relation à suppprimer inexistante");

    delete m_relations[i];
    m_relations[i]=m_relations[--m_nbRelations];
}

void RelationsManager::removeNote(Note* n){
    for(Iterator it=getIterator(); !it.isDone(); it.next())
        it.current().removeNote(n);
}

//void RelationsManager::save() const {}

void RelationsManager::load() {
    QFile fin(m_filename);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        throw Exception("Erreur ouverture fichier notes");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    qDebug()<<"debut fichier de relations\n";
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError())
    {   //début de tant que on n'est pas à la fin du doc
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement)
        { // début de si on a trouvé une balise de début
            // If it's named relations, we'll go to the next.
            if(xml.name() == "relations") continue;
            // If it's named relation, we'll dig the information from there.
            if(xml.name() == "relation")
            { //début de si on a trouvé une relation
                qDebug()<<"new relation\n";
                QString idRelation;
                QString title;
                QString description;
                QString tmp;
                int nbCouples;
                int nbMaxCouples;
                bool isOriented;
                QXmlStreamAttributes attributes = xml.attributes();
                NotesManager& nm=NotesManager::getManager();

                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named relaion.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "relation"))
                { // début de tant que on n'est pas à la fin de la relation
                    if(xml.tokenType() == QXmlStreamReader::StartElement)
                    { // début de si on a trouvé un élément de relation

                        if(xml.name() == "id") {
                            xml.readNext(); idRelation=xml.text().toString();
                            qDebug()<<"id="<<idRelation<<"\n";
                        }

                        if(xml.name() == "title") {
                            xml.readNext(); title=xml.text().toString();
                            qDebug()<<"title="<<title<<"\n";
                        }

                        if(xml.name() == "description") {
                            xml.readNext(); description=xml.text().toString();
                            qDebug()<<"description="<<description<<"\n";
                        }

                        if(xml.name() == "nbCouples") {
                            xml.readNext(); nbCouples=xml.text().toInt();
                            qDebug()<<"nbCouples="<<nbCouples<<"\n";
                        }

                        if(xml.name() == "nbMaxCouples") {
                            xml.readNext(); nbMaxCouples=xml.text().toInt();
                            qDebug()<<"nbCouples="<<nbMaxCouples<<"\n";
                        }

                        if(xml.name() == "isOriented") {
                           // conversion en booléen
                           xml.readNext(); tmp=xml.text().toString();
                           isOriented=(tmp=="1"?1:0);
                           qDebug()<<"isOriented="<<isOriented<<"\n";
                           addRelation(title,description,Q_NULLPTR,nbCouples,nbMaxCouples,idRelation,isOriented);
                        }

                        if(xml.name() == "couples"){xml.readNext(); continue;}
                        if(xml.name()=="couple")
                        { // début de si on a trouvé un couple
                            qDebug()<<"new couple\n";
                            QString identificateur;
                            QString label;
                            QString referencingNote;
                            QString referencedNote;
                            QXmlStreamAttributes attributes = xml.attributes();

                            NotesManager& nm=NotesManager::getManager();
                            xml.readNext();
                            //We're going to loop over the things because the order might change.
                            //We'll continue the loop until we hit an EndElement named couple.
                            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "couple"))
                            {// début de tant que on n'est pas à la fin d'un couple
                                if(xml.tokenType() == QXmlStreamReader::StartElement)
                                { // début de si on a trouvé un élément de couple

                                    if(xml.name() == "id") {
                                         xml.readNext(); identificateur=xml.text().toString();
                                         qDebug()<<"id="<<identificateur<<"\n";
                                     }

                                    if(xml.name() == "referencingNote") {
                                        xml.readNext(); referencingNote=xml.text().toString();
                                        qDebug()<<"referencingNote="<<referencingNote<<"\n";
                                    }

                                    if(xml.name() == "referencedNote") {
                                        xml.readNext(); referencedNote=xml.text().toString();
                                        qDebug()<<"referencedNote="<<referencedNote<<"\n";
                                    }

                                    if(xml.name() == "label") {
                                         xml.readNext(); label=xml.text().toString();
                                         qDebug()<<"label="<<label<<"\n";
                                     }

                                } // fin de si on a trouvé un élément de couple
                                xml.readNext();
                            } // fin de tant que on n'est pas à la fin du couple
                            qDebug()<<"ajout couple "<<identificateur<<"\n";
                            addCouple(idRelation,*(nm.getNoteById(referencingNote)),*(nm.getNoteById(referencedNote)),identificateur,label);
                        } // fin de si on a trouvé un couple
                    } // fin de si on a trouvé un élément de relation
                    xml.readNext();
                } // fin de tant que on n'est pas à la fin de relation
                qDebug()<<"ajout relation "<<idRelation<<"\n";
            }// fin de si on a trouvé une relation
        }// fin de si on a trouvé une baise de début
    } // fin de tant que on n'est pas à la fin du doc

    // Error handling.
    if(xml.hasError()) {
        throw Exception("Erreur lecteur fichier relations, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    //xml.clear();
    qDebug()<<"fin load\n";
}
*/

