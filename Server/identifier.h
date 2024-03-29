#ifndef IDENTIFIER
#define IDENTIFIER

#include <string>
#include <sstream>
#include <map>
#include <vector>
#include "error_buffer.h"
#include <pthread.h>

using namespace std;

class Identifier{
	protected:
		bool error;

	public:
		pthread_mutex_t lock;
		
		Identifier(); //Constructor

		virtual void initialize (char* token, string &errors) = 0;

		virtual Identifier* clone(vector<char*> argv, string& errors) = 0;

		virtual string getType() = 0; //Returns the class type for an object

		virtual string getStrValue() = 0; //Converts the value of an object into a string and return it

		virtual ~Identifier(); // Destructor
		
		// report an error message
    	void reportError(string errMsg , int lineNumber = -1);
};

#endif
