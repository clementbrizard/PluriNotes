#include "Note.h"
#include <iostream>
using namespace std;

void Article::show()const{
    cout << "Id : " << getId() << "\n";
    cout << "Titre : " << getTitle() << "\n";
    cout << "Contenu : " << m_text << "\n";
}

void Task::show()const{
    cout << "Id : " << getId() << "\n";
    cout << "Titre: " << getTitle() << "\n";
    cout << "Action: " << m_action <<"\n";
    if (m_priority != 0) cout << "Priorité : " << m_priority <<"\n";
    if(!(m_deadline == Date(1,1,2000))) cout << "Deadline : "<<m_deadline;
}

void Media::show()const{
    cout << "Id : " << getId() << "\n";
    cout << "Titre: " << getTitle() << "\n";
    cout << "Description: " << m_description << "\n";
    cout << "Media: " << m_imageFileName << "\n";
}
