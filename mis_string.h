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
		String(const String &copy);

		// Method
		void initialize (char* token);
		Identifier* clone(vector<char*> argv);

		char* getValue();
		void setValue(char* val);
		string getType();
		static string type();
		string getStrValue();


		// Destructor
		virtual ~String();
};

#endif