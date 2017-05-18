#include<iostream>
#include"plurinotes.h"
using namespace std;

//Méthode de manager

template<class T>
T* Manager::uniqueInstance = nullptr;

template <class T>
T& Manager::giveInstance(){
    if(uniqueInstance == nullptr)
        uniqueInstance=new Manager();
    return *uniqueInstance;
}

void Manager::freeInstance(){
    if(uniqueInstance == nullptr)
        delete uniqueInstance;
    uniqueInstance=nullptr;
}

template <class T>
T& Manager::getNote(const int& id){
    for(unsigned int i=0; i<m_nb; i++)
        if(m_notes[i]->getId()==id) return *notes[i]
    throw NotesException("error, non existent note");
}

template <class T>
T& Manager::getNewNote(const int& id){
    T* t=new T(id,"",0, 0, "active");
	addNote(t);
	return *t;
}

Manager::~Manager(){
    if (m_fileName!="") save();
    for(unsigned int i=0; i<m_nb; i++) delete notes[i];
    delete[] notes;
}

void Manager::save() const {
    QFile newfile(filename);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw NotesException(QString("erreur sauvegarde notes : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("notes");
    for(unsigned int i=0; i<nbArticles; i++){
        stream.writeStartElement("article");
        stream.writeTextElement("id",articles[i]->getId());
        stream.writeTextElement("title",articles[i]->getTitle());
        stream.writeTextElement("text",articles[i]->getText());
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}

void Manager::load() {
    QFile fin(filename);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw NotesException("Erreur ouverture fichier notes");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    //qDebug()<<"debut fichier\n";
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            // If it's named taches, we'll go to the next.
            if(xml.name() == "notes") continue;
            // If it's named tache, we'll dig the information from there.
            if(xml.name() == "article") {
                qDebug()<<"new article\n";
                QString identificateur;
                QString titre;
                QString text;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "article")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); identificateur=xml.text().toString();
                            qDebug()<<"id="<<identificateur<<"\n";
                        }

                        // We've found titre.
                        if(xml.name() == "title") {
                            xml.readNext(); titre=xml.text().toString();
                            qDebug()<<"titre="<<titre<<"\n";
                        }
                        // We've found text
                        if(xml.name() == "text") {
                            xml.readNext();
                            text=xml.text().toString();
                            qDebug()<<"text="<<text<<"\n";
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                qDebug()<<"ajout note "<<identificateur<<"\n";
                addArticle(identificateur,titre,text);
            }
        }
    }
    // Error handling.
    if(xml.hasError()) {
        throw NotesException("Erreur lecteur fichier notes, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load\n";
}

void Article::show(){
    cout << "Id : " << getId() << "\n";
    cout << "Titre : " << getTitle() << "\n";
    cout << "Contenu : " << m_text << "\n";
}

void Task::show(){
    cout << "Id : " << getId() << "\n";
    cout << "Titre: " << getTitle() << "\n";
    if (m_priority != 0) cout << "Priorité :" << m_priority;
    //if(m_deadline != Date(0,0,0)) cout << "Deadline : "<<m_deadline; reféfinir l'opérateur différent pour la classe Date
}

void Media::show(){
    cout << "Id : " << getId() << "\n";
    cout << "Titre: " << getTitle() << "\n";
    cout << "Description: " << m_description << "\n";
    cout << "Titre: " << m_imageFileName << "\n";
}
