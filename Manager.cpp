#include <iostream>
#include <fstream>
#include <string>
#include "Manager.h"

void Manager::addNote(Note* n){
	for(int i=0; i<m_nb; i++){
		if (m_notes[i]->getId()==n->getId()) throw Exception("error, creation of an already existent note");
	}
	if (m_nb==m_nbMax){
		Note** newM_notes= new Note*[m_nbMax+5];
		for(int i=0; i<m_nb; i++) newM_notes[i]=m_notes[i];
		Note** oldM_notes=m_notes;
		m_notes=newM_notes;
		m_nbMax+=5;
		if (oldM_notes) delete[] oldM_notes;
	}
	m_notes[m_nb++]=n;
}

Note& Manager::getNote(const int& id){
	for(int i=0; i<m_nb; i++){
		if (m_notes[i]->getId()==id) return *m_notes[i];
	}
	throw Exception("error, nonexistent note");

}

Note& Manager::getNewNote(const int& id){
	Note* n=new Note(id,"",Date(1,1,2000),Date(1,1,2000));
	addNote(n);
	return *n;
}

Manager::~Manager(){
	save();
	for(int i=0; i<m_nb; i++) delete m_notes[i];
	delete[] m_notes;
}

void Manager::save() const {
	ofstream fout(m_filename);
	for(int i=0; i<m_nb; i++){
		fout<<*m_notes[i];
	}
	fout.close();
}

ostream& operator<<(ostream& f, const Note& n){
	n.show();
	return f;
}

void Manager::load(const string& f) {
	if (m_filename!=f) save();
	m_filename=f;
	ifstream fin(m_filename); // open file
	if (!fin) throw Exception("error, file does not exist");
	while(!fin.eof()&&fin.good()){
		char tmp[1000];
		fin.getline(tmp,1000); // get id on the first line
		if (fin.bad()) throw Exception("error reading note id on file");
		string id=tmp;
		fin.getline(tmp,1000); // get title on the next line
		if (fin.bad()) throw Exception("error reading note title on file");
		string title=tmp;
		fin.getline(tmp,1000); // get text on the next line
		if (fin.bad()) throw Exception("error reading note text on file");
		string text=tmp;
		Note* n=new Note(id,title,Date(1,1,2000),Date(1,1,2000));
		addNote(n);
		if (fin.peek()=='\r') fin.ignore();
		if (fin.peek()=='\n') fin.ignore();
	}
	fin.close(); // close file
}

