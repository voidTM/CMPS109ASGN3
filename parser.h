#ifndef PARSER
#define PARSER

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <ctype.h>
#include <fstream>

#include "variable.h"
#include "numeric.h"
#include "real.h"
#include "character.h"
#include "mis_string.h"

using namespace std;
class parser{
	private:
		map<string, Variable> varSet;
		map<string, Instruction> instSet;

	public:
		// Constructor
		Parser();

		// Methods
		parseFile(File*);
		parseVar(stringstream &line);
		parseInst(string command, stringstream &argv);

		// Destructor
		~Parser();
};
#endif