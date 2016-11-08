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
		String(int size);

		// Method
		void initialize (char* token);
		Identifier* clone(vector<char*> argv);

		char* getValue();
		static string type();
		void setValue(char* val);
		// Destructor
		virtual ~String();
};

#endif