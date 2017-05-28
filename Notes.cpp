#include "Notes.h"
#include "Relations.h"
#include <fstream>

/*****************NOTE**************************/

Note::Note(const string& title):
    m_id(-1),m_title(title),m_dateCreation(time(0)),m_dateLastModif(time(0))
{}

void Note::setId(const int& id){
    m_id=id;
}

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

Article::Article(const string& title, const string& text):
	Note(title),m_text(text)
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
Media::Media(const string& title,const string& description,const string& imageFileName):
    Note(title),m_description(description),m_imageFileName(imageFileName)
{}

void Media::setDescription(const string& description){
    m_description=description;
}

void Media::setImageFileName(const string& imageFileName){
    m_imageFileName=imageFileName;
}

/********************IMAGE********************/

Image::Image(const string& title,const string& description,const string& imageFileName):
    Media(title,description,imageFileName)
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
		if (m_notes[i]->getId()==n->getId()) throw Exception("error, creation of an already existent note");
	}
	if (m_nbNotes==m_nbMaxNotes){
		Note** newM_notes= new Note*[m_nbMaxNotes+5];
		for(unsigned int i=0; i<m_nbNotes; i++) newM_notes[i]=m_notes[i];
		Note** oldM_notes=m_notes;
		m_notes=newM_notes;
		m_nbMaxNotes+=5;
		if (oldM_notes) delete[] oldM_notes;
	}
	n->setId(m_nbNotes);
	m_notes[m_nbNotes++]=n;
}

void NotesManager::addArticle(const string& title, const string& text){
    for(unsigned int i=0; i<m_nbNotes; i++){
        if (m_notes[i]->getTitle()==title) throw Exception("Erreur : article déjà existant");
    }
    Article* a=new Article(title,text);
    addNote(a);
}

void NotesManager::addImage(const string& title, const string& description, const string& imageFileName){
    for(unsigned int i=0; i<m_nbNotes; i++){
        if (m_notes[i]->getTitle()==title) throw Exception("Erreur : Image deja existante");
    }
    Image* i=new Image(title,description,imageFileName);
    addNote(i);
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
	if (!fin) throw Exception("error, file does not exist");
	while(!fin.eof()&&fin.good()){
		char tmp[1000];
		fin.getline(tmp,1000); // get id on the first line
		if (fin.bad()) throw Exception("error reading note id on file");
		string id =tmp;
		fin.getline(tmp,1000); // get title on the next line
		if (fin.bad()) throw Exception("error reading note title on file");
		string title=tmp;
		fin.getline(tmp,1000); // get text on the next line
		if (fin.bad()) throw Exception("error reading note text on file");
		string text=tmp;
		Article* a=new Article(title,text);
		addNote(a);
		if (fin.peek()=='\r') fin.ignore();
		if (fin.peek()=='\n') fin.ignore();
	}
	fin.close(); // close file
}

ostream& operator<<(ostream&f,const NotesManager& m){
    cout<<"Affichage du NotesManager"<<endl<<endl;
    for(NotesManager::Iterator it=m.getIterator(); !it.isDone(); it.next())
        (it.current()).show();
    return f;
}
