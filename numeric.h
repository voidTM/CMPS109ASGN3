#ifndef NUMERIC
#define NUMERIC

#include <string>
#include <sstream>

#include "variable.h"
#include "arithmetic.h"

using namespace std;

class Numeric: public MClass{
	private:
		int value;
	public:
		// Constructor
		Numeric(); 
		Numeric(int val);
		// Method
		void initialize (char* token);
		Variable* clone(stringstream & ss) = 0;

		// Destructor
		virtual ~Numeric();
};

#endif