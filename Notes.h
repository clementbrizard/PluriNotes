#if !defined(_NOTES_H)
#define _NOTES_H
#include <string>
#include <iostream>
using namespace std;

class Article;
class NotesManager;


class NotesException{
public:
	NotesException(const string& message):info(message){}
	string getInfo() const { return info; }
private:
	string info;
};

class Note{
private:
    string id;
	string title;
public:
    Note(const string& i, const string& ti);
    virtual ~Note(){};
    string getId() const { return id; }
	string getTitle() const { return title; }
	void setTitle(const string& t);
    virtual void afficher() const=0;
};

class Article : public Note{
	string text;
public:
	Article(const string& i, const string& ti, const string& te);
	~Article(){}
	string getText() const { return text; }
	void setText(const string& t);
	void afficher()const;
};

class NotesManager {
private:
	Note** notes;
	unsigned int nbNotes;
	unsigned int nbMaxNotes;
	string filename;
	void addNote(Note* n);
	struct Handler {
        NotesManager* instance; // pointeur sur l'unique instance
        Handler():instance(nullptr){}
        ~Handler() { delete instance; }
    };
    static Handler handler;
    NotesManager();
	~NotesManager();
	NotesManager(const NotesManager& m);
	NotesManager& operator=(const NotesManager& m);
public:
	string getFilename() const { return filename; }
    void setFilename(const string& f) { filename=f; }
    void addArticle(const string& i, const string& ti, const string& te);
	void load(const string& f);
	void save() const;
    static NotesManager& getManager();
    static void freeManager();

    class Iterator {
            friend class NotesManager;
            Note** currentN;
            unsigned int nbRemain;
            Iterator(Note** n, unsigned nb):currentN(n),nbRemain(nb){}
        public:
            Iterator():currentN(nullptr),nbRemain(0){}
            bool isDone() const { return nbRemain==0; }
            void next() {
                if (isDone())
                    throw NotesException("error, next on an iterator which is done");
                nbRemain--;
                currentN++;
            }
            Note& current() const {
                if (isDone())
                    throw NotesException("error, indirection on an iterator which is done");
                return **currentN;
            }
        };
        Iterator getIterator()const {
            return Iterator(notes,nbNotes);
        }

};

ostream& operator<<(ostream& f, const Article& a);

ostream& operator<<(ostream&f,const NotesManager& m);

ostream& operator<<(ostream&f, const Note& n);
#endif
