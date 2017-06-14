#include "notes.h"


/*****************NOTESMANAGER*****************/

NotesManager::NotesManager():m_notes(nullptr),m_nbNotes(0),m_nbMaxNotes(0),m_filename("test.xml"){}

NotesManager::~NotesManager(){
    save();
    for(unsigned int i=0; i<m_nbNotes; i++) delete m_notes[i];
    delete[] m_notes;
}

NotesManager::Handler NotesManager::handler=Handler();

NotesManager& NotesManager::getManager(){
    if (!handler.instance) handler.instance=new NotesManager;
    return *handler.instance;
}

void NotesManager::freeManager(){
    delete handler.instance;
    handler.instance=nullptr;
}

Note* NotesManager::getNoteByTitle(QString title){
    for (unsigned int i=0; i<m_nbNotes; i++){
        if (title == m_notes[i]->getTitle()) return m_notes[i];
    }
    throw Exception ("Note non trouvee..");
}

Note* NotesManager::getNoteById(QString id){
    for (unsigned int i=0; i<m_nbNotes; i++){
        if (id == m_notes[i]->getId()) return m_notes[i];
    }
    throw Exception ("Note non trouvee..");
}

void NotesManager::addNote(Note* n){
    for(unsigned int i=0; i<m_nbNotes; i++){
        if (m_notes[i]->getId()==m_nbNotes) throw Exception("error, creation of an already existent note");
    }
    if (m_nbNotes==m_nbMaxNotes){
        Note** newM_notes= new Note*[m_nbMaxNotes+5];
        for(unsigned int i=0; i<m_nbNotes; i++) newM_notes[i]=m_notes[i];
        Note** oldM_notes=m_notes;
        m_notes=newM_notes;
        m_nbMaxNotes+=5;
        if (oldM_notes) delete[] oldM_notes;
    }
    QString s = QString::number(m_nbNotes);
    n->setId(s);

    m_notes[m_nbNotes++]=n;
}

void NotesManager::addLoadedNote(Note* n){
    for(unsigned int i=0; i<m_nbNotes; i++){
        if (m_notes[i]->getId()==n->getId()){
            QMessageBox::information(Q_NULLPTR,"Erreur","error, creation of an already existent note");
            return;
        }
    }
    if (m_nbNotes==m_nbMaxNotes){
        Note** newM_notes= new Note*[m_nbMaxNotes+5];
        for(unsigned int i=0; i<m_nbNotes; i++) newM_notes[i]=m_notes[i];
        Note** oldM_notes=m_notes;
        m_notes=newM_notes;
        m_nbMaxNotes+=5;
        if (oldM_notes) delete[] oldM_notes;
    }
    m_notes[m_nbNotes++]=n;
}

void NotesManager::addArticle(const QString& title, QString statut, const QString& text, const QString& id, const QDate &dateCreation, const QDate &dateLastModif, const int &nVersion, const bool &isVersionActuelle){
    for(unsigned int i=0; i<m_nbNotes; i++){
        if (m_notes[i]->getTitle()==title) throw Exception("Erreur : article déjà existant");
    }
    Article* a=new Article(title,statut,text,id,dateCreation,dateLastModif,nVersion,isVersionActuelle);
    addNote(a);
}

void NotesManager::addTask(const QString& title, QString statut,const QString& action,const QString& priority,const QDate& deadline, const QString& id,const QDate& dateCreation,const QDate& dateLastModif, const int &nVersion, const bool &isVersionActuelle){
    for(unsigned int i=0; i<m_nbNotes; i++){
        if (m_notes[i]->getTitle()==title) throw Exception("Erreur : task déjà existante");
    }
    Task* t=new Task(title,statut,action,priority,deadline,id,dateCreation,dateLastModif,nVersion,isVersionActuelle);
    addNote(t);
}

void NotesManager::addImage(const QString& title, QString statut, const QString& description, const QString& imageFileName,const QString& id,const QDate& dateCreation,const QDate& dateLastModif, const int &nVersion, const bool &isVersionActuelle){
    for(unsigned int i=0; i<m_nbNotes; i++){
        if (m_notes[i]->getTitle()==title) throw Exception("Erreur : Image deja existante");
    }
    Image* i=new Image(title,statut,description,imageFileName,id,dateCreation,dateLastModif,nVersion,isVersionActuelle);
    addNote(i);
}

void NotesManager::addAudio(const QString& title, QString statut, const QString& description, const QString& imageFileName,const QString& id, const QDate& dateCreation, const QDate &dateLastModif, const int &nVersion, const bool &isVersionActuelle){
    for(unsigned int i=0; i<m_nbNotes; i++){
        if (m_notes[i]->getTitle()==title) throw Exception("Erreur : Image deja existante");
    }
    Audio* au=new Audio(title,statut,description,imageFileName,id,dateCreation,dateLastModif,nVersion,isVersionActuelle);
    addNote(au);
}

void NotesManager::addVideo(const QString& title, QString statut, const QString& description, const QString& imageFileName, const QString& id, const QDate &dateCreation, const QDate &dateLastModif, const int &nVersion, const bool &isVersionActuelle){
    for(unsigned int i=0; i<m_nbNotes; i++){
        if (m_notes[i]->getTitle()==title) throw Exception("Erreur : Video deja existante");
    }
    Video* vi=new Video(title,statut,description,imageFileName,id,dateCreation,dateLastModif,nVersion,isVersionActuelle);
    addNote(vi);
}

void NotesManager::removeNote(Note *n){
    int i=0;
    Iterator it = getIterator();
    while(!it.isDone() && it.current().getId()!=n->getId()){
        it.next();
        i++;
    }

    if(it.current().getId()==n->getId()){
        m_notes[i]=m_notes[--m_nbNotes];
    }
    else throw Exception("Note a supprimer non trouvee");
}

void NotesManager::save() const {
    QFile newfile(m_filename);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw Exception(QString("erreur sauvegarde notes : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("notes");
    for(NotesManager::Iterator it=getIterator(); !it.isDone(); it.next()){
        (it.current()).save(stream);
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}

void NotesManager::load() {
    QFile fin(m_filename);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox msgBox(QMessageBox::Icon::Information, "Info", "Abandon de l'ouverture fichier notes.");
        msgBox.exec();
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    qDebug()<<"debut fichier de notes\n";
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            // If it's named notes, we'll go to the next.
            if(xml.name() == "notes") continue;
            // If it's named article, we'll dig the information from there.
            if(xml.name() == "article") { loadArticle(xml); }
            if(xml.name() == "audio") { loadAudio(xml); }
            if(xml.name() == "image") { loadImage(xml); }
            if(xml.name() == "video") { loadVideo(xml); }
            if(xml.name() == "task") { loadTask(xml); }
        }
    }
    // Error handling.
    if(xml.hasError()) {
        QMessageBox msgBox(QMessageBox::Icon::Information, "Info", "Abandon de l'ouverture du fichier notes.");
        msgBox.exec();
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    //xml.clear();
    qDebug()<<"fin load\n";
}

QXmlStreamReader& NotesManager::loadArticle(QXmlStreamReader& xml){
    qDebug()<<"new article\n";
    QString identificateur;
    QString titre;
    QString text;
    QString temp;
    QDate dateCreation;
    QDate dateLastModif;
    QString statut;
    int nVersion;
    bool isVersionActuelle;
    QXmlStreamAttributes attributes = xml.attributes();
    xml.readNext();
    //We're going to loop over the things because the order might change.
    //We'll continue the loop until we hit an EndElement named article.
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "article")) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {
            // We've found identificateur.
            if(xml.name() == "id") {
                xml.readNext(); identificateur=xml.text().toString();
                qDebug()<<"id="<<identificateur<<"\n";
            }

            // We've found statut.
            if(xml.name() == "statut") {
                xml.readNext(); statut=xml.text().toString();
                qDebug()<<"statut="<<statut<<"\n";
            }
            // We've found nVersion.
            if(xml.name() == "nVersion") {
                xml.readNext(); temp=xml.text().toString();
                nVersion=temp.toInt();
                qDebug()<<"nVersion="<<nVersion<<"\n";
            }
            // We've found isVersionActuelle.
            if(xml.name() == "isVersionActuelle") {
                xml.readNext(); temp=xml.text().toString();
                isVersionActuelle=(temp=="1" ? true : false);
                qDebug()<<"isVersionActuelle="<<isVersionActuelle<<"\n";
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

            //We've found dateCreation
            if(xml.name() == "dateCreation"){
                xml.readNext();
                temp = xml.text().toString();
                //Conversion d'une Qstring en QDate depuis le format dd-MM-yyyy
                dateCreation = QDate::fromString(temp,"dd-MM-yyyy");
                qDebug()<<"creation="<<dateCreation<<"\n";
            }

            //We've found dateLastModif
            if(xml.name() == "dateLastModif"){
                xml.readNext();
                temp = xml.text().toString();
                //Conversion d'une Qstring en QDate depuis le format dd-MM-yyyy
                 dateLastModif= QDate::fromString(temp,"dd-MM-yyyy");
                qDebug()<<"date="<<dateLastModif<<"\n";
            }

        }
        // ...and next...
        xml.readNext();
    }
    qDebug()<<"ajout Article "<<identificateur<<"\n";
    Article* a=new Article(titre,statut,text,identificateur,dateCreation,dateLastModif,nVersion,isVersionActuelle);
    addLoadedNote(a);
    return xml;
}

QXmlStreamReader& NotesManager::loadImage(QXmlStreamReader& xml){
    qDebug()<<"new image\n";
    QString identificateur;
    QString titre;
    QString description;
    QString imageFileName;
    QString temp;
    QDate dateCreation;
    QDate dateLastModif;
    QString statut;
    int nVersion;
    bool isVersionActuelle;
    QXmlStreamAttributes attributes = xml.attributes();
    xml.readNext();
    //We're going to loop over the things because the order might change.
    //We'll continue the loop until we hit an EndElement named article.
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "image")) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {
            // We've found identificateur.
            if(xml.name() == "id") {
                xml.readNext(); identificateur=xml.text().toString();
                qDebug()<<"id="<<identificateur<<"\n";
            }

            // We've found statut.
            if(xml.name() == "statut") {
                xml.readNext(); statut=xml.text().toString();
                qDebug()<<"statut="<<statut<<"\n";
            }
            // We've found nVersion.
            if(xml.name() == "nVersion") {
                xml.readNext(); temp=xml.text().toString();
                nVersion=temp.toInt();
                qDebug()<<"nVersion="<<nVersion<<"\n";
            }
            // We've found isVersionActuelle.
            if(xml.name() == "isVersionActuelle") {
                xml.readNext(); temp=xml.text().toString();
                isVersionActuelle=(temp=="1" ? true : false);
                qDebug()<<"isVersionActuelle="<<isVersionActuelle<<"\n";
            }
            // We've found titre.
            if(xml.name() == "title") {
                xml.readNext(); titre=xml.text().toString();
                qDebug()<<"titre="<<titre<<"\n";
            }

            // We've found description
            if(xml.name() == "description") {
                xml.readNext();
                description=xml.text().toString();
                qDebug()<<"description="<<description<<"\n";
            }

            // We've found imageFileName
            if(xml.name() == "imageFileName") {
                xml.readNext();
                imageFileName=xml.text().toString();
                qDebug()<<"imageFileName="<<imageFileName<<"\n";
            }

            //We've found dateCreation
            if(xml.name() == "dateCreation"){
                xml.readNext();
                temp = xml.text().toString();
                //Conversion d'une Qstring en QDate depuis le format dd-MM-yyyy
                dateCreation = QDate::fromString(temp,"dd-MM-yyyy");
                qDebug()<<"creation="<<dateCreation<<"\n";
            }

            //We've found dateLastModif
            if(xml.name() == "dateLastModif"){
                xml.readNext();
                temp = xml.text().toString();
                //Conversion d'une Qstring en QDate depuis le format dd-MM-yyyy
                 dateLastModif= QDate::fromString(temp,"dd-MM-yyyy");
                qDebug()<<"date="<<dateLastModif<<"\n";
            }

        }
        // ...and next...
        xml.readNext();
    }
    qDebug()<<"ajout Image "<<identificateur<<"\n";
    Image* i=new Image(titre,statut,description,imageFileName,identificateur,dateCreation,dateLastModif,nVersion,isVersionActuelle);
    addLoadedNote(i);
    return xml;
}

