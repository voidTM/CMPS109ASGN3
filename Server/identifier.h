#ifndef IDENTIFIER
#define IDENTIFIER

#include <string>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

class Identifier{
	protected:
		//string name;
		//string type;
		//auto value;

	public:
		Identifier(){}; //Constructor

		virtual void initialize (char* token) = 0;

		virtual Identifier* clone(vector<char*> argv) = 0;

		virtual string getType() = 0; //Returns the class type for an object

		virtual string getStrValue() = 0; //Converts the value of an object into a string and return it

		virtual ~Identifier(){}; // Destructor
};

#endif
