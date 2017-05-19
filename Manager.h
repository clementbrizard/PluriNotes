#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED
#include <string>
#include "Exception.h"
#include "timing.h"
using namespace std;

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


#endif // MANAGER_H_INCLUDED
