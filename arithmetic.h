#ifndef ARITHMETIC
#define ARITHMETIC

#include <string>
#include <sstream>

#include "variable.h"

using namespace std;

class Arithmetic: public Variable{
	protected:
	public:
		Variable(); //Constructor
		virtual void initialize (stringstream & ss) = 0;
		virtual Variable* clone(stringstream & ss) = 0;
		virtual ~Arithmetic();
};

#endif