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

		virtual string getType() = 0;

		virtual string getStrValue() = 0;

		virtual ~Identifier(){};
};

#endif
