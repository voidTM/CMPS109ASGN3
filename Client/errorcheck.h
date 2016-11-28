#ifndef MACHINE
#define MACHINE

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include "identifier.h"
#include "numeric.h"
#include "real.h"
#include "character.h"
#include "mis_string.h"

using namespace std;

class Instruction;

class ErrorChecker {

	private:
		vector<Instruction*> instructions; // a list of all the existing instructions
		map<string,Identifier*> identifiers; // a map of all the existing identifiers (a.k.a variables)
		map<string,Identifier*> typeSet; // a map of identifiers' prototypes that are used for cloning
		map<string,Instruction*> instSet; // a map of instructions' prototypes that are used for cloning
		map<string,int> labels; // a map of defined labels

		string programFileName; // the filename for the MIS program

		string ReplaceAll(string str, const string& from, const string& to); // replaces all occurrences of a string inside of another string

	public:
	// constructor
	ErrorChecker();
	ErrorChecker(string programFileName);

	// write the error message to the error file (.err)
	void reportError(string errMsg , int lineNumber = -1 , bool terminate = false);

	// Continuously parse an mis file
	void parseFile();

	// Parses one line for an given variable
		void parseVar(stringstream &line, int lineNumber);

	// Parses one line for an given instruction
		void parseInst(string command, stringstream &argv, int lineNumber);


	// parses line for every token/argument
	vector<char*> parseLine (stringstream &line);
	bool getErrorStatus();
	void trimWhitespace(string& str); // trims whitespace

    // destructor
	virtual ~Parser();
};

#endif /* MACHINE */
