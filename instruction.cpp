#include "instruction.h"
#include "machine.h"

Instruction::Instruction() {}

Instruction::Instruction(Machine * machine) : machine(machine) {}

Instruction::Instruction(Machine * machine, int lineNumber) : machine(machine) , lineNumber(lineNumber) {}

Instruction::~Instruction() {}

Identifier* Instruction::identifyConstant(char* constant){
	int a;
	int p;
	double b;
	char c;
	string type;
	Identifier* obj = NULL;

	if(sscanf(constant,"%d.%d", &a, &p) == 2 &&sscanf(constant, "%lf", &b)){
		obj = new Real(b);
	}
	else if(sscanf(constant, "%d", &a)){
		obj = new Numeric(a);
	}
	else if(sscanf(constant, "%c", &c)){
		obj = new Character(c);
	}
	else {
		int length = strlen(constant);
		if(constant[0] == '\"' && constant[length - 1] == '\"')
		{
			// copy without first and last value
			// removes double quotes
			string val = constant;
			val.erase(val.begin());
			val.erase(val.end());
			obj = new String(val);
		}
	}
	cout << obj->getStrValue() << endl;

	return obj;
}

void Instruction::reportError(string errMsg , int lineNumber /*= -1*/ , bool exit /*= false*/) {
	machine->reportError(errMsg, lineNumber, exit);
	machine->setParseError(true);
}

int Instruction::getLineNumber() {
	return lineNumber;
}
