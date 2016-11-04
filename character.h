#ifndef CHARACTER
#define CHARACTER

#include <string>
#include <sstream>

#include "variable.h"

using namespace std;

class Character: public Letter{
	private:
		char value;
	public:

		// Constructor
		Real(); 
		Real(char val);

		// Method
		void initialize (stringstream & ss) = 0;
		Variable* clone(stringstream & ss) = 0;

		// Destructor
		virtual ~Real();
};

#endif