#include "MIS_Thread.h"

MIS_Thread::MIS_Thread(vector*<instructions> threadInstr){
  threadInstructions = threadInstr;
}

void MIS_Thread::threadMainBody(void * arg){
  // runbased off of instructionthread
  // Include mutex somehow?
  // currently does not check for bounded buffers.
  int retval, currentInstIdx = 0;
  try
  {
    while (currentInstIdx < instructions.size())
    {
      // execute the current instruction
      retval = threadInstructions[currentInstIdx]->execute();

      if (retval == -1)
        currentInstIdx++; // if it was a non-jump instructions, then go to the next instruction
      else
        currentInstIdx = retval; // if it was a jump instruction, then jump to that specified point
    }
  }

  catch (int e)
  {
    int lineNumber = instructions[currentInstIdx]->getLineNumber();
    reportError("An error was generated while executing the line. Execution of the program terminated." , lineNumber); //, true);
    exit(1);
  }
}
