#include "Notes.h"

int main() {
	try {
        NotesManager& m=NotesManager::getManager();
        m.addArticle("ta mère","la catin","des iles");
        m.addImage("ton pere","le roi","des cons","de France");
        cout<<m;
	}
	catch(NotesException& e){
		std::cout<<e.getInfo()<<"\n";
	}
	system("pause");
	return 0;
}
