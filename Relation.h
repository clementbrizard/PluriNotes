#ifndef RELATION_H_INCLUDED
#define RELATION_H_INCLUDED
#include <string>
#include "Exception.h"
#include "timing.h"
using namespace std;


class Couple{
private:
	Note m_referencingNote;
	Note m_referencedNote;
	string label;
public:
	Couple(const Note& referencingNote,const Note& referencedNote,const string& label ='') : m_referencingNote(referencingNote), m_referencedNote(referencedNote) {}
	~Couple();
	setReferencingNote(const Note& referencingNote){m_referencingNote=referencingNote; }
	setReferencedNote(const Note& referencedNote){m_referencedNote=referencedNote; }
    setLabel(const string& label){m_label=label; }
    const Note& getReferencingNote() const {return m_referencingNote; }
    const Note& getReferencedNote() const  {return m_referencedNote; }
    const string& getLabel() const {return label; }
};




#endif // RELATION_H_INCLUDED
