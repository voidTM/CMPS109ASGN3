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
		Character(const Character &copy);

		// Method
		void initialize (char* token, string &errors);
		Identifier* clone(vector<char*> argv, string& errors);
		void setValue(char val);
		static string type();
		string getType();
		string getStrValue();
		char getValue();
		// Destructor
		virtual ~Character();
};

#endif