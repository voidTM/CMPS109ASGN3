#include "identifier.h"

Identifier::Identifier() {
    pthread_mutex_init(&lock, NULL);
}

Identifier::~Identifier() {
    pthread_mutex_destroy(&lock);
}

void Identifier::reportError(string errMsg , int lineNumber /* = -1 */) {
	error = true;
}

