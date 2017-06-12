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
Note& NotesManager::getNoteTitle(QString title){
    for (unsigned int i=0; i<m_nbNotes; i++){
        if (title == m_notes[i]->getTitle()) return *m_notes[i];
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

void NotesManager::addArticle(const QString& title, const QString& text,const QString& id){
    for(unsigned int i=0; i<m_nbNotes; i++){
        if (m_notes[i]->getTitle()==title) throw Exception("Erreur : article déjà existant");
    }
    Article* a=new Article(title,text,id);
    addNote(a);
}
void NotesManager::addImage(const QString& title, const QString& description, const QString& imageFileName,const QString& id){
    for(unsigned int i=0; i<m_nbNotes; i++){
        if (m_notes[i]->getTitle()==title) throw Exception("Erreur : Image deja existante");
    }
    Image* i=new Image(title,description,imageFileName,id);
    addNote(i);
}

void NotesManager::addAudio(const QString& title, const QString& description, const QString& imageFileName,const QString& id){
    for(unsigned int i=0; i<m_nbNotes; i++){
        if (m_notes[i]->getTitle()==title) throw Exception("Erreur : Image deja existante");
    }
    Audio* au=new Audio(title,description,imageFileName,id);
    addNote(au);
}
void NotesManager::addVideo(const QString& title, const QString& description, const QString& imageFileName,const QString& id){
    for(unsigned int i=0; i<m_nbNotes; i++){
        if (m_notes[i]->getTitle()==title) throw Exception("Erreur : Video deja existante");
    }
    Video* vi=new Video(title,description,imageFileName,id);
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
        throw Exception("Erreur ouverture fichier notes");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    qDebug()<<"debut fichier\n";
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
            //if(xml.name() == "video") { loadVideo(xml); }
            //if(xml.name() == "task") { loadTask(xml); }
        }
    }
    // Error handling.
    if(xml.hasError()) {
        throw Exception("Erreur lecteur fichier notes, parser xml");
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
    Article* a=new Article(titre,text,identificateur,dateCreation,dateLastModif);
    addLoadedNote(a);
    return xml;
}

QXmlStreamReader& NotesManager::loadImage(QXmlStreamReader& xml){
    qDebug()<<"new image\n";
    QString identificateur;
    QString titre;
    QString description;
    QString imageFileName;
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
        }
        // ...and next...
        xml.readNext();
    }
    qDebug()<<"ajout Image "<<identificateur<<"\n";
    Image* i=new Image(titre,description,imageFileName,identificateur);
    addLoadedNote(i);
    return xml;
}

QXmlStreamReader& NotesManager::loadAudio(QXmlStreamReader& xml){
    qDebug()<<"new audio\n";
    QString identificateur;
    QString titre;
    QString description;
    QString imageFileName;
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
        }
        // ...and next...
        xml.readNext();
    }
    qDebug()<<"ajout Audio "<<identificateur<<"\n";
    Audio* i=new Audio(titre,description,imageFileName,identificateur);
    addLoadedNote(i);
    return xml;
}


/*****************NOTE**************************/

Note::Note(const QString& title, const QString& id, const QDate &dateCreation, const QDate &dateLastModif):
    m_id(id),m_title(title),m_dateCreation(dateCreation),m_dateLastModif(dateLastModif)
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


/******************ARTICLE**********************/

Article::Article(const QString& title, const QString& text,const QString& id,const QDate &dateCreation, const QDate &dateLastModif):
    Note(title,id,dateCreation,dateLastModif),m_text(text)
{}

void Article::setText(const QString& text) {
    m_text=text;
}


QXmlStreamWriter& Article::save(QXmlStreamWriter& stream) const {
        stream.writeStartElement("article");
        stream.writeTextElement("id",getId());
        stream.writeTextElement("title",getTitle());
        stream.writeTextElement("text",getText());
        stream.writeEndElement();
        return stream;
}

/********************MEDIA********************/
Media::Media(const QString& title, const QString& description, const QString& imageFileName, const QString &id):
    Note(title),m_description(description),m_imageFileName(imageFileName)
{}

void Media::setDescription(const QString& description){
    m_description=description;
}

void Media::setImageFileName(const QString& imageFileName){
    m_imageFileName=imageFileName;
}

/********************IMAGE********************/

Image::Image(const QString& title, const QString& description, const QString& imageFileName, const QString &id):
    Media(title,description,imageFileName,id)
{}

QXmlStreamWriter& Image::save(QXmlStreamWriter& stream) const {
        stream.writeStartElement("image");
        stream.writeTextElement("id",getId());
        stream.writeTextElement("title",getTitle());
        stream.writeTextElement("description",getDescription());
        stream.writeTextElement("imageFilename",getImageFileName());
        stream.writeEndElement();
        return stream;
}

/********************AUDIO********************/

Audio::Audio(const QString& title, const QString& description, const QString& imageFileName, const QString &id):
    Media(title,description,imageFileName,id)
{}
QXmlStreamWriter& Audio::save(QXmlStreamWriter& stream) const {
        stream.writeStartElement("audio");
        stream.writeTextElement("id",getId());
        stream.writeTextElement("title",getTitle());
        stream.writeTextElement("description",getDescription());
        stream.writeTextElement("imageFilename",getImageFileName());
        stream.writeEndElement();
        return stream;
}
/********************VIDEO********************/

Video::Video(const QString& title, const QString& description, const QString& imageFileName, const QString &id):
    Media(title,description,imageFileName,id)
{}
QXmlStreamWriter& Video::save(QXmlStreamWriter& stream) const {
        stream.writeStartElement("video");
        stream.writeTextElement("id",getId());
        stream.writeTextElement("title",getTitle());
        stream.writeTextElement("description",getDescription());
        stream.writeTextElement("imageFilename",getImageFileName());
        stream.writeEndElement();
        return stream;
}
QXmlStreamReader& NotesManager::loadVideo(QXmlStreamReader& xml){
    qDebug()<<"new video\n";
    QString identificateur;
    QString titre;
    QString description;
    QString imageFileName;
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
        }
        // ...and next...
        xml.readNext();
    }
    qDebug()<<"ajout Audio "<<identificateur<<"\n";
    Video* v=new Video(titre,description,imageFileName,identificateur);
    addLoadedNote(v);
    return xml;
}