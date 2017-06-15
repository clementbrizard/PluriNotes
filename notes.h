#ifndef NOTES_H
#define NOTES_H

#include "qt_include.h"

using namespace std;

class Exception;
class Notes;
class Article;
class NotesManager;

/***************EXCEPTION***********************/
///Gestion des exceptions
class Exception{
public:
    Exception(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};


/******************NOTE*******************/
///Classe abstraite Note
class Note{
private:
    QString m_id;
    QString m_title;
    QString m_statut;
    int m_nVersion;
    bool m_isVersionActuelle;
    QDate m_dateCreation;
    QDate m_dateLastModif;

public:
    Note(const QString& title,QString statut="active",const QString& id="",const QDate& dateCreation=QDate::currentDate(),const QDate& dateLastModif=QDate::currentDate(),const int& nVersion=1,const bool& isVersionActuelle=true);
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
    void setNVersion(int nVersion);
    void setIsVersionActuelle(bool isVersionActuelle);
    virtual QXmlStreamWriter& save(QXmlStreamWriter& stream) const = 0;
    virtual QString getType() const=0;
    const int& getNVersion() const {return m_nVersion;}
    const bool& getIsVersionActuelle() const {return m_isVersionActuelle;}
};

/******************ARTICLE****************/
///Classe Article
class Article : public Note{
    QString m_text;
public:
    Article(const QString& title, QString statut, const QString& text, const QString& id="", const QDate& dateCreation=QDate::currentDate(), const QDate& dateLastModif=QDate::currentDate(), const int &nVersion=1, const bool &isVersionActuelle=true);
    ~Article(){}
    QString getText() const { return m_text; }
    void setText(const QString& text);
    QXmlStreamWriter& save(QXmlStreamWriter& stream) const;
    QString getType() const {return (QString)"art";}
};

/******************TASK****************/
///Classe Task
class Task : public Note{
    QString m_action;
    QString m_priority;
    QDate m_deadline;
public:
    Task(const QString& title, QString statut, const QString& action,const QString& priority,const QDate& deadline, const QString& id="",const QDate& dateCreation=QDate::currentDate(),const QDate& dateLastModif=QDate::currentDate(), const int &nVersion=1, const bool &isVersionActuelle=true);
    ~Task(){}
    QString getAction() const { return m_action; }
    QString getPriority() const { return m_priority; }
    QDate getDeadline() const {return m_deadline;}
    void setAction(const QString& action);
    void setPriority(const QString& priority);
    void setDeadline(const QDate& deadline);
    QXmlStreamWriter& save(QXmlStreamWriter& stream) const;
    QString getType() const {return (QString)"task";}
};

/*****************MEDIA*******************/
///Classe media qui définit les méthodes et attributs communs à vidéo, audio et image
class Media : public Note{ // abstraite par construction car n'implémente pas la fonction show()
private:
    QString m_description;
    QString m_imageFileName;
public:
    Media(const QString& title, QString statut, const QString& description, const QString& imageFileName, const QString& id="", const QDate &dateCreation=QDate::currentDate(), const QDate &dateLastModif=QDate::currentDate(), const int &nVersion=1, const bool &isVersionActuelle=true);
    ~Media(){};
    QString getDescription()const{return m_description; }
    QString getImageFileName()const{return m_imageFileName; }
    void setDescription(const QString& description);
    void setImageFileName(const QString& imageFileName);
    virtual QString getType() const=0;
};

/***************IMAGE*********************/
///Classe Image
class Image : public Media{
public:
    Image(const QString& title, QString statut, const QString& description,const QString& imageFileName,const QString& id="",const QDate& dateCreation=QDate::currentDate(),const QDate& dateLastModif=QDate::currentDate(), const int &nVersion=1, const bool &isVersionActuelle=true);
    ~Image(){};
    QXmlStreamWriter& save(QXmlStreamWriter& stream) const;
    QString getType() const {return (QString)"img";}
};

/***************AUDIO*********************/
///Classe Audio
class Audio : public Media{
public:
    Audio(const QString& title, QString statut, const QString& description, const QString& imageFileName, const QString& id="", const QDate& dateCreation=QDate::currentDate(),const QDate& dateLastModif=QDate::currentDate(), const int &nVersion=1, const bool &isVersionActuelle=true);
    ~Audio(){};
    QXmlStreamWriter& save(QXmlStreamWriter& stream) const;
    QString getType() const {return (QString)"aud";}
};

/***************VIDEO*********************/
///Classe Video
class Video : public Media{
public:
    Video(const QString& title,QString statut,const QString& description,const QString& imageFileName,const QString& id="",const QDate& dateCreation=QDate::currentDate(),const QDate& dateLastModif=QDate::currentDate(), const int &nVersion=1, const bool &isVersionActuelle=true);
    ~Video(){};
    QXmlStreamWriter& save(QXmlStreamWriter& stream) const;
    QString getType() const {return (QString)"vid";}
};

/************NOTESMANAGER*************/
///Classe NotesManager
class NotesManager {
private:
    Note** m_notes;
    unsigned int m_nbNotes;
    unsigned int m_nbMaxNotes;
    QString m_filename;
    ///Instance unique du NotesManager
    struct Handler {
        NotesManager* instance; // pointeur sur l'unique instance
        Handler():instance(nullptr){}
        ~Handler() { delete instance; }
    };
    static Handler handler;
    ///Constructeur du NotesManager
    NotesManager();
    ///Destructeur du NotesManager
    ~NotesManager();
    NotesManager(const NotesManager& nm);
    ///Surchage de l'opérateur =
    NotesManager& operator=(const NotesManager& nm);
    ///Ajoute une note au NotesManager
    void addNote(Note* n);
    ///Ajoute une note qui est chargée du XML au NotesManager
    void addLoadedNote(Note* n);

    /// ajoute un article au NotesManager sans incrémenter son id
    void addModifiedNote(Note* n);

public:

    Note** getM_notes()const{return m_notes; }
    QString getFilename() const { return m_filename; }

    // Fonctions de manipulations des notes :
    ///Ajoute un article
    void addArticle(const QString& title, QString statut, const QString& text, const QString& id="", const QDate &dateCreation=QDate::currentDate(), const QDate &dateLastModif=QDate::currentDate(), const int &nVersion=1, const bool &isVersionActuelle=true);
    ///Ajoute une image
    void addImage(const QString& title, QString statut, const QString& description, const QString& imageFileName, const QString& id="", const QDate &dateCreation=QDate::currentDate(), const QDate &dateLastModif=QDate::currentDate(), const int &nVersion=1, const bool &isVersionActuelle=true);
    ///Ajoute un audio
    void addAudio(const QString& title, QString statut, const QString& description, const QString& imageFileName, const QString& id="",const QDate &dateCreation=QDate::currentDate(), const QDate &dateLastModif=QDate::currentDate(), const int &nVersion=1, const bool &isVersionActuelle=true);
    ///Ajoute une vidéo
    void addVideo(const QString& title, QString statut, const QString& description, const QString& imageFileName, const QString& id="",const QDate &dateCreation=QDate::currentDate(), const QDate &dateLastModif=QDate::currentDate(), const int &nVersion=1, const bool &isVersionActuelle=true);
    ///Ajoute une tache
    void addTask(const QString& title, QString statut, const QString& action,const QString& priority,const QDate& deadline, const QString& id="",const QDate& dateCreation=QDate::currentDate(),const QDate& dateLastModif=QDate::currentDate(), const int &nVersion=1, const bool &isVersionActuelle=true);
    ///Supprime les anciennes versions d'une note
    void removeOldVersionsOfNote(const Note* n);
    ///Supprime une note
    void removeNote(Note *n);
    ///Appelle la fonction principale load qui appelle la fonction load nécessaire en fonction du type de la note
    void load();
    ///Fonction load adaptée au type Article
    QXmlStreamReader& loadArticle(QXmlStreamReader& xml);
    ///Fonction load adaptée au type Task
    QXmlStreamReader& loadTask(QXmlStreamReader& xml);
    ///Fonction load adaptée au type Image
    QXmlStreamReader& loadImage(QXmlStreamReader& xml);
    ///Fonction load adaptée au type Audio
    QXmlStreamReader& loadAudio(QXmlStreamReader& xml);
    ///Fonction load adaptée au type Video
    QXmlStreamReader& loadVideo(QXmlStreamReader& xml);
    ///Appel des fonctions save adaptée pour chaque type
    void save() const;
    ///Retourne true si la note dont on a fourni l'id existe
    bool NoteActiveExists(const QString& id);

    // getters
    ///Retourne la derniere version de la note dont on a envoyé le titre
     Note* getNoteActiveByTitle(const QString& title);
     ///Retourne la derniere version de la note dont on a envoyé l'id
     Note* getNoteActiveById(const QString& id);

        // setters
     ///Permet de renseigner le nom du fichier XML utilisé
        void setFilename(const QString& filename) { m_filename=filename; }
    ///Renvoie une instance de NotesManager
    static NotesManager& getManager();
    ///Libère l'instance du NotesManager
    static void freeManager();
    ///Design pattern iterator du NotesManager
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

/************CORBEILLE************/

/// Classe permettant le stockage lorsqu'une note est supprimée. La note devient en attente d'une éventuelle restauration
class Corbeille{
private :
    /// vector d'objet pointeur sur Note
    vector<Note*> poubelle;
    /// Constructeur
    Corbeille();
    /// Constructeur de recopie
    Corbeille(const Corbeille& c);
     ///Surcharge de l'opérateur =
    Corbeille& operator=(const Corbeille& c);
    ///Destructeur
    ~Corbeille();

    ///static Corbeille *instance: Implantation du singleton
    struct HandlerC{
        Corbeille* instance;
        HandlerC() : instance(0){}
        ~HandlerC(){if(instance) delete instance; instance = 0;}
    };
    static HandlerC handlerC;

public :
    static Corbeille& getInstance();
    static void libererInstance();
    ///Permet de savoir le nombre d'éléments dans la corbeille
    int getPoubelleSize() const {return poubelle.size();}
    /// Restaurer une note
    void RestoreNote(Note* n);
    /// Trouver une note par son titre
    Note* getNoteByTitle(QString title);
    ///Trouver une note par son ID
    Note* getNoteById(QString id);
    /// Trouver une note par sa position dans la corbeille
    Note* getNoteByPosition(unsigned int position);
    ///Suppression d'une note de la corbeille
    void deleteNote(Note* n);
    ///Ajout d'une note dans la corbeille
    void addNote(Note*n);
    ///Retourne la position d'une note dans le vecteur dustbin
    unsigned int getNotePosition(Note*n);
    ///Vide le vecteur dustbin
    void emptyDustBin(){poubelle.clear();}
};

#endif // NOTES_H
