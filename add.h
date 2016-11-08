#ifndef ADD
#define ADD

#include "instruction.h"
#include "numeric.h"
#include "real.h"

using namespace std;

class Add : public Instruction {

public:
	Add(Machine * machine);
	Add(Machine * machine, int lineNumber);

	Instruction * clone(vector<char*> & argv, int lineNumber);

	void initialize (vector<char*> & argv);

	int execute();

	virtual ~Add();
};

#endif /* ADD */
