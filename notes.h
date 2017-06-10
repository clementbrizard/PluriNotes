#ifndef NOTES_H
#define NOTES_H

#include "qt_include.h"

using namespace std;

class Exception;
class Notes;
class Article;
class NotesManager;


/***************EXCEPTION***********************/

class Exception{
public:
    Exception(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};


/******************NOTE*******************/

class Note{
private:
    QString m_id;
    QString m_title;
    time_t m_dateCreation;
    time_t m_dateLastModif;

public:
    Note(const QString& title,const QString& id="");
    virtual ~Note(){}
    const QString& getId() const { return m_id; }
    const QString& getTitle() const { return m_title; }
    time_t getDateCreation()const{return m_dateCreation; }
    time_t getDateLastModif()const{return m_dateLastModif; }
    void setId(const QString& id);
    void setTitle(const QString& title);
    void setDateLastModif(time_t dateLastModif);
    virtual QXmlStreamWriter& save(QXmlStreamWriter& stream) const = 0;
};




/******************ARTICLE****************/

class Article : public Note{
    QString m_text;
public:
    Article(const QString& title, const QString& text, const QString& id="");
    ~Article(){}
    QString getText() const { return m_text; }
    void setText(const QString& text);
    QXmlStreamWriter& save(QXmlStreamWriter& stream) const;
};

/************NOTESMANAGER*************/
class NotesManager {
private:
    Note** m_notes;
    unsigned int m_nbNotes;
    unsigned int m_nbMaxNotes;
    QString m_filename;

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

        void addNote(Note* n);
        void addLoadedNote(Note* n);

    public:

        Note** getM_notes()const{return m_notes; }
        QString getFilename() const { return m_filename; }

        // Fonctions de manipulations des notes :
        void addArticle(const QString& title, const QString& text, const QString& id="");
        //void addImage(const QString& title, const QString& description, const QString& imageFileName);
        void removeNote(Note *n);
        void load();
        QXmlStreamReader& loadArticle(QXmlStreamReader& xml);
        void save() const;

        // getters
        Note& getNoteTitle(QString title);

        // setters
        void setFilename(const QString& filename) { m_filename=filename; }

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
                        throw Exception("error, next on an iterator which is done");
                    m_nbRemain--;
                    m_currentN++;
                }
                Note& current() const {
                    if (isDone())
                        throw Exception("error, indirection on an iterator which is done");
                    return **m_currentN;
                }
            };
            Iterator getIterator()const {
                return Iterator(m_notes,m_nbNotes);
            }

    };
#endif // NOTES_H
