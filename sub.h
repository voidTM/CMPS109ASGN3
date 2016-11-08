#ifndef SUB
#define SUB

#include "instruction.h"
#include "numeric.h"
#include "real.h"

using namespace std;

class Sub : public Instruction{

public:

	Sub(Machine * machine);
	Sub(Machine * machine, int lineNumber);

	Instruction * clone(vector<char*> & argv, int lineNumber);

	void initialize (vector<char*> & argv);

	int execute();

	virtual ~Sub();
};

#endif /* SUB */
