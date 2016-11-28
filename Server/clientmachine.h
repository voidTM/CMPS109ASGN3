#ifndef MISCLIENTMACHINE
#define MISCLIENTMACHINE

#include "machine.h"
#include "instruction.h"

class Instruction;

class ClientMachine : public Machine{
	private:
		string programFileName;
	public:
		//ClientMachine();
		ClientMachine(string programFileName);

		void readFile();
		bool getErrorStatus();
		bool checkError();
		string getErrorMsg();
		string getOutputMsg();
		void executeInstructions(int startInstIdx = 0);
		virtual ~ClientMachine();
};

#endif