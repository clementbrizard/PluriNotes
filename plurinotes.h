#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

#include <iostream>
#include <string>
#include <time.h>
#include <fstream>

using namespace std;

//On crée le template pour iterator
//On crée les classes de base

//Classe pour la date 
class date {
private:
	int jour;
	int mois;
	int annee;
public:
	date(int jour = 0, int mois = 0, int annee = 0);
};

//Notes Exception pour les erreurs
class NotesException{
private:
	string info;
public:
	NotesException(const string& message):info(message){}
	string getInfo() const { return info; }
};

//Classe Manager
class Manager{
private:
	static T* m_uniqueInstance;
	T* m_tab ;
	int m_nb;
	int m_nbMax;
	string m_filename;
	Manager();
	Manager(nm : const Manager&);
	~Manager();
	operator=(nm : const Manager&) : Manager&;
public:
	//Class iterator design pattern
template <class T> class iterator{
private:
	T** m_current;
	int m_remain;
	iterator(T** current, int remain);
public:
	const bool isDone();
	next();
	const T& currentValue();
}
	int getNbArticles();
	static Manager& giveInstance();
	static freeInstance();
	T& getNew(const int& id);
	T& get(const int& id);
	load (const string& f);
	const save();
	restore(const int& id);
	iterator begin();
};

//Class Note
class note { //C'est une classe abstraite
protected:
    string m_id;
	string m_title;
	date m_creation;
	date m_last_modif;
	enum m_status
   {
      active,
      archive,
      trash
   };


public:
    note(const string& id, const string& title) : m_id(id), m_title(title) {}
    virtual ~note();
    virtual string getId() const { return m_id; }
	virtual string getTitle() const { return m_title; }
	virtual void setTitle(const string& t) {m_title=t;}
	setDateLastModif(const date& dateLastModif) : m_last_modif(dateLastModif){}
	const date getDateLastModif(){return m_last_modif;}
	setStatus(const string& status);
	const string getStatus(){return m_status;}
	virtual void show() const = 0;
};
class article : public Note{
private:
	string m_text;
	public :
	Article(id : const int&, title : const string&, text : const string&)
	virtual ~Article();
	setText(const string& text):m_text(text)
	const string& getText() const {return m_text;}
	virtual show();

};