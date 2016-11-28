#include "stdio.h"
#include <iostream>

#include "numeric.h"

using namespace std;

Numeric::Numeric(){
	value = 0;
	error = false;
}

Numeric::Numeric(int val){
	value = val;
}

Numeric::Numeric(const Numeric &copy){
	this->value = copy.value;
}

void Numeric::initialize(char* token, string& errors){
	int val;
	int t;
	t = sscanf(token, "%d", &val);
	if(t == 1)
		value = val;
	
	else{
		error = true;
		errors += "Argument is not a valid String\n";
	}	// else throw error
}

Identifier* Numeric::clone(vector<char*> argv, string& errors){
	if (argv.size() > 1){
		// report error due to in proper amount of 
		// values
		errors += "Invalid argument to Numeric\n";
		return NULL;
	}

	char* tok = argv[0];
	//cout << tok << endl;
	Numeric* number = new Numeric();
	number->initialize(tok, errors);
	if(error)
		return NULL;

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
