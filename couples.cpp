#include "couples.h"

using namespace std;

/******************COUPLE************************/

Couple::Couple(Note& referencingNote, Note& referencedNote, const QString &id, const QString& relation):
    m_id(id),m_referencingNote(referencingNote),m_referencedNote(referencedNote),m_relation(relation)
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

void Couple::setRelation(const QString& relation){
    m_relation=relation;
}

/*************COUPLESMANAGER************/

CouplesManager::CouplesManager():m_couples(nullptr),m_nbCouples(0),m_nbMaxCouples(0),m_filename("Relations.dat"){}

CouplesManager::~CouplesManager(){
    //save();
    for(int i=0; i<m_nbCouples; i++) delete m_couples[i];
    delete[] m_couples;
}

CouplesManager::Handler CouplesManager::handler=Handler();

CouplesManager& CouplesManager::getManager(){
    if (!handler.instance) handler.instance=new CouplesManager;
    return *handler.instance;
}

void CouplesManager::freeManager(){
    delete handler.instance;
    handler.instance=nullptr;
}

void CouplesManager::setNbMaxCouples(const int& nbMaxCouples){
    m_nbMaxCouples=nbMaxCouples;
}

void CouplesManager::setNbCouples(const int& nbCouples){
    m_nbCouples = nbCouples;
}

void CouplesManager:: removeCouplesWithThisNote(Note* n){
    for (Iterator it=getIterator(); !it.isDone(); it.next())
        if(it.current().getReferencingNote().getId()==n->getId() || it.current().getReferencedNote().getId()==n->getId()) removeCouple(it.current().getId());
}

void CouplesManager::removeCouple(const QString& idCouple){
    int i=0;
    for (Iterator it=getIterator(); !it.isDone(); it.next()){
        if(it.current().getId()==idCouple)
            m_couples[i]=m_couples[--m_nbCouples];
        i++;
    }
}

void CouplesManager::addCouple(Note& referencingNote,Note& referencedNote,const QString& id,const QString& relation){

    if (m_nbCouples==m_nbMaxCouples){
        Couple** newM_couples= new Couple*[m_nbMaxCouples+5];
        for(int i=0; i<m_nbCouples; i++) newM_couples[i]=m_couples[i];
        Couple** oldM_couples=m_couples;
        m_couples=newM_couples;
        m_nbMaxCouples+=5;
        if (oldM_couples) delete[] oldM_couples;
    }

    Couple* c=new Couple(referencingNote,referencedNote,id,relation);
    QString s = QString::number(m_nbCouples);
    c->setId(s);
    m_couples[m_nbCouples++]=c;
 }

void CouplesManager::save() const {
     QFile newfile(m_filename);
     if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
         throw Exception(QString("erreur sauvegarde couples : ouverture fichier xml"));
     QXmlStreamWriter stream(&newfile);
     stream.setAutoFormatting(true);
     stream.writeStartDocument();
     stream.writeStartElement("couples");
     for(CouplesManager::Iterator it=getIterator(); !it.isDone(); it.next()){
         stream.writeStartElement("couple");
         stream.writeTextElement("id",it.current().getId());
         stream.writeTextElement("referencingNote",it.current().getReferencingNote().getId());
         stream.writeTextElement("referencingNote",it.current().getReferencingNote().getId());
         stream.writeTextElement("relation",it.current().getRelation());
         stream.writeEndElement();
     }
     stream.writeEndElement();
     stream.writeEndDocument();
     newfile.close();
}

void CouplesManager::load() {
     QFile fin(m_filename);
     // If we can't open it, let's show an error message.
     if (!fin.open(QIODevice::ReadOnly | QIODevice::Text))
     {
         QMessageBox msgBox(QMessageBox::Icon::Information, "Info", "Abandon de l'ouverture du fichier de couples.");
         msgBox.exec();

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
             // If it's named couples, we'll go to the next.
             if(xml.name() == "couples") continue;
             // If it's named couple, we'll dig the information from there.
             if(xml.name() == "couple")
              { // début de si on a trouvé un couple
                 qDebug()<<"new couple\n";
                 QString identificateur;
                 QString relation;
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

                         if(xml.name() == "relation") {
                              xml.readNext(); relation=xml.text().toString();
                              qDebug()<<"relation="<<relation<<"\n";
                          }

                     } // fin de si on a trouvé un élément de couple
                     xml.readNext();
                 } // fin de tant que on n'est pas à la fin du couple
                 qDebug()<<"ajout couple "<<identificateur<<"\n";
                 addCouple(*(nm.getNoteById(referencingNote)),*(nm.getNoteById(referencedNote)),identificateur,relation);
             } // fin de si on a trouvé un couple

         }// fin de si on a trouvé une balise de début
     } // fin de tant que on n'est pas à la fin du doc

     // Error handling.
     if(xml.hasError()) {
         QMessageBox msgBox(QMessageBox::Icon::Information, "Info", "Abandon de l'ouverture du fichier de couples.");
         msgBox.exec();
     }
     // Removes any device() or data from the reader * and resets its internal state to the initial state.
     //xml.clear();
     qDebug()<<"fin load\n";
 }
