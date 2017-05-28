#include "Relations.h"
#include <fstream>
using namespace std;

/******************COUPLE************************/

Couple::Couple(Note& referencingNote,Note& referencedNote,const string& label):
    m_id(-1),m_referencingNote(referencingNote),m_referencedNote(referencedNote),m_label(label)
{}

void Couple::setId(const int& id){
    m_id=id;
}

void Couple::setReferencingNote(const Note& referencingNote){
    m_referencingNote=referencingNote;
 }

void Couple::setReferencedNote(const Note& referencedNote){
    m_referencedNote=referencedNote;
}

void Couple::setLabel(const string& label){
    m_label=label;
}

void Couple::show(){
    cout<<m_id<<endl<<"Note référençante : "<<m_referencingNote.getId()<<endl<<"Note référencée : "<<m_referencedNote.getId()<<endl<<m_label<<endl<<endl;
}

ofstream& Couple::write(ofstream& f)const{
    f<<m_id<<endl<<m_referencingNote.getId()<<endl<<m_referencedNote.getId()<<endl;
    if(m_label!="") f<<m_label<<endl;
    f<<endl;
    return f;
}

/*****************RELATION************************/

Relation::Relation(const string& title, const string& description, bool isOriented):
    m_id(-1),m_title(title),m_description(description),m_couples(nullptr), m_nbCouples(0), m_nbMaxCouples(0),m_isOriented(isOriented)
{}

void Relation::setId(const int& id){
    m_id=id;
}

void Relation::setNbCouples(const int& nbCouples){
    m_nbCouples = nbCouples;
}

void Relation::setNbMaxCouples(const int& nbMaxCouples){
    m_nbMaxCouples=nbMaxCouples;
}

void Relation::setTitle(const string& title){
    m_title=title;
}

void Relation::setDescription (const string& description){
    m_description=description;
}

void Relation::addCouple(Note& referencingNote,Note& referencedNote,const string& label){

    if (m_nbCouples==m_nbMaxCouples){
		Couple** newM_couples= new Couple*[m_nbMaxCouples+5];
		for(int i=0; i<m_nbCouples; i++) newM_couples[i]=m_couples[i];
		Couple** oldM_couples=m_couples;
		m_couples=newM_couples;
		m_nbMaxCouples+=5;
		if (oldM_couples) delete[] oldM_couples;
	}

    Couple* c=new Couple(referencingNote,referencedNote,label);
    c->setId(m_nbCouples);
    m_couples[m_nbCouples++]=c;
}

void Relation::removeCouple(const int& id){
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

void Relation::show(){
    cout<<"Affichage de la relation "<<m_title<<endl;
    for(Iterator it=getIterator(); !it.isDone(); it.next())
        (it.current()).show();
}

ofstream& operator<<(ofstream&f, const Relation& r){
     for(Relation::Iterator it=r.getIterator(); !it.isDone(); it.next())
        (it.current()).write(f);
    return f;
}


/*************RELATIONSMANAGER************/

RelationsManager::RelationsManager():m_relations(nullptr),m_nbRelations(0),m_nbMaxRelations(0),m_filename("Relations.dat"){}

RelationsManager::~RelationsManager(){
    save();
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

void RelationsManager::addRelation(const string& title, const string& description, bool isOriented){
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
	Relation* r=new Relation(title,description,isOriented);
	r->setId(m_nbRelations);
	m_relations[m_nbRelations++]=r;
}

void RelationsManager::addCouple(const int& idRelation, Note& note1, Note& note2, const string label){
    Iterator it=getIterator();
    while(!it.isDone() && it.current().getId()!=idRelation) it.next();
    if(it.isDone()) throw Exception("La relation à laquelle vous voulez ajouter un couple n'existe pas encore");
    else{
        it.current().addCouple(note1,note2,label);
        if(!it.current().getIsOriented())
             it.current().addCouple(note2,note1,label);
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

void RelationsManager::save() const {
	ofstream fout(m_filename.c_str());
	for(int i=0; i<m_nbRelations; i++){
		fout<<*m_relations[i]<<endl;
	}
	fout.close();
}

/*void RelationsManager::load(const string& f) { // à modifier pour qu'elle charge des Relations
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
		Article* a=new Article(id,title,text);
		addRelation(a);
		if (fin.peek()=='\r') fin.ignore();
		if (fin.peek()=='\n') fin.ignore();
	}
	fin.close(); // close file
}*/

ostream& operator<<(ostream& f,const RelationsManager& rm){
    cout<<"Affichage du RelationsManager"<<endl;
     for(RelationsManager::Iterator it=rm.getIterator(); !it.isDone(); it.next())
        (it.current()).show();
    return f;
}
