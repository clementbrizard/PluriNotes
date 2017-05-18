#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include "timing.h"

using namespace std;

class NotesException{
private:
	string info;
public:
	NotesException(const string& message) : info(message){}
	string getInfo() const { return info; }
};

template <class T> class Manager{
private:
	static T* m_uniqueInstance;
	T** m_notes;
	int m_nb;
	int m_nbMax;
	string m_fileName;
	Manager() : m_tab(nullptr), m_nb(0), m_nbMax(0), m_fileName(""){}
	Manager(const Manager& nm);
	~Manager();
	const Manager& operator=(const Manager& nm);
	void addNote(T* t);
public:
	int getNb() {return m_nb; };
	static Manager& giveInstance();
	static freeInstance();
	T& getNewNote(const int& id);
	T& getNote(const int& id);
	void load (const string& f);
	void save();
	//void restore(const int& id);
		//Class iterator
    template <class T> class iteratorManager{
    private:
        T** m_current;
        int m_remain;
        iterator(T** current, int remain);
        friend class Manager;
    public:
        const bool isDone(return remain==0; );
        void next(){m_current++; m_remain--; return *this; }
        const T& currentValue(){return **m_current; }
    };
	iterator begin()const {return iteratorManager(m_notes, m_nb); }
};

class Note{
private:
    const int m_id;
    string m_title;
    const Date m_dateCreation;
    Date m_dateLastModif;
    Status m_status;
public :
    Note(const int& id, const string& title) : m_id(id), m_title(title), m_dateCreation(Date(0,0,0)), m_dateLastModif(Date(0,0,0)), m_status(active){}
    virtual ~Note();
    void setTitle(const string& title){m_title=title; }
    void setDateLastModif(const Date& dateLastModif){ m_dateLastModif=dateLastModif; }
    void setStatus(const Status& status){m_status=status; }
    const int& getId() const {return m_id; }
    const string& getTitle() const {return m_title; }
    const Date& getDateLastModif() const  {return m_dateLastModif; }
    const Status& getStatus() const {return m_status; }
    void virtual show() const =0;
};

class Article : public Note{
private:
	string m_text;
public :
	Article(const int& id, const string& title, const string& text) : Note(id,title), m_text(text){}
	virtual ~Article();
	void setText(const string& text) {m_text=text; }
	const string& getText() const {return m_text;}
	void virtual show();

};

class Task : public Note{
private:
	string m_action;
	int m_priority;
	Date m_deadline;
public:
	Task(const int& id, const string& title, const string& action, const int& priority, const Date& deadline=Date(0,0,0)) : Note(id, title), m_action(action), m_priority(priority), m_deadline(deadline){}
	virtual ~Task();
	void setAction(const string& action) {m_action=action; }
	void setPriority(const int& priority) {m_priority=priority; }
	void setDeadline(const Date& deadline) {m_deadline = deadline; }
	const string& getAction() const {return m_action;}
	const int& getPriority() const {return m_priority;}
	const Date& getDeadline() const {return m_deadline;}
	void virtual show();
};

class Media : public Note{
private:
	string m_description;
	string m_imageFileName;
public:
	Media(const int& id, const string& title, const string& description, const string& imageFileName) : Note(id,title), m_description(description), m_imageFileName(imageFileName){}
	virtual ~Media();
	void setDescription(const string& description) { m_description=description; }
	void setImageFilename(const string& imageFileName){m_imageFileName=imageFileName; }
	const string& getDescription() const {return m_description; }
	const string& getImageFilename() const{return m_imageFileName; }
	void virtual show();
};

class Image : public Media{
public :
	Image(const int& id, const string& title, const string& description, const string& imageFileName) : Media(id,title,description,imageFileName){}
	~Image();
};

class Video : public Media{
public :
	Video(const int& id, const string& title, const string& description, const string& imageFileName) : Media(id,title,description,imageFileName){}
	~Video();
};

class Audio : public Media{

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


