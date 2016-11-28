#include "identifier.h"

//Identifier::Identifier(Machine * machine) : machine(machine) {}

Identifier::Identifier() {}

void Identifier::reportError(string errMsg , int lineNumber /* = -1 */) {
	error = true;
	//localerrors += errMsg;
    //ErrorBuffer::reportError(errMsg, lineNumber);
}

