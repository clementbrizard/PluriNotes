#ifndef EXCEPTION_H_INCLUDED
#define EXCEPTION_H_INCLUDED
#include <iostream>
#include <string>
#include "timing.h"
using namespace std;

class Exception{
private:
	string info;
public:
	Exception(const string& message) : info(message){}
	string getInfo() const { return info; }
};

#endif // EXCEPTION_H_INCLUDED
