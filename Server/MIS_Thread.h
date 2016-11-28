#ifndef MIS_THREAD
#define MIS_THREAD

#include "Thread.h"
#include "instruction.h"
#include "identifier.h"


class MIS_Thread: public Thread{
  private:
    vector<Instruction*> threadInstructions;

  public:
    MIS_Thread(vector<Instruction*>);
    void * threadMainBody (void * arg);
    virtual ~MIS_Thread();
};

#endif
