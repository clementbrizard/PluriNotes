#include <iostream>
#include "plurinotes.cpp"

//Méthode de la classe Date
date::date(int j, int m, int a) : jour(j), mois(m), annee(a) {}
void date::print() const{
    std:cout << jour << "/" << mois << "/" << annee << "\n";
}

//Methodes de la classe Article
//Constructeur & destructeur:
article::article(const string& id, const string& titre, const string& text) : note(id,titre),text(text){}
article::~article() {}

void article::show() const{
    std::cout << "Id de l'article: " << id << "\n";
    std::cout << "Titre de l'article: " << title << "\n";
    std::cout << "Contenu de l'article: " << text << "\n";
}