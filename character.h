#ifndef CHARACTER
#define CHARACTER

#include <string>
#include <sstream>

#include "identifier.h"

using namespace std;

class Character: public Identifier{
	private:
		char value;
	public:

		// Constructor
		Real(); 
		Real(char val);

		// Method
		void initialize (char* token);
		Identifier* clone(vector<char*> argv);

		// Destructor
		virtual ~Real();
};

#endif