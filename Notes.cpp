#include "Notes.h"
#include <fstream>

Note::Note(const string& i, const string& ti):
    id(i),title(ti)
{}
Article::Article(const string& i, const string& ti, const string& te):
	Note(i,ti),text(te)
{}

void Note::setTitle(const string& t) {
	title=t;
}

void Article::setText(const string& t) {
	text=t;
}

void Article::afficher()const{
    cout<<getId()<<getTitle()<<text<<endl;
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
	for(unsigned int i=0; i<nbNotes; i++){
		if (notes[i]->getId()==n->getId()) throw NotesException("error, creation of an already existent note");
	}
	if (nbNotes==nbMaxNotes){
		Note** newNotes= new Note*[nbMaxNotes+5];
		for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
		Note** oldNotes=notes;
		notes=newNotes;
		nbMaxNotes+=5;
		if (oldNotes) delete[] oldNotes;
	}
	notes[nbNotes++]=n;
}

void NotesManager::addArticle(const string& id, const string& ti, const string& te){
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("Erreur : identificateur déjà existant");
    }
    Article* a=new Article(id,ti,te);
    addNote(a);
}

NotesManager::NotesManager():notes(nullptr),nbNotes(0),nbMaxNotes(0),filename(""){}

NotesManager::~NotesManager(){
    if (filename!="") save();
	for(unsigned int i=0; i<nbNotes; i++) delete notes[i];
	delete[] notes;
}

void NotesManager::save() const {
	ofstream fout(filename);
	for(unsigned int i=0; i<nbNotes; i++){
		fout<<*notes[i];
	}
	fout.close();
}

void NotesManager::load(const string& f) {
	if (filename!=f) save();
	filename=f;
	ifstream fin(filename); // open file
	if (!fin) throw NotesException("error, file does not exist");
	while(!fin.eof()&&fin.good()){
		char tmp[1000];
		fin.getline(tmp,1000); // get id on the first line
		if (fin.bad()) throw NotesException("error reading note id on file");
		string id=tmp;
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

ostream& operator<<(ostream& f, const Article& a){
	f<<a.getId()<<"\n";
	f<<a.getTitle()<<"\n";
	f<<a.getText()<<"\n";
	return f;
}

ostream& operator<<(ostream&f,const NotesManager& m){
    for(NotesManager::Iterator it=m.getIterator(); !it.isDone(); it.next())
        f<<it.current();
    return f;

}

ostream& operator<<(ostream&f, const Note& n){
    n.afficher();
    return f;
}

