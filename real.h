#ifndef REALNUMBER
#define REALNUMBER

#include <string>
#include <sstream>

using namespace std;

class Real: public Variable{
	protected:
		double value;
	public:

		// Constructor
		Real(); 
		Real(double val);
		// Method
		double getValue();
		void initialize (char* token);
		Variable* clone(stringstream & ss);

		// Destructor
		virtual ~Numeric();
};

#endif