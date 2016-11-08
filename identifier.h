#ifndef IDENTIFIER
#define IDENTIFIER

#include <string>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

class Identifier{
	protected:
	public:
		Identifier(){}; //Constructor

		virtual void initialize (char* token) = 0;
		virtual string type();
		virtual Identifier* clone(vector<char*> argv) = 0;
		virtual ~Identifier(){};
};

#endif