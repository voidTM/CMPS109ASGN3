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
		//auto getValue() = 0;
		//virtual void setValue(auto) = 0;
		virtual Identifier* clone(vector<char*> argv) = 0;
		virtual ~Identifier(){};
};

#endif