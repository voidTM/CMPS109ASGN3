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
		Character(); 
		Character(char val);

		// Method
		void initialize (char* token);
		Identifier* clone(vector<char*> argv);

		char getValue();
		// Destructor
		virtual ~Character();
};

#endif