#ifndef NUMERIC
#define NUMERIC

#include <string>
#include <sstream>

#include "identifier.h"

using namespace std;

class Numeric: public Identifier{
	private:
		int value;
	public:
		// Constructor
		Numeric(); 
		Numeric(int val);
		// Method
		void initialize (char* token);
		Identifier* clone(vector<char*> argv);

		// Destructor
		virtual ~Numeric();
};

#endif