#ifndef RELATIONS_H
#define RELATIONS_H

#include "qt_include.h"
#include "notes.h"

using namespace std;

class Couple;
class Relation;
class RelationsManager;

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

/**************RELATION*******************/

class Relation{
private:
    QString m_id;
    QString m_title;
    QString m_description;
    Couple** m_couples;
    int m_nbCouples;
    int m_nbMaxCouples;
    bool m_isOriented;
public:
    Relation(const QString& title, const QString& description, Couple** couples=Q_NULLPTR, const int& nbCouples=0, const int& nbMaxCouples=0, const QString &id="", bool isOriented=1);
    ~Relation(){};

    void setId(const QString& id);
    void setNbCouples(const int& nbCouples);
    void setNbMaxCouples(const int& nbMaxCouples);
    void setTitle(const QString& title);
    void setDescription (const QString& description);

    const int& getNbCouples()const{ return m_nbCouples; }
    const int& getNbMaxCouples()const{ return m_nbMaxCouples; }
    const QString& getId()const{return m_id; };
    const QString& getTitle()const{return m_title; };
    const QString& getDescription()const{return m_description; }
    const bool& getIsOriented()const{return m_isOriented; }

    // ajoute un couple à la relation
    void addCouple(Note& referencingNote,Note& referencedNote,const QString& id="",const QString& label="");

    // supprime un couple
    void removeCouple(const QString& id);

    // supprime tous les couples dans la relation qui
    // comportent la note dont on a passé l'id en commentaire
    void removeNote(Note *n);

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


/*************RELATIONSMANAGER************/

class RelationsManager{
private:

    //tableau de relations
    Relation** m_relations;
    int m_nbRelations;
    int m_nbMaxRelations;

    // fichier contenant les relations
    QString m_filename;

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
    QString getFilename() const { return m_filename; }
    void setFilename(const QString& filename) {m_filename=filename; }

    // ajoute une relation au RelationsManager
    void addRelation(const QString& title, const QString& description, Couple** couples=Q_NULLPTR, const int& nbCouples=0, const int& nbMaxCouples=0, const QString &id="", bool isOriented=1);

    // ajoute un couple à la relation dont on a passé l'id en paramètre
    void addCouple(const QString& idRelation, Note& note1, Note& note2, const QString &id="", const QString label="");

    // supprimer une relation et tous les couples qu'elle contient
    void removeRelation(Relation *r);

    // supprime tous les couples contenant la note dont l'id est passé en paramètre
    // fonction appelée quand on supprime une note dans le NotesManager
    void removeNote(Note* n);

    // charge le fichier XML contenant les notes et chacun de leurs couples
    void load();

    // Parse un couple dans une relation du fichier XML contenant toutes les relations
    QXmlStreamReader& loadCouple(QXmlStreamReader& xml);

    // enregistre le RelationsManager dans le ficier XML chargé à l'ouverture de l'application
    void save() const;

    // initialise le RelationsManager
    static RelationsManager& getManager();

    // libère l'instance unique de RelationsManager
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


#endif // RELATIONS_H
