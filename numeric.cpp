#include "stdio.h"
#include <iostream>

#include "numeric.h"

using namespace std;

Numeric::Numeric();Numeric(0){}

Numeric::Numeric(int val){
	value = val;
}

void Numeric::initialize(char* token){
	int val;
	int t;
	t = sscanf(token, "%d", &val);
	if(t == 1)
		value = val;
	// else throw error
}

Variable* Numeric::clone(vector<char*> argv){
	if (argv.length() > 1){
		// Throw error due to in proper amount of
		// values
		cerr << "Invalid argument to Numeric" << endl;
		exit(1);
	}

	char* tok = argv[0];
	Numeric* number = new Numeric();
	number->initialize(tok);

	return number;
}