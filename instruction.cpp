#include "instruction.h"
#include "machine.h"

Instruction::Instruction() {}

Instruction::Instruction(Machine * machine) : machine(machine) {}

Instruction::Instruction(Machine * machine, int lineNumber) : machine(machine) , lineNumber(lineNumber) {}

Instruction::~Instruction() {}

void Instruction::reportError(string errMsg , int lineNumber /*= -1*/ , bool exit /*= false*/) {
	machine->reportError(errMsg, lineNumber, exit);
	machine->setParseError(true);
}

int Instruction::getLineNumber() {
	return lineNumber;
}
