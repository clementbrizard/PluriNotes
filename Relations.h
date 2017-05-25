#ifndef RELATIONS_H_INCLUDED
#define RELATIONS_H_INCLUDED
#include <string>
#include <iostream>
#include "Notes.h"
using namespace std;

class Couple;
class Relation;


/**************COUPLE*********************/

class Couple{
private:
    string m_id;
    Note& m_referencingNote;
    Note& m_referencedNote;
    string m_label;
public:
    Couple(const string& id,Note& referencingNote,Note& referencedNote,const string& label="");
    ~Couple(){};
    void setReferencingNote(const Note& referencingNote);
    void setReferencedNote(const Note& referencedNote);
    void setLabel(const string& label);
    const string& getId(){return m_id; }
    const Note& getReferencingNote()const{return m_referencingNote; }
    const Note& getReferencedNote()const{return m_referencedNote; }
    void show();
    ofstream& write(ofstream& f)const;
};

/**************RELATION*******************/

class Relation{
private:
    string m_id;
    string m_title;
    string m_description;
    Couple** m_couples;
    int m_nbCouples;
    int m_nbMaxCouples;
    bool m_isOriented;
public:
    Relation(const string& id,const string& title, const string& description, bool isOriented=1);
    ~Relation(){};
    void setNbCouples(const int& nbCouples);
    void setNbMaxCouples(const int& nbMaxCouples);
    void setTitle(const string& title);
    void setDescription (const string& description);
    void setIsNonOriented(const bool& isNonOriented);
    const int& getNbCouples()const{ return m_nbCouples; }
    const int& getNbMaxCouples()const{ return m_nbMaxCouples; }
    const string& getId()const{return m_id; };
    const string& getTitle()const{return m_title; };
    const string& getDescription()const{return m_description; }
    const bool& getIsNonOriented()const{return m_isOriented; }
    void addCouple(const string& id,Note& referencingNote,Note& referencedNote,const string& label);
    void removeCouple(const string& id);
    void removeNote(Note *n);
    void show();

    class Iterator {
            friend class Relation;
            Couple** m_currentC;
            int m_nbRemain;
            Iterator(Couple** currentC, int nbRemain):m_currentC(currentC),m_nbRemain(nbRemain){}
        public:
            Iterator():m_currentC(nullptr),m_nbRemain(0){}
            bool isDone() const { return m_nbRemain==0; }
            void next() {
                if (isDone())
                    throw Exception("error, next on an iterator which is done");
                m_nbRemain--;
                m_currentC++;
            }
            Couple& current() const {
                if (isDone())
                    throw Exception("error, indirection on an iterator which is done");
                return **m_currentC;
            }
        };

    Iterator getIterator()const {
            return Iterator(m_couples,m_nbCouples);
        }
};

ofstream& operator<<(ofstream& f, const Relation& r);


/*************RELATIONSMANAGER************/

class RelationsManager{
private:
	Relation** m_relations;
	int m_nbRelations;
	int m_nbMaxRelations;
	string m_filename;
	struct Handler {
        RelationsManager* instance; // pointeur sur l'unique instance
        Handler():instance(nullptr){}
        ~Handler() { delete instance; }
    };
    static Handler handler;
    RelationsManager();
	~RelationsManager();
	RelationsManager(const RelationsManager& rm);
	RelationsManager& operator=(const RelationsManager& rm);
public:
	Relation** getM_relations()const{return m_relations; }
	string getFilename() const { return m_filename; }
    void setFilename(const string& filename) {m_filename=filename; }
    void addRelation(const string& id, const string& title, const string& description, bool isOriented=1);
    void addCouple(const string& idRelation, const string& idCouple, Note& note1, Note& note2, const string label="");
    void removeRelation(Relation *r);
    void removeNote(Note* n);
    void addCouple(const string& idRelation);
	//void load(const string& filename);
	void save() const;
    static RelationsManager& getManager();
    static void freeManager();

    class Iterator {
            friend class RelationsManager;
            Relation** m_currentR;
            int m_nbRemain;
            Iterator(Relation** currentR, int nbRemain):m_currentR(currentR),m_nbRemain(nbRemain){}
        public:
            Iterator():m_currentR(nullptr),m_nbRemain(0){}
            bool isDone() const { return m_nbRemain==0; }
            void next() {
                if (isDone())
                    throw Exception("error, next on an iterator which is done");
                m_nbRemain--;
                m_currentR++;
            }
            Relation& current() const {
                if (isDone())
                    throw Exception("error, indirection on an iterator which is done");
                return **m_currentR;
            }
        };
        Iterator getIterator()const {
            return Iterator(m_relations,m_nbRelations);
        }
};

ostream& operator<<(ostream& f,const RelationsManager& rm);

#endif // RELATIONS_H_INCLUDED
