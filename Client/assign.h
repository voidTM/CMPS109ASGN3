#ifndef ASSIGN
#define ASSIGN

#include "instruction.h"
#include "identifier.h"
#include "numeric.h"
#include "real.h"
#include "character.h"
#include "mis_string.h"
//#include <regex>

using namespace std;

class Assign : public Instruction {

	public:
	//Add();

	Assign(ErrorChecker* parser);
	Assign(ErrorChecker* parser, int lineNumber);

	Instruction * clone(vector<char*> & argv, int lineNumber);

	void initialize (vector<char*> & argv);
	int execute();

	//Identifier* identifyConstant(char* constant);

	virtual ~Assign();
};

#endif