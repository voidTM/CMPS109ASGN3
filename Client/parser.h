#ifndef PARSER
#define PARSER

#include <fstream>
#include <iostream>

#include "includeMIS.h"

class Parser{
	private:
		//file object
		map<string,Identifier*> identifiers; // a map of all the existing identifiers (a.k.a variables)
		map<string,Identifier*> typeSet; // a map of identifiers' prototypes that are used for cloning
		//map<string,Instruction*> instSet; // a map of instructions' prototypes that are used for cloning
		char* buffer;
		bool parseError;

		// Parses one line for an given variable
		void parseVar(stringstream &line, int lineNumber);

		// Parses one line for an given instruction
		void parseInst(string command, stringstream &argv, int lineNumber);
		// Maybe unneeded for parser since no formating string is required
		string ReplaceAll(string str, const string& from, const string& to);
	public:
		//Constructor
		Parser();

		void parseFile(ifstream file);

		map<string,Identifier*> * getidentifiers(); // get a pointer to the map of existing identifiers
		map<string,Identifier*> * getTypes(); // get a pointer to the map of identifiers' prototypes (typeSet)
		map<string, int> *  getLabels(); // get a pointer to the map of existing labels

		// parses line for every token/argument
		vector<char*> parseLine (stringstream &line);
		void trimWhitespace(string& str); // trims whitespace

		// Destructor
		~Parser();
};

#endif