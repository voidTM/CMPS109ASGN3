#include "identifier.h"

void Identifier::reportError(string errMsg , int lineNumber /* = -1 */) {
    ErrorBuffer::reportError(errMsg, lineNumber);
}