QXmlStreamReader& NotesManager::loadAudio(QXmlStreamReader& xml){
    qDebug()<<"new audio\n";
    QString identificateur;
    QString titre;
    QString description;
    QString imageFileName;
    QString temp;
    QDate dateCreation;
    QDate dateLastModif;
    QString statut;
    int nVersion;
    bool isVersionActuelle;
    QXmlStreamAttributes attributes = xml.attributes();
    xml.readNext();
    //We're going to loop over the things because the order might change.
    //We'll continue the loop until we hit an EndElement named article.
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "audio")) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {
            // We've found identificateur.
            if(xml.name() == "id") {
                xml.readNext(); identificateur=xml.text().toString();
                qDebug()<<"id="<<identificateur<<"\n";
            }

            // We've found statut.
            if(xml.name() == "statut") {
                xml.readNext(); statut=xml.text().toString();
                qDebug()<<"statut="<<statut<<"\n";
            }
            // We've found nVersion.
            if(xml.name() == "nVersion") {
                xml.readNext(); temp=xml.text().toString();
                nVersion=temp.toInt();
                qDebug()<<"nVersion="<<nVersion<<"\n";
            }
            // We've found isVersionActuelle.
            if(xml.name() == "isVersionActuelle") {
                xml.readNext(); temp=xml.text().toString();
                isVersionActuelle=(temp=="1" ? true : false);
                qDebug()<<"isVersionActuelle="<<isVersionActuelle<<"\n";
            }
            // We've found titre.
            if(xml.name() == "title") {
                xml.readNext(); titre=xml.text().toString();
                qDebug()<<"titre="<<titre<<"\n";
            }

            // We've found description
            if(xml.name() == "description") {
                xml.readNext();
                description=xml.text().toString();
                qDebug()<<"description="<<description<<"\n";
            }

            // We've found imageFileName
            if(xml.name() == "imageFileName") {
                xml.readNext();
                imageFileName=xml.text().toString();
                qDebug()<<"imageFileName="<<imageFileName<<"\n";
            }

            //We've found dateCreation
            if(xml.name() == "dateCreation"){
                xml.readNext();
                temp = xml.text().toString();
                //Conversion d'une Qstring en QDate depuis le format dd-MM-yyyy
                dateCreation = QDate::fromString(temp,"dd-MM-yyyy");
                qDebug()<<"creation="<<dateCreation<<"\n";
            }

            //We've found dateLastModif
            if(xml.name() == "dateLastModif"){
                xml.readNext();
                temp = xml.text().toString();
                //Conversion d'une Qstring en QDate depuis le format dd-MM-yyyy
                 dateLastModif= QDate::fromString(temp,"dd-MM-yyyy");
                qDebug()<<"date="<<dateLastModif<<"\n";
            }


        }
        // ...and next...
        xml.readNext();
    }
    qDebug()<<"ajout Audio "<<identificateur<<"\n";
    Audio* i=new Audio(titre,statut,description,imageFileName,identificateur,dateCreation,dateLastModif,nVersion,isVersionActuelle);
    addLoadedNote(i);
    return xml;
}

