#ifndef JUMPS
#define JUMPS

#include "instruction.h"
#include "identifier.h"
#include "numeric.h"
#include "real.h"
#include "character.h"
#include "mis_string.h"

using namespace std;

class Jump : public Instruction {

	public:
	//Add();

	Jump(Machine * machine);
	Jump(Machine * machine, int lineNumber);

	virtual Instruction * clone(vector<char*> & argv, int lineNumber);

	virtual void initialize (vector<char*> & argv);
	virtual int execute();

	virtual ~Jump();
};

#endif