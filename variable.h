#ifndef VARIABLES
#define VARIABLES

#include <string>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

class MClass{
	protected:
		//string name;
		//string type;
		auto value;
	public:
		Variable(); //Constructor
		virtual void initialize (char* token) = 0;
		auto getValue() = 0;
		virtual void setValue(auto) = 0;
		virtual Variable* clone(vector<char*> argv) = 0;
		virtual ~Variable();
};

extern map<string, Variable> varTable;
map<string, Variable> varTable;

#endif