#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include "timing.h"

using namespace std;

//On crée les classes de base

//Notes Exception pour les erreurs
class NotesException{
private:
	string info;
public:
	NotesException(const string& message) : info(message){}
	string getInfo() const { return info; }
};

//Classe Manager
template <class T> class Manager{
private:
	static T* m_uniqueInstance;
	T* m_tab ;
	int m_nb;
	int m_nbMax;
	string m_filename;
	Manager();
	Manager(const Manager& nm);
	~Manager();
	const Manager& operator=(const Manager& nm);
public:
	int getNb() {return m_nb; };
	static Manager& giveInstance();
	static freeInstance();
	T& getNew(const int& id);
	T& get(const int& id);
	void load (const string& f);
	void save();
	void restore(const int& id);
		//Class iterator
    template <class T> class iterator{
    private:
        T** m_current;
        int m_remain;
        iterator(T** current, int remain);
    public:
        const bool isDone();
        void next();
        const T& currentValue();
    };
	iterator begin();
};

//Class Note

class Article : public Note{
private:
	string m_text;
public :
	Article(const int& id, const string& title, const string& text) : Note(id,title), m_text(text){}
	virtual ~Article();
	setText(const string& text) {m_text=text; }
	const string& getText() const {return m_text;}
	virtual show();

};

class Task : public Note{
private:
	string m_action;
	int m_priority;
	date m_deadline;
public:
	Task(const int& id, const string& title, const string& action, const int& priority, const Date& deadline=O) : Note(id, title), m_action(action), m_priority(priority), m_deadline(deadline)
	virtual ~Task();
	setAction(const string& action) {m_action=action; }
	setPriority(const int& priority) {m_priority=priority; }
	setDeadline(const Date& deadline) {m_deadline = deadline; }
	const string& getAction() const {return m_action;}
	const int& getPriority() const {return m_priority;}
	const Date& getDeadline() const {return m_deadline;}
	virtual show();
};

class Media : public Note{
private:
	string m_description;
	string m_imageFileName;
public:
	media(const string& id, const string& title, const string& description, const string& imageFileName) : Note(id,title), m_description(description), m_imageFilename(imageFilename){}
	virtual ~media() const = 0;
	setDescription(const string& description) { m_description=description; }
	setImageFilename(const string& imageFileName){m_imageFileName=imageFileName; }
	const string& getDescription() const {return m_description; }
	const string& getImageFilename() const{return m_imageFileName; }
	virtual show();
};

class Image : public Media{
public :
	Image(const string& id, const string& title, const string& description, const string& imageFileName) : Media(id,title,description,imageFileName){}
	~Image();
};

class Video : public media{
public :
	Video(const string& id, const string& title, const string& description, const string& imageFileName) : Media(id,title,description,imageFileName){}
	~Video();
};

class Audio : public media{
public :
    Audio(const string& id, const string& title, const string& description, const string& imageFileName) : Media(id,title,description,imageFileName){}
    ~Audio();
};

class Couple{
private:
	Note m_referencingNote;
	Note m_referencedNote;
	string label;
public:
	Couple(const Note& referencingNote,const Note& referencedNote,const string& label ='') : m_referencingNote(referencingNote), m_referencedNote(referencedNote) {}
	~Couple();
	setReferencingNote(const Note& referencingNote){m_referencingNote=referencingNote; }
	setReferencedNote(const Note& referencedNote){m_referencedNote=referencedNote; }
    setLabel(const string& label){m_label=label; }
    const Note& getReferencingNote() const {return m_referencingNote; }
    const Note& getReferencedNote() const  {return m_referencedNote; }
    const string& getLabel() const {return label; }
};


