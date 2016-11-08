#ifndef MUL
#define MUL

#include "instruction.h"
#include "numeric.h"
#include "real.h"

using namespace std;

class Mul : public Instruction {

public:
	Mul(Machine * machine);
	Mul(Machine * machine, int lineNumber);

	Instruction * clone(vector<char*> & argv, int lineNumber);

	void initialize (vector<char*> & argv);

	int execute();

	virtual ~Mul();
};

#endif /* MUL */
