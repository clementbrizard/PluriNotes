#include "Relations.h"
using namespace std;

/******************COUPLE************************/

Couple::Couple(const string& id,Note& referencingNote,Note& referencedNote,const string& label):
    m_id(id),m_referencingNote(referencingNote),m_referencedNote(referencedNote),m_label(label)
{}

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
    cout<<m_id<<endl<<"Note référençante : "<<m_referencingNote.getId()<<endl<<"Note référencée : "<<m_referencedNote.getId()<<endl<<m_label<<endl;
}

/*****************RELATION************************/

Relation::Relation(const string& title, const string& description, bool isOriented):
    m_title(title),m_description(description),m_couples(nullptr), m_nbCouples(0), m_nbMaxCouples(0),m_isOriented(isOriented)
{}

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

void Relation::setIsNonOriented(const bool& isOriented){
    m_isOriented=isOriented;
}

void Relation::addCouple(const string& id, Note& referencingNote,Note& referencedNote,const string& label){
    for(int i=0; i<m_nbCouples; i++){
        if (m_couples[i]->getId()==id) throw Exception("Erreur : identificateur déjà existant");
    }

    if (m_nbCouples==m_nbMaxCouples){
		Couple** newM_couples= new Couple*[m_nbMaxCouples+5];
		for(int i=0; i<m_nbCouples; i++) newM_couples[i]=m_couples[i];
		Couple** oldM_couples=m_couples;
		m_couples=newM_couples;
		m_nbMaxCouples+=5;
		if (oldM_couples) delete[] oldM_couples;
	}

    Couple* c=new Couple(id,referencingNote,referencedNote,label);
    m_couples[m_nbCouples++]=c;
}

void Relation::removeCouple(const string& id){
    int i=0;

	while(i<m_nbCouples && m_couples[i]->getId()!=id) i++;
	if (i==m_nbCouples) throw Exception("erreur : Couple inexistant");

	delete m_couples[i];
	m_couples[i]=m_couples[--m_nbCouples];
}

ostream& operator<<(ostream&f,const Relation& r){
     for(Relation::Iterator it=r.getIterator(); !it.isDone(); it.next())
        (it.current()).show();
    return f;
}

