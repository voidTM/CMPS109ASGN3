#ifndef PARSER
#define PARSER

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <ctype.h>
#include <sstream>
#include <iostream>
#include <cstddef>

#include "identifier.h"
#include "numeric.h"
#include "real.h"
#include "character.h"
#include "mis_string.h"

using namespace std;
class Parser{
	protected:
		map<string, Identifier*> typeSet;
		//map<string, Instruction*> instSet;

		map<string, Identifier*> varMap;
		//vector<Instruction*> instructions;
	public:
		// Constructor
		Parser();

		// Methods
		void parseFile(string filename);
		// unable to return abstact datatypes
		void parseVar(stringstream &line);
		void parseInst(string command, stringstream &argv);
		vector<char*> parseLine (stringstream &argv);

		// helpers
		void trimWhitespace(string& str);
		// Destructor
		~Parser();
};
#endif