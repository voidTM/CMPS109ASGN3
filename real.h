#ifndef REALNUMBER
#define REALNUMBER

#include <string>
#include <sstream>

using namespace std;

class Real: public Identifier{
	protected:
		double value;
	public:

		// Constructor
		Real(); 
		Real(double val);
		// Method
		//double getValue();
		auto getValue();
		void setValue(auto);
		void initialize (char* token);
		Identifier* clone(vector<char*> argv);

		// Destructor
		virtual ~Numeric();
};

#endif