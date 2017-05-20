#ifndef NOTE_H_INCLUDED
#define NOTE_H_INCLUDED
#include <iostream>
#include <string>
#include "timing.h"
using namespace std;
using namespace TIME;

enum Status {active, archive, trash};

class Note{
private:
    const int m_id;
    string m_title;
    const Date m_dateCreation;
    Date m_dateLastModif;
    Status m_status;
public :
    Note(const int& id, const string& title, const Date& dateCreation, const Date& dateLastModif) : m_id(id), m_title(title), m_dateCreation(dateCreation), m_dateLastModif(dateLastModif), m_status(active){}
    virtual ~Note() {};
    void setTitle(const string& title){m_title=title; }
    void setStatus(const Status& status){m_status=status; }
    const int& getId() const {return m_id; }
    const string& getTitle() const {return m_title; }
    const Status& getStatus() const {return m_status; }
    void virtual show() const =0;
};

class Article : public Note{
private:
	string m_text;
public :
	Article(const int& id, const string& title, const Date& dateCreation, const Date& dateLastModif, const string& text) : Note(id,title, dateCreation, dateLastModif), m_text(text){}
	~Article() {};
	void setText(const string& text) {m_text=text; }
	const string& getText() const {return m_text;}
	void show() const;
};

class Task : public Note{
private:
	string m_action;
	int m_priority;
	Date m_deadline;
public:
	Task(const int& id, const string& title, const Date& dateCreation, const Date& dateLastModif, const string& action, const int& priority, const Date& deadline=Date(1,1,2000)) : Note(id, title, dateCreation, dateLastModif), m_action(action), m_priority(priority), m_deadline(deadline){}
	~Task() {};
	void setAction(const string& action) {m_action=action; }
	void setPriority(const int& priority) {m_priority=priority; }
	void setDeadline(const Date& deadline) {m_deadline = deadline; }
	const string& getAction() const {return m_action;}
	const int& getPriority() const {return m_priority;}
	const Date& getDeadline() const {return m_deadline;}
	void show() const;
};

class Media : public Note{
private:
	string m_description;
	string m_imageFileName;
public:
	Media(const int& id, const string& title, const Date& dateCreation, const Date& dateLastModif, const string& description, const string& imageFileName) : Note(id,title, dateCreation, dateLastModif), m_description(description), m_imageFileName(imageFileName){}
	~Media(){};
	void setDescription(const string& description) { m_description=description; }
	void setImageFilename(const string& imageFileName){m_imageFileName=imageFileName; }
	const string& getDescription() const {return m_description; }
	const string& getImageFilename() const{return m_imageFileName; }
	void show()const;
};

class Image : public Media{
public :
	Image(const int& id, const string& title, const Date& dateCreation, const Date& dateLastModif, const string& description, const string& imageFileName) : Media(id,title, dateCreation, dateLastModif, description, imageFileName){}
	~Image(){};
};

class Video : public Media{
public :
	Video(const int& id, const string& title, const Date& dateCreation, const Date& dateLastModif, const string& description, const string& imageFileName) : Media(id,title, dateCreation, dateLastModif, description, imageFileName){}
	~Video(){};
};

class Audio : public Media{
public:
    Audio(const int& id, const string& title, const Date& dateCreation, const Date& dateLastModif, const string& description, const string& imageFileName) : Media(id,title, dateCreation, dateLastModif, description,imageFileName){}
	~Audio(){};
};



#endif // NOTE_H_INCLUDED
