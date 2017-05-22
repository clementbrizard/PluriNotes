#include "Notes.h"

int main() {
	try {
        NotesManager& m=NotesManager::getManager();
        m.addArticle("idArticle","title","text");
        m.addImage("idImage","title","description","imageFileName");
        cout<<m;
	}
	catch(NotesException& e){
		std::cout<<e.getInfo()<<"\n";
	}

	return 0;
}
