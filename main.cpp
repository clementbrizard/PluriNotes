#include "Notes.h"
#include "Relations.h"
using namespace std;

int main() {
	try {
        /**********CRÉATION D'UN NOTESMANAGER*********/
        NotesManager& m=NotesManager::getManager();

        /**********AJOUT DE NOTES AU NOTESMANAGER*****/
        m.addArticle("idArticle1","Title","Text");
        m.addImage("idImage1","Title","Description","image filename");


        /********AFFICHAGE DES NOTES AJOUTÉES*********/
        cout<<m;

        /********CRÉATION D'UN COUPLE DE NOTES********/
        Article a("idArticleEnCouple","Just married","Congrats");
        Image i("idImageEnCouple","Just married","Description of weddings","image of weddings filename");

        Relation married("married","in couple",0);
        married.addCouple("couple1",a,i,"weddings");
        cout<<married;
	}
	catch(Exception& e){
		std::cout<<e.getInfo()<<"\n";
	}

	return 0;
}
