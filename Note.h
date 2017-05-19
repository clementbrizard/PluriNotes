#ifndef NOTE_H_INCLUDED
#define NOTE_H_INCLUDED
#include <iostream>
#include <string>
#include "Exception.h"
#include "timing.h"
using namespace std;


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
    Audio(const int& id, const string& title, const string& description, const string& imageFileName) : Media(id,title,description,imageFileName){}
	~Audio();
}


#endif // NOTE_H_INCLUDED
