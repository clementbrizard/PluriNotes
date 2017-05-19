#include<iostream>
#include"Note.h"
using namespace std;

void Article::show(){
    cout << "Id : " << getId() << "\n";
    cout << "Titre : " << getTitle() << "\n";
    cout << "Contenu : " << m_text << "\n";
}

void Task::show(){
    cout << "Id : " << getId() << "\n";
    cout << "Titre: " << getTitle() << "\n";
    if (m_priority != 0) cout << "Priorité :" << m_priority;
    //if(m_deadline != Date(0,0,0)) cout << "Deadline : "<<m_deadline; reféfinir l'opérateur différent pour la classe Date
}

void Media::show(){
    cout << "Id : " << getId() << "\n";
    cout << "Titre: " << getTitle() << "\n";
    cout << "Description: " << m_description << "\n";
    cout << "Titre: " << m_imageFileName << "\n";
}
