#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

#include <iostream>
#include <string>
#include <time.h>
#include <fstream>

using namespace std;


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
class article : public note{
private:
	string m_text;
	public :
	Article(const int& id,const string& title,const string&  text)
	virtual ~Article();
	setText(const string& text):m_text(text)
	const string& getText() const {return m_text;}
	virtual show();

};
class task : public note{
private:
	string m_action;
	int m_priority;
	int m_deadline;
public:
	Task(const int& id,const string&  title,const string& action,const int& priority);
	virtual ~Task();
	setAction(const string& action);
	setPriority(const int& priority);
	setDeadline(const int& deadline);
	const string& getAction() const {return m_action;}  
	const int& getPriority() const {return m_priority;}
	const int& getDeadline() const {return m_deadline;}
	virtual show(); 
};
class media :public note{
private:
	string m_description; 
	string m_imageFileName;
public:
	media(const string& id,const string&  title, const string&description,const string&  imageFileName);
	virtual ~media()  const = 0;
	setDescription(const string& description):m_description(description){}
	setImageFilename(const string& imageFileName):m_imageFileName(imageFileName){}
	const string& getDescription() const {return m_description;}
	const string& getImageFilename() const{return m_imageFileName;}
	virtual show();
};
class image : public media{
	public :
	~image();
};
class video : public media{
	public :
	~video();
};
class audio : public media{
	public :
	~audio();
};

class couple{
private:
	Note m_referencingNote; 
	Note m_referencedNote;
	string label;
public:
	couple(const Note& referencingNote,const Note& referencedNote,const string& label ='');
	~couple();
	setReferencingNote(const Note& referencingNote):m_referencingNote(referencingNote){}
	setReferencedNote(const Note& referencedNote):m_referencedNote(referencedNote){}
setLabel(const string& label):label(label){}
const Note& getReferencingNote() const {return m_referencingNote;}
const Note& getReferencedNote() const  {return m_referencedNote;}
const string&  getLabel() const {return label;}
};