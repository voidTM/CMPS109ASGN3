#ifndef THREADBEGIN
#define THREADBEGIN

#include <pthread.h>
#include "instruction.h"

using namespace std;

class ThreadBegin : public Instruction {
private:
	int beginInstIdx;
	int endInstIdx;
	pthread_t pthread;

public:
	// constructor
	ThreadBegin(Machine * machine);
	ThreadBegin(Machine * machine, int lineNumber);

	// clone object
	Instruction * clone(vector<char*> & argv, int lineNumber);
	
	// initialize and parse with the provided parameters
	void initialize (vector<char*> & argv);

	// execute the instruction with the provided parameters
	int execute();
	
	void setBeginInstIdx(int val);
	
	void setEndInstIdx(int val);
	
	int getBeginInstIdx();
	
	static void * runThread(void * threadBeginObject);

	// destructor
	virtual ~ThreadBegin();
};

#endif /* THREADBEGIN */

