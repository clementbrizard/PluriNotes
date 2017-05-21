#include "Notes.h"

int main() {
	try {
        NotesManager& m=NotesManager::getManager();
        m.addArticle("ta mère","","");
        cout<<m;

	}
	catch(NotesException& e){
		std::cout<<e.getInfo()<<"\n";
	}
	system("pause");
	return 0;
}
