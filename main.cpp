#include "Notes.h"
#include "Relations.h"
using namespace std;

int main() {
	try {
        /**********CRÉATION D'UN NOTESMANAGER*********/
        NotesManager& nm=NotesManager::getManager();


        /**********AJOUT DE NOTES AU NOTESMANAGER*****/
        nm.addArticle("Title Article","Text");
        nm.addImage("Title Image","Description","image filename");


        /********AFFICHAGE DES NOTES AJOUTÉES*********/
        cout<<nm;


        /*********CRÉATION D'UN RELATIONSMANAGER******/
        RelationsManager& rm=RelationsManager::getManager();


        /**AJOUT D'UNE RELATION AU RELATIONSMANAGER***/
        rm.addRelation("married","in couple",0);


        /********CRÉATION D'UN COUPLE DE NOTES********/
        /********ET AJOUT DANS UNE RELATION**********/

        rm.addCouple(0,*(nm.getM_notes()[0]),*(nm.getM_notes()[1]),"just married");
        rm.getM_relations()[0]->show();


        /********SUPPRESSION D'UNE NOTE**************/

        /**D'ABORD SUPPRESSION DES COUPLES OÙ ELLE EST*/
                     /**IMPLIQUÉE*****/
        //rm.removeNote(nm.getM_notes()[0]);

        /*********ENSUITE DANS NOTESMANAGER**********/
        /*nm.removeNote(nm.getM_notes()[0]);
        cout<<"******************************************"<<endl;
        cout<<nm;
        rm.getM_relations()[0]->show();*/
	}

	catch(Exception& e){
		std::cout<<e.getInfo()<<"\n";
	}

	return 0;
}