QXmlStreamReader& NotesManager::loadVideo(QXmlStreamReader& xml){
    qDebug()<<"new video\n";
    QString identificateur;
    QString titre;
    QString description;
    QString imageFileName;
    QString temp;
    QDate dateCreation;
    QDate dateLastModif;
    QString statut;
    int nVersion;
    bool isVersionActuelle;
    QXmlStreamAttributes attributes = xml.attributes();
    xml.readNext();
    //We're going to loop over the things because the order might change.
    //We'll continue the loop until we hit an EndElement named article.
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "video")) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {
            // We've found identificateur.
            if(xml.name() == "id") {
                xml.readNext(); identificateur=xml.text().toString();
                qDebug()<<"id="<<identificateur<<"\n";
            }

            // We've found statut.
            if(xml.name() == "statut") {
                xml.readNext(); statut=xml.text().toString();
                qDebug()<<"statut="<<statut<<"\n";
            }
            // We've found nVersion.
            if(xml.name() == "nVersion") {
                xml.readNext(); temp=xml.text().toString();
                nVersion=temp.toInt();
                qDebug()<<"nVersion="<<nVersion<<"\n";
            }
            // We've found isVersionActuelle.
            if(xml.name() == "isVersionActuelle") {
                xml.readNext(); temp=xml.text().toString();
                isVersionActuelle=(temp=="1" ? true : false);
                qDebug()<<"isVersionActuelle="<<isVersionActuelle<<"\n";
            }
            // We've found titre.
            if(xml.name() == "title") {
                xml.readNext(); titre=xml.text().toString();
                qDebug()<<"titre="<<titre<<"\n";
            }

            // We've found description
            if(xml.name() == "description") {
                xml.readNext();
                description=xml.text().toString();
                qDebug()<<"description="<<description<<"\n";
            }

            // We've found imageFileName
            if(xml.name() == "imageFileName") {
                xml.readNext();
                imageFileName=xml.text().toString();
                qDebug()<<"imageFileName="<<imageFileName<<"\n";
            }

            //We've found dateCreation
            if(xml.name() == "dateCreation"){
                xml.readNext();
                temp = xml.text().toString();
                //Conversion d'une Qstring en QDate depuis le format dd-MM-yyyy
                dateCreation = QDate::fromString(temp,"dd-MM-yyyy");
                qDebug()<<"creation="<<dateCreation<<"\n";
            }

            //We've found dateLastModif
            if(xml.name() == "dateLastModif"){
                xml.readNext();
                temp = xml.text().toString();
                //Conversion d'une Qstring en QDate depuis le format dd-MM-yyyy
                 dateLastModif= QDate::fromString(temp,"dd-MM-yyyy");
                qDebug()<<"date="<<dateLastModif<<"\n";
            }

        }
        // ...and next...
        xml.readNext();
    }
    qDebug()<<"ajout video "<<identificateur<<"\n";
    Video* v=new Video(titre,statut,description,imageFileName,identificateur,dateCreation,dateLastModif,nVersion,isVersionActuelle);
    addLoadedNote(v);
    return xml;
}

QXmlStreamReader& NotesManager::loadTask(QXmlStreamReader& xml){
    qDebug()<<"new article\n";
    QString identificateur;
    QString titre;
    QString action;
    QString priority;
    QDate deadline;
    QString temp;
    QDate dateCreation;
    QDate dateLastModif;
    QString statut;
    int nVersion;
    bool isVersionActuelle;
    QXmlStreamAttributes attributes = xml.attributes();
    xml.readNext();
    //We're going to loop over the things because the order might change.
    //We'll continue the loop until we hit an EndElement named article.
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "task")) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {
            // We've found identificateur.
            if(xml.name() == "id") {
                xml.readNext(); identificateur=xml.text().toString();
                qDebug()<<"id="<<identificateur<<"\n";
            }

            // We've found statut.
            if(xml.name() == "statut") {
                xml.readNext(); statut=xml.text().toString();
                qDebug()<<"statut="<<statut<<"\n";
            }
            // We've found nVersion.
            if(xml.name() == "nVersion") {
                xml.readNext(); temp=xml.text().toString();
                nVersion=temp.toInt();
                qDebug()<<"nVersion="<<nVersion<<"\n";
            }
            // We've found isVersionActuelle.
            if(xml.name() == "isVersionActuelle") {
                xml.readNext(); temp=xml.text().toString();
                isVersionActuelle=(temp=="1" ? true : false);
                qDebug()<<"isVersionActuelle="<<isVersionActuelle<<"\n";
            }

            // We've found titre.
            if(xml.name() == "title") {
                xml.readNext(); titre=xml.text().toString();
                qDebug()<<"titre="<<titre<<"\n";
            }

            // We've found action
            if(xml.name() == "action") {
                xml.readNext();
                action=xml.text().toString();
                qDebug()<<"action="<<action<<"\n";
            }
            // We've found priority
            if(xml.name() == "priority") {
                xml.readNext();
                priority=xml.text().toString();
                qDebug()<<"priority="<<priority<<"\n";
            }
            //We've found deadline
            if(xml.name() == "deadline"){
                xml.readNext();
                temp = xml.text().toString();
                //Conversion d'une Qstring en QDate depuis le format dd-MM-yyyy
                deadline = QDate::fromString(temp,"dd-MM-yyyy");
                qDebug()<<"deadline="<<deadline<<"\n";
            }
            //We've found dateCreation
            if(xml.name() == "dateCreation"){
                xml.readNext();
                temp = xml.text().toString();
                //Conversion d'une Qstring en QDate depuis le format dd-MM-yyyy
                dateCreation = QDate::fromString(temp,"dd-MM-yyyy");
                qDebug()<<"creation="<<dateCreation<<"\n";
            }

            //We've found dateLastModif
            if(xml.name() == "dateLastModif"){
                xml.readNext();
                temp = xml.text().toString();
                //Conversion d'une Qstring en QDate depuis le format dd-MM-yyyy
                 dateLastModif= QDate::fromString(temp,"dd-MM-yyyy");
                qDebug()<<"date="<<dateLastModif<<"\n";
            }

        }
        // ...and next...
        xml.readNext();
    }
    qDebug()<<"ajout task "<<identificateur<<"\n";
    Task* t=new Task(titre,statut,action,priority,deadline,identificateur,dateCreation,dateLastModif,nVersion,isVersionActuelle);
    addLoadedNote(t);
    return xml;
}

/****************CORBEILLE**************************/

Corbeille::Corbeille(){}

///Destructeur de la corbeille
Corbeille::~Corbeille(){
    ///On vide bien toutes les notes présentes dans le vecteur de pointeur de notes dustBin
    for(unsigned int i=0; i<poubelle.size(); i++){ delete poubelle[i];}
    ///On libère le vecteur poubelle
    poubelle.clear();
}

Corbeille::HandlerC Corbeille::handlerC=HandlerC();


///Retourne l'instance unique de la courbeille, ou en crée une si il n'y en a pas
Corbeille& Corbeille::getInstance() {
  /// Si le pointeur vers l'instance unique pointe vers 0
  if(!handlerC.instance) {
    ///Création d'une nouvelle instance unique
    handlerC.instance = new Corbeille;
  }
  /// Retour par ref vers l'instance unique
  return *handlerC.instance;
}


/// Libérer l'instance
void Corbeille::libererInstance() {
  /// Liberation de la memoire allouee a l'instance unique
  delete handlerC.instance;
  /// Repasse le pointeur a null/nullptr/0 pour que le prochain appel a getInstance recree bien une instance
  handlerC.instance=0;
}


///Renvoie un pointeur sur une note en fonction de son id
Note* Corbeille::getNoteById(QString id){
    ///itération sur les notes de dustbin
    for(unsigned int i=0; i<poubelle.size();i++){
        ///Si l'id de la note correspond à l'id passé en argument, on renvoie un pointeur vers cette note
        if(poubelle[i]->getId() == id) {return poubelle[i];}
        ///sinon on lance une exception pour dire que la note n'a pas été trouvée.
        else {throw Exception("La note n'a pas ete trouvee..");}
    }
}


///Fonction permettant de renvoyer un pointeur vers une note en fonction du numéro de sa position
Note* Corbeille::getNoteByPosition(unsigned int position){
    if(position<poubelle.size()) {return poubelle[position];}
    ///Si la position passée en argument est supérieure à la taille du vecteur, on lance une exception
    else throw Exception ("La note n'a pas ete trouvee..");
}



/// Ajout d'une note via la fonction push_back de vector
void Corbeille::addNote(Note* n){
  poubelle.push_back(n);
}


///Fonction qui renvoie la position d'une note passée en argument
unsigned int Corbeille::getNotePosition(Note* n){
    ///itération sur les notes de dustbin
    for(unsigned int i=0;i<poubelle.size();i++){
        ///Si la note itérée correspond à la note apssée en argument, on renvoie un pointeur vers cette note itérée
        if(poubelle[i]==n){return i;}
    }
    ///sinon on lance une exception pour dire que la note n'a pas été trouvée.
    throw Exception("La note n'a pas ete trouvee..");
}


///fonction permettant de restaurer une note
void Corbeille::RestoreNote(Note* n){
    ///On récupère la position de la note dans le vecteur
    unsigned int i=getNotePosition(n);
    ///On ajoute la note dans notesmanager
    addNote(n);
    ///On supprime la note du vecteur de notes dustBin
    poubelle.erase(poubelle.begin()+i);
}


///Fonction permettant de retourner un pointeur vers une note ayant un titre identique à celui passé en paramètre
Note* Corbeille::getNoteByTitle(QString title){
    ///itération sur les notes de dustbin
    for(unsigned int i=0; i<poubelle.size(); i++){
        ///Si le titre de la note correspond au titre passé en argument, on renvoie un pointeur vers cette note
        if(poubelle[i]->getTitle()== title) return poubelle[i];
    }
    ///sinon on lance une exception pour dire que la note n'a pas été trouvée.
    throw Exception("La note n'a pas ete trouvee..");
}


///Fonction permettant de supprimer une note du vecteur de notes
void Corbeille::deleteNote(Note* n){
    ///On récupère sa position
    unsigned int i = Corbeille::getInstance().getNotePosition(n);
    ///Apple de l'instance unique de relationsmanager
   // RelationsManager& rm = RelationsManager::getInstance();
    ///Suppression de toutes les relations correspondant à cette note
   // rm.deleteRelationOfNote(*n);
    ///Suppression de la note du vecteur de notes
    poubelle.erase(poubelle.begin()+i);
    ///Suppression de la note de notesmanager
    NotesManager::getManager().removeNote(n);
}

/*****************NOTE**************************/

Note::Note(const QString& title, QString statut, const QString& id, const QDate &dateCreation, const QDate &dateLastModif, const int &nVersion, const bool &isVersionActuelle):
    m_id(id),m_title(title),m_statut(statut), m_dateCreation(dateCreation),m_dateLastModif(dateLastModif),m_nVersion(nVersion),m_isVersionActuelle(isVersionActuelle)
{}

void Note::setId(const QString &id){
    m_id=id;
}

void Note::setTitle(const QString &title) {
    m_title=title;
}

void Note::setDateLastModif(QDate dateLastModif){
    m_dateLastModif=dateLastModif;
}

 void Note::setStatut(QString statut){
     m_statut=statut;
 }
 void Note::setNVersion(int nVersion){
     m_nVersion=nVersion;
 }

 void Note::setIsVersionActuelle(bool isVersionActuelle){
     m_isVersionActuelle=isVersionActuelle;
 }

/******************ARTICLE**********************/

Article::Article(const QString& title, QString statut, const QString& text,const QString& id,const QDate &dateCreation, const QDate &dateLastModif,const int &nVersion, const bool &isVersionActuelle):
    Note(title,statut,id,dateCreation,dateLastModif,nVersion,isVersionActuelle),m_text(text)
{}

void Article::setText(const QString& text) {
    m_text=text;
}

QXmlStreamWriter& Article::save(QXmlStreamWriter& stream) const {
        stream.writeStartElement("article");
        stream.writeTextElement("id",getId());
        stream.writeTextElement("statut",getStatut());
        stream.writeTextElement("nVersion",QString::number(getNVersion()));
        stream.writeTextElement("isVersionActuelle",QString::number(getIsVersionActuelle()));
        stream.writeTextElement("title",getTitle());
        stream.writeTextElement("text",getText());
        stream.writeTextElement("dateCreation",getDateCreation().toString("dd-MM-yyyy"));
        stream.writeTextElement("dateLastModif",getDateLastModif().toString("dd-MM-yyyy"));
        stream.writeEndElement();
        return stream;
}


/******************TASK**********************/

Task::Task(const QString& title, QString statut,const QString& action,const QString& priority,const QDate& deadline, const QString& id,const QDate& dateCreation,const QDate& dateLastModif,const int &nVersion, const bool &isVersionActuelle):
    Note(title,statut,id,dateCreation,dateLastModif,nVersion,isVersionActuelle),m_action(action),m_priority(priority),m_deadline(deadline)
{}

void Task::setAction(const QString& action) {
    m_action=action;
}
void Task::setPriority(const QString& priority) {
    m_priority=priority;
}
void Task::setDeadline(const QDate& deadline) {
    m_deadline=deadline;
}

QXmlStreamWriter& Task::save(QXmlStreamWriter& stream) const {
        stream.writeStartElement("task");
        stream.writeTextElement("id",getId());
        stream.writeTextElement("statut",getStatut());
        stream.writeTextElement("nVersion",QString::number(getNVersion()));
        stream.writeTextElement("isVersionActuelle",QString::number(getIsVersionActuelle()));
        stream.writeTextElement("title",getTitle());
        stream.writeTextElement("action",getAction());
        stream.writeTextElement("priority",getPriority());
        stream.writeTextElement("deadline",getDeadline().toString("dd-MM-yyyy"));
        stream.writeTextElement("dateCreation",getDateCreation().toString("dd-MM-yyyy"));
        stream.writeTextElement("dateLastModif",getDateLastModif().toString("dd-MM-yyyy"));
        stream.writeEndElement();
        return stream;
}

/********************MEDIA********************/

Media::Media(const QString& title, QString statut,const QString& description, const QString& imageFileName, const QString &id,const QDate &dateCreation, const QDate &dateLastModif,const int &nVersion, const bool &isVersionActuelle):
    Note(title,statut,id,dateCreation,dateLastModif,nVersion,isVersionActuelle),m_description(description),m_imageFileName(imageFileName)
{}

void Media::setDescription(const QString& description){
    m_description=description;
}

void Media::setImageFileName(const QString& imageFileName){
    m_imageFileName=imageFileName;
}


/********************IMAGE********************/

Image::Image(const QString& title, QString statut, const QString& description, const QString& imageFileName, const QString &id,const QDate& dateCreation,const QDate& dateLastModif,const int &nVersion, const bool &isVersionActuelle):
    Media(title,statut,description,imageFileName,id,dateCreation,dateLastModif,nVersion,isVersionActuelle)
{}

QXmlStreamWriter& Image::save(QXmlStreamWriter& stream) const {
        stream.writeStartElement("image");
        stream.writeTextElement("id",getId());
        stream.writeTextElement("statut",getStatut());
        stream.writeTextElement("nVersion",QString::number(getNVersion()));
        stream.writeTextElement("isVersionActuelle",QString::number(getIsVersionActuelle()));
        stream.writeTextElement("title",getTitle());
        stream.writeTextElement("description",getDescription());
        stream.writeTextElement("imageFilename",getImageFileName());
        stream.writeTextElement("dateCreation",getDateCreation().toString("dd-MM-yyyy"));
        stream.writeTextElement("dateLastModif",getDateLastModif().toString("dd-MM-yyyy"));
        stream.writeEndElement();
        return stream;
}


/********************AUDIO********************/

Audio::Audio(const QString& title, QString statut, const QString& description, const QString& imageFileName, const QString &id,const QDate& dateCreation,const QDate& dateLastModif,const int &nVersion, const bool &isVersionActuelle):
Media(title,statut,description,imageFileName,id,dateCreation,dateLastModif,nVersion,isVersionActuelle)
{}

QXmlStreamWriter& Audio::save(QXmlStreamWriter& stream) const {
        stream.writeStartElement("audio");
        stream.writeTextElement("id",getId());
        stream.writeTextElement("statut",getStatut());
        stream.writeTextElement("nVersion",QString::number(getNVersion()));
        stream.writeTextElement("isVersionActuelle",QString::number(getIsVersionActuelle()));
        stream.writeTextElement("title",getTitle());
        stream.writeTextElement("description",getDescription());
        stream.writeTextElement("imageFilename",getImageFileName());
        stream.writeTextElement("dateCreation",getDateCreation().toString("dd-MM-yyyy"));
        stream.writeTextElement("dateLastModif",getDateLastModif().toString("dd-MM-yyyy"));
        stream.writeEndElement();
        return stream;
}


/********************VIDEO********************/

Video::Video(const QString& title, QString statut, const QString& description, const QString& imageFileName, const QString &id, const QDate &dateCreation, const QDate &dateLastModif,const int &nVersion, const bool &isVersionActuelle):
    Media(title,statut,description,imageFileName,id,dateCreation,dateLastModif,nVersion,isVersionActuelle)
{}

QXmlStreamWriter& Video::save(QXmlStreamWriter& stream) const {
        stream.writeStartElement("video");
        stream.writeTextElement("id",getId());
        stream.writeTextElement("statut",getStatut());
        stream.writeTextElement("nVersion",QString::number(getNVersion()));
        stream.writeTextElement("isVersionActuelle",QString::number(getIsVersionActuelle()));
        stream.writeTextElement("title",getTitle());
        stream.writeTextElement("description",getDescription());
        stream.writeTextElement("imageFilename",getImageFileName());
        stream.writeTextElement("dateCreation",getDateCreation().toString("dd-MM-yyyy"));
        stream.writeTextElement("dateLastModif",getDateLastModif().toString("dd-MM-yyyy"));
        stream.writeEndElement();
        return stream;
}
