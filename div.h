#ifndef DIV
#define DIV

#include "instruction.h"
#include "numeric.h"
#include "real.h"

using namespace std;

class Div : public Instruction {

public:
	Div(Machine * machine);
	Div(Machine * machine, int lineNumber);

	Instruction * clone(vector<char*> & argv, int lineNumber);

	void initialize (vector<char*> & argv);

	int execute();

	virtual ~Div();
};

#endif /* DIV */
