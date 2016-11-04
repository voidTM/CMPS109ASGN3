#ifndef CHARACTER
#define CHARACTER

#include <string>
#include <sstream>

#include "variable.h"

using namespace std;

class Character: public Identifier{
	private:
		char value;
	public:

		// Constructor
		Real(); 
		Real(char val);

		// Method
		void initialize (char* token) = 0;
		Identifier* clone(vector<char*> argv);

		// Destructor
		virtual ~Real();
};

#endif