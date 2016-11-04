#ifndef MIS_STRING
#define MIS_STRING

#include <string>
#include <sstream>
#include <cstring>

#include "variable.h"

using namespace std;

class String: public Variable{
	private:
		char* value;
		int size;
	public:

		// Constructor
		String();
		String(string val);
		String(string val, int size);
		String(int size);

		// Method
		void initialize (char* token);
		Variable* clone(stringstream & ss) = 0;

		// Destructor
		virtual ~String();
};

#endif