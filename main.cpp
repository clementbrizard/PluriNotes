#include <iostream>
#include "Note.h"
#include "Manager.h"

using namespace std;

int main()
{
    ManagerarticlesManager=Manager::giveInstance();
    articlesManager.freeInstance();
    return 0;
}
