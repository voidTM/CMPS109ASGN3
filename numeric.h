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
		Numeric(const Numeric &copy);

		// Method
		void initialize (char* token);
		Identifier* clone(vector<char*> argv);
		int getValue();
		void setValue(int);
		static string type();
		string getType();
		// Destructor
		virtual ~Numeric();
};

#endif