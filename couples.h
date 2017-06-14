#ifndef RELATIONS_H
#define RELATIONS_H

#include "qt_include.h"
#include "notes.h"

using namespace std;

class Couple;
class Relation;
class CouplesManager;

/**************COUPLE*********************/

class Couple{
private:
    QString m_id;
    Note& m_referencingNote;
    Note& m_referencedNote;
    QString m_label;
public:
    Couple(Note& referencingNote,Note& referencedNote,const QString& id="",const QString& label="");
    ~Couple(){};

    void setId(const QString& id);
    void setReferencingNote(const Note& referencingNote);
    void setReferencedNote(const Note& referencedNote);
    void setLabel(const QString& label);

    const QString& getId()const{return m_id; }
    const Note& getReferencingNote()const{return m_referencingNote; }
    const Note& getReferencedNote()const{return m_referencedNote; }
};


/*************COUPLESMANAGER************/

class CouplesManager{
private:

    //tableau de couples
    Couple** m_couples;
    int m_nbCouples;
    int m_nbMaxCouples;

    // fichier contenant les relations
    QString m_filename;

    struct Handler {
        CouplesManager* instance; // pointeur sur l'unique instance
        Handler():instance(nullptr){}
        ~Handler() { delete instance; }
    };
    static Handler handler;

    CouplesManager();
    ~CouplesManager();
    CouplesManager(const CouplesManager& rm);
    CouplesManager& operator=(const CouplesManager& rm);

public:

    Couple** getM_couples()const{return m_couples; }
    QString getFilename() const { return m_filename; }
    void setFilename(const QString& filename) {m_filename=filename; }

    void setNbMaxCouples(const int& nbMaxCouples);

    void setNbCouples(const int& nbCouples);

    // ajoute un couple au CouplesManager
    void addCouple(Note& referencingNote,Note& referencedNote,const QString& id="",const QString& label="");

    // supprime tous les couples contenant la note dont l'id est passé en paramètre
    // fonction appelée quand on supprime une note dans le NotesManager
    void removeNote(Note* n);

    // charge le fichier XML contenant tous les couples
    void load();

    // enregistre le CouplesManager dans le ficier XML chargé à l'ouverture de l'application
    void save() const;

    // initialise le CouplesManager
    static CouplesManager& getManager();

    // libère l'instance unique de CouplesManager
    static void freeManager();

    class Iterator {
            friend class CouplesManager;
            Couple** m_currentR;
            int m_nbRemain;
            Iterator(Couple** currentR, int nbRemain):m_currentR(currentR),m_nbRemain(nbRemain){}
        public:
            Iterator():m_currentR(nullptr),m_nbRemain(0){}
            bool isDone() const { return m_nbRemain==0; }
            void next() {
                if (isDone())
                    throw Exception("error, next on an iterator which is done");
                m_nbRemain--;
                m_currentR++;
            }
            Couple& current() const {
                if (isDone())
                    throw Exception("error, indirection on an iterator which is done");
                return **m_currentR;
            }
        };
        Iterator getIterator()const {
            return Iterator(m_couples,m_nbCouples);
        }
};


#endif // RELATIONS_H
