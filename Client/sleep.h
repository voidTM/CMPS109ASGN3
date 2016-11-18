#ifndef SLEEPTIMER
#define SLEEPTIMER

#include "instruction.h"
#include "identifier.h"
#include "numeric.h"
#include "real.h"
#include "character.h"
#include "mis_string.h"
#include "unistd.h"

using namespace std;

class Sleep : public Instruction {

	public:
	//Add();

	Sleep(Parser* parser);
	Sleep(Parser* parser, int lineNumber);

	Instruction * clone(vector<char*> & argv, int lineNumber);

	void initialize (vector<char*> & argv);
	int execute();

	virtual ~Sleep();
};

#endif