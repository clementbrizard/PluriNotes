#include "Notes.h"
#include <fstream>

/*****************NOTE**************************/

Note::Note(const string& id, const string& title):
    m_id(id),m_title(title),m_dateCreation(time(0)),m_dateLastModif(time(0))
{}

void Note::setTitle(const string& title) {
	m_title=title;
}

void Note::setDateLastModif(time_t dateLastModif){
    m_dateLastModif=dateLastModif;
}

ofstream& operator<<(ofstream&f, const Note& n){
    n.write(f);
    return f;
}


/******************ARTICLE**********************/

Article::Article(const string& id, const string& title, const string& text):
	Note(id,title),m_text(text)
{}

void Article::setText(const string& text) {
	m_text=text;
}

void Article::show()const{
    time_t dateCreation=getDateCreation();
    time_t dateLastModif = getDateLastModif();
    cout<<getId()<<endl<<getTitle()<<endl<<m_text<<endl<<ctime(&dateCreation)<<ctime(&dateLastModif)<<endl;
}

ofstream& Article::write(ofstream& f)const{
    time_t dateCreation=getDateCreation();
    time_t dateLastModif = getDateLastModif();
    f<<getId()<<endl<<getTitle()<<endl<<m_text<<endl<<ctime(&dateCreation)<<ctime(&dateLastModif);
    return f;
}


/********************MEDIA********************/
Media::Media(const string& id,const string& title,const string& description,const string& imageFileName):
    Note(id,title),m_description(description),m_imageFileName(imageFileName)
{}

void Media::setDescription(const string& description){
    m_description=description;
}

void Media::setImageFileName(const string& imageFileName){
    m_imageFileName=imageFileName;
}

/********************IMAGE********************/

Image::Image(const string& id,const string& title,const string& description,const string& imageFileName):
    Media(id,title,description,imageFileName)
{}

void Image::show()const{
    time_t dateCreation=getDateCreation();
    time_t dateLastModif=getDateLastModif();
    cout<<getId()<<endl<<getTitle()<<endl<<getDescription()<<endl<<getImageFileName()<<endl<<ctime(&dateCreation)<<ctime(&dateLastModif)<<endl;
}

ofstream& Image::write(ofstream& f)const{
    time_t dateCreation=getDateCreation();
    time_t dateLastModif = getDateLastModif();
    f<<getId()<<endl<<getTitle()<<endl<<getDescription()<<endl<<getImageFileName()<<endl<<ctime(&dateCreation)<<ctime(&dateLastModif)<<endl;
    return f;
}

/*****************NOTESMANAGER*****************/

NotesManager::NotesManager():m_notes(nullptr),m_nbNotes(0),m_nbMaxNotes(0),m_filename("tmp.dat"){}

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

void NotesManager::addNote(Note* n){
	for(unsigned int i=0; i<m_nbNotes; i++){
		if (m_notes[i]->getId()==n->getId()) throw NotesException("error, creation of an already existent note");
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

void NotesManager::addArticle(const string& id, const string& title, const string& text){
    for(unsigned int i=0; i<m_nbNotes; i++){
        if (m_notes[i]->getId()==id) throw NotesException("Erreur : identificateur déjà existant");
    }
    Article* a=new Article(id,title,text);
    addNote(a);
}

void NotesManager::addImage(const string& id, const string& title, const string& description, const string& imageFileName){
    for(unsigned int i=0; i<m_nbNotes; i++){
        if (m_notes[i]->getId()==id) throw NotesException("Erreur : identificateur déjà existant");
    }
    Image* i=new Image(id,title,description,imageFileName);
    addNote(i);
}

void NotesManager::save() const {
	ofstream fout(m_filename.c_str());
	for(unsigned int i=0; i<m_nbNotes; i++){
		fout<<*m_notes[i]<<endl;
	}
	fout.close();
}

void NotesManager::load(const string& f) {
	if (m_filename!=f) save();
	m_filename=f;
	ifstream fin(m_filename); // open file
	if (!fin) throw NotesException("error, file does not exist");
	while(!fin.eof()&&fin.good()){
		char tmp[1000];
		fin.getline(tmp,1000); // get id on the first line
		if (fin.bad()) throw NotesException("error reading note id on file");
		string id =tmp;
		fin.getline(tmp,1000); // get title on the next line
		if (fin.bad()) throw NotesException("error reading note title on file");
		string title=tmp;
		fin.getline(tmp,1000); // get text on the next line
		if (fin.bad()) throw NotesException("error reading note text on file");
		string text=tmp;
		Article* a=new Article(id,title,text);
		addNote(a);
		if (fin.peek()=='\r') fin.ignore();
		if (fin.peek()=='\n') fin.ignore();
	}
	fin.close(); // close file
}

ostream& operator<<(ostream&f,const NotesManager& m){
    for(NotesManager::Iterator it=m.getIterator(); !it.isDone(); it.next())
        (it.current()).show();
    return f;

}

