#include <iostream>
#include "Note.h"

using namespace std;

int main()
{
    Audio i(1,"Image", Date(20,5,2017), Date(20,5,2017), "description", "image.png");
    i.show();
    return 0;
}
