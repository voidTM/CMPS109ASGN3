#ifndef REALNUMBER
#define REALNUMBER

#include <string>
#include <sstream>

#include "identifier.h"

using namespace std;

class Real: public Identifier{
	protected:
		double value;
	public:

		// Constructor
		Real(); 
		Real(double val);
		Real(const Real &copy);

		// Method
		//double getValue();
		double getValue();
		void setValue(double val);
		
		void initialize (char* token);
		Identifier* clone(vector<char*> argv);

		static string type();
		string getType();
		string getStrValue();

		// Destructor
		virtual ~Real();
};

#endif