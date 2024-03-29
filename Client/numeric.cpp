#include "stdio.h"
#include <iostream>

#include "numeric.h"

using namespace std;

Numeric::Numeric(){
	value = 0;
}

Numeric::Numeric(int val){
	value = val;
}

Numeric::Numeric(const Numeric &copy){
	this->value = copy.value;
}

void Numeric::initialize(char* token){
	int val;
	int t;
	t = sscanf(token, "%d", &val);
	if(t == 1)
		value = val;
	// else throw error
}

Identifier* Numeric::clone(vector<char*> argv){
	if (argv.size() > 1){
		// Throw error due to in proper amount of
		// values
		reportError("Invalid argument to Numeric");
		return NULL;
		//exit(1);
	}

	char* tok = argv[0];
	//cout << tok << endl;
	Numeric* number = new Numeric();
	number->initialize(tok);

	return number;
}

int Numeric::getValue(){
	return value;
}

void Numeric::setValue(int val){
	value = val;
}

string Numeric::getStrValue(){ return to_string(value); }

string Numeric::type() {return "NUMERIC"; }
string Numeric::getType() {return "NUMERIC"; }

Numeric::~Numeric(){}