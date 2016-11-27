#include "error_buffer.h"

ErrorBuffer::ErrorBuffer() {
    errorBuffer = "";
}

ErrorBuffer::~ErrorBuffer() {}

void ErrorBuffer::reportError(string errorMsg, int lineNumber /*= -1*/) {
	string msg = errorMsg + "\n";
	if (lineNumber > -1)
		msg = "Error in line " + to_string(lineNumber) + ": " + msg;
		
	errorBuffer += msg;
}

string ErrorBuffer::getErrorBuffer() {
    return errorBuffer;
}

void ErrorBuffer::emptyBuffer() {
    errorBuffer = "";
}

