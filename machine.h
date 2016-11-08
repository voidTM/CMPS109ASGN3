#ifndef MACHINE
#define MACHINE

#include <map>
#include <string>
#include <fstream>
#include <iostream>
//#include "instruction.h"
#include "identifier.h"
#include "numeric.h"
#include "real.h"
#include "character.h"
#include "mis_string.h"
//#include "add.h"

using namespace std;

class Instruction;

class Machine {

private:
	vector<Instruction*> instructions;
	map<string,Identifier*> identifiers;
	map<string,Identifier*> typeSet;
	map<string,Instruction*> instSet;
	map<string,int> labels;

	string programFileName;
	string errorFileName;
	string outputFileName;

	// becomes true if error happens during parsing
	bool parseError;

	void parseFile();

	void parseVar(stringstream &line, int lineNumber);

	void parseInst(string command, stringstream &argv, int lineNumber);

public:
	Machine();
	Machine(string programFileName, string errorFileName, string outputFileName);

	void run();

	void reportError(string errMsg , int lineNumber = -1 , bool terminate = false);

	void setParseError(bool val);

	map<string,Identifier*> * getidentifiers();
	map<string,Identifier*> * getTypes();
	map<string, int> *  getLabels();
	vector<char*> parseLine (stringstream &line);
	void trimWhitespace(string& str);

	virtual ~Machine();
};

#endif /* MACHINE */
