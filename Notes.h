#if !defined(_NOTES_H)
#define _NOTES_H
#include <string>
#include <iostream>
#include <ctime>
using namespace std;

class NotesException;
class Note;
class Article;
class Media;
class Image;
class NotesManager;

class NotesException{
public:
	NotesException(const string& message):info(message){}
	string getInfo() const { return info; }
private:
	string info;
};

/******************NOTE*******************/

class Note{
private:
    string m_id;
	string m_title;
	time_t m_dateCreation;
	time_t m_dateLastModif;

public:
    Note(const string& id, const string& title);
    virtual ~Note(){}
    string getId() const { return m_id; }
	string getTitle() const { return m_title; }
	time_t getDateCreation()const{return m_dateCreation; }
	time_t getDateLastModif()const{return m_dateLastModif; }
	void setTitle(const string& title);
	void setDateLastModif(time_t dateLastModif);
    virtual void show() const=0;
    virtual ofstream& write(ofstream& f) const=0;
};


ofstream& operator<<(ostream&f, const Note& n);

/******************ARTICLE****************/

class Article : public Note{
	string m_text;
public:
	Article(const string& id, const string& title, const string& text);
	~Article(){}
	string getText() const { return m_text; }
	void setText(const string& text);
	void show()const;
	ofstream& write(ofstream& f)const;
};


/*****************MEDIA*******************/

class Media : public Note{ // abstraite par construction car n'implémente pas la fonction show()
private:
    string m_description;
    string m_imageFileName;
public:
    Media(const string& id,const string& title,const string& description,const string& imageFileName);
    ~Media(){};
    string getDescription()const{return m_description; }
    string getImageFileName()const{return m_imageFileName; }
    void setDescription(const string& description);
    void setImageFileName(const string& imageFileName);
};

/***************IMAGE*********************/

class Image : public Media{
public:
    Image(const string& id,const string& title,const string& description,const string& imageFileName);
    ~Image(){};
    void show()const;
    ofstream& write(ofstream& f)const;
};

/**************NOTESMANAGER***************/

class NotesManager {
private:
	Note** m_notes;
	unsigned int m_nbNotes;
	unsigned int m_nbMaxNotes;
	string m_filename;
	void addNote(Note* n);
	struct Handler {
        NotesManager* instance; // pointeur sur l'unique instance
        Handler():instance(nullptr){}
        ~Handler() { delete instance; }
    };
    static Handler handler;
    NotesManager();
	~NotesManager();
	NotesManager(const NotesManager& nm);
	NotesManager& operator=(const NotesManager& nm);
public:
	string getFilename() const { return m_filename; }
    void setFilename(const string& filename) { m_filename=filename; }
    void addArticle(const string& id, const string& title, const string& text);
    void addImage(const string& id, const string& title, const string& description, const string& imageFileName);
	void load(const string& filename);
	void save() const;
    static NotesManager& getManager();
    static void freeManager();

    class Iterator {
            friend class NotesManager;
            Note** m_currentN;
            unsigned int m_nbRemain;
            Iterator(Note** currentN, unsigned nbRemain):m_currentN(currentN),m_nbRemain(nbRemain){}
        public:
            Iterator():m_currentN(nullptr),m_nbRemain(0){}
            bool isDone() const { return m_nbRemain==0; }
            void next() {
                if (isDone())
                    throw NotesException("error, next on an iterator which is done");
                m_nbRemain--;
                m_currentN++;
            }
            Note& current() const {
                if (isDone())
                    throw NotesException("error, indirection on an iterator which is done");
                return **m_currentN;
            }
        };
        Iterator getIterator()const {
            return Iterator(m_notes,m_nbNotes);
        }

};

ostream& operator<<(ostream&f,const NotesManager& nm);

#endif
