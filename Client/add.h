#ifndef ADD
#define ADD

#include "instruction.h"
#include "numeric.h"
#include "real.h"

using namespace std;

class Add : public Instruction {

public:
	// constructor
	Add(Parser* parser);
	Add(Parser* parser, int lineNumber);

	// clone object
	Instruction * clone(vector<char*> & argv, int lineNumber);

	// initialize and parse with the provided parameters
	void initialize (vector<char*> & argv);

	// execute the instruction with the provided parameters
	int execute();

	// destructor
	virtual ~Add();
};

#endif /* ADD */
