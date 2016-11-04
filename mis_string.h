#ifndef MISSTRING
#define MISSTRING

#include <string>
#include <sstream>
#include <cstring>

#include "identifier.h"

using namespace std;

class String: public Identifier{
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
		Identifier* clone(vector<char*> argv);

		// Destructor
		virtual ~String();
};

#endif