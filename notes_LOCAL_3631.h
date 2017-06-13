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
    QString m_statut;
    QDate m_dateCreation;
    QDate m_dateLastModif;


public:
    Note(const QString& title,QString statut="active",const QString& id="",const QDate& dateCreation=QDate::currentDate(),const QDate& dateLastModif=QDate::currentDate());
    virtual ~Note(){}
    const QString& getId() const { return m_id; }
    const QString& getStatut()const {return m_statut; }
    const QString& getTitle() const { return m_title; }
    QDate getDateCreation()const{return m_dateCreation; }
    QDate getDateLastModif()const{return m_dateLastModif; }
    void setId(const QString& id);
    void setTitle(const QString& title);
    void setDateLastModif(QDate dateLastModif);
    void setStatut(QString statut);
    virtual QXmlStreamWriter& save(QXmlStreamWriter& stream) const = 0;
};

/******************ARTICLE****************/

class Article : public Note{
    QString m_text;
public:
    Article(const QString& title, QString statut, const QString& text, const QString& id="",const QDate& dateCreation=QDate::currentDate(),const QDate& dateLastModif=QDate::currentDate());
    ~Article(){}
    QString getText() const { return m_text; }
    void setText(const QString& text);
    QXmlStreamWriter& save(QXmlStreamWriter& stream) const;
};

/******************TASK****************/

class Task : public Note{
    QString m_action;
    QString m_priority;
    QDate m_deadline;
public:
    Task(const QString& title, QString statut, const QString& action,const QString& priority,const QDate& deadline, const QString& id="",const QDate& dateCreation=QDate::currentDate(),const QDate& dateLastModif=QDate::currentDate());
    ~Task(){}
    QString getAction() const { return m_action; }
    QString getPriority() const { return m_priority; }
    QDate getDeadline() const {return m_deadline;}
    void setAction(const QString& action);
    void setPriority(const QString& priority);
    void setDeadline(const QDate& deadline);
    QXmlStreamWriter& save(QXmlStreamWriter& stream) const;
};


/*****************MEDIA*******************/

class Media : public Note{ // abstraite par construction car n'implémente pas la fonction show()
private:
    QString m_description;
    QString m_imageFileName;
public:
    Media(const QString& title, QString statut, const QString& description, const QString& imageFileName, const QString& id="", const QDate &dateCreation=QDate::currentDate(), const QDate &dateLastModif=QDate::currentDate());
    ~Media(){};
    QString getDescription()const{return m_description; }
    QString getImageFileName()const{return m_imageFileName; }
    void setDescription(const QString& description);
    void setImageFileName(const QString& imageFileName);
};

/***************IMAGE*********************/

class Image : public Media{
public:
    Image(const QString& title, QString statut, const QString& description,const QString& imageFileName,const QString& id="",const QDate& dateCreation=QDate::currentDate(),const QDate& dateLastModif=QDate::currentDate());
    ~Image(){};
    QXmlStreamWriter& save(QXmlStreamWriter& stream) const;
    QString getType() const {return (QString)"img";}
};

/***************AUDIO*********************/

class Audio : public Media{
public:
    Audio(const QString& title, QString statut, const QString& description, const QString& imageFileName, const QString& id="", const QDate& dateCreation=QDate::currentDate(),const QDate& dateLastModif=QDate::currentDate());
    ~Audio(){};
    QXmlStreamWriter& save(QXmlStreamWriter& stream) const;
    QString getType() const {return (QString)"aud";}
};

/***************VIDEO*********************/

class Video : public Media{
public:
    Video(const QString& title,QString statut,const QString& description,const QString& imageFileName,const QString& id="",const QDate& dateCreation=QDate::currentDate(),const QDate& dateLastModif=QDate::currentDate());
    ~Video(){};
    QXmlStreamWriter& save(QXmlStreamWriter& stream) const;
    QString getType() const {return (QString)"vid";}
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

    void addArticle(const QString& title, QString statut, const QString& text, const QString& id="", const QDate &dateCreation=QDate::currentDate(), const QDate &dateLastModif=QDate::currentDate());

    void addImage(const QString& title, QString statut, const QString& description, const QString& imageFileName, const QString& id="",const QDate &dateCreation=QDate::currentDate(), const QDate &dateLastModif=QDate::currentDate());

    void addAudio(const QString& title, QString statut, const QString& description, const QString& imageFileName, const QString& id="",const QDate &dateCreation=QDate::currentDate(), const QDate &dateLastModif=QDate::currentDate());

    void addVideo(const QString& title, QString statut, const QString& description, const QString& imageFileName, const QString& id="",const QDate &dateCreation=QDate::currentDate(), const QDate &dateLastModif=QDate::currentDate());

    void addTask(const QString& title, QString statut, const QString& action,const QString& priority,const QDate& deadline, const QString& id="",const QDate& dateCreation=QDate::currentDate(),const QDate& dateLastModif=QDate::currentDate());

    void removeNote(Note *n);

    void load();

    QXmlStreamReader& loadArticle(QXmlStreamReader& xml);

    QXmlStreamReader& loadTask(QXmlStreamReader& xml);

    QXmlStreamReader& loadImage(QXmlStreamReader& xml);

    QXmlStreamReader& loadAudio(QXmlStreamReader& xml);

    QXmlStreamReader& loadVideo(QXmlStreamReader& xml);

    void save() const;

    // getters
    Note& getNoteByTitle(QString title);
    Note& getNoteById(QString id);

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