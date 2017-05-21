#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED
#include <string>
#include "timing.h"
#include "Note.h"
using namespace std;

class Exception{
private:
	string info;
public:
	Exception(const string& message) : info(message){}
	string getInfo() const { return info; }
};

class Manager {
private:
    static Manager* m_uniqueInstance;
	Note** m_notes;
	int m_nb;
    int m_nbMax;
	void addNote(Note* n);
	string m_filename;
	Manager() : m_notes(nullptr),m_nb(0),m_nbMax(0),m_filename("tmp.dat"){}
	Manager(const Manager& m);
	Manager& operator=(const Manager& m);
	~Manager();
public:
    unsigned int getNb() {return m_nb;}
	static Manager& giveInstance();
	static void freeInstance();
	Note& getNewNote(const int& id);
	Note& getNote(const int& id);
	void load(const string& f);
	void save() const;
	
	class iteratorManager{
    private:
        T** m_current;
        int m_remain;
        iteratorManager(Note** current, int remain);
        friend class Manager;
    public:
        const bool isDone(){return m_remain==0; };
        void next(){m_current++; m_remain--; return *this; }
        const Note& currentValue(){return **m_current; }
    };
	iteratorManager begin()const {return iteratorManager(m_notes, m_nb); }
};

ostream& operator<<(ostream& f, const Note& n);

#endif
