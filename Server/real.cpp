#include <iostream>

#include "real.h"

using namespace std;

// Constructor

Real::Real():Real(0.0){}

Real::Real(double val){
	value = val;
	error = false;
}

Real::Real(const Real &copy){
	this->value = copy.value;
}

double Real::getValue(){
	return value;
}

void Real::setValue(double val){
	value = val;
}

void Real::initialize (char* token){
	double val;
	int t;
	t = sscanf(token, "%lf", &val);
	if(t == 1)
		value = val;
	/*
	else
		reportError("Argument is not a valid Real");
	//else throw error*/
}

Identifier* Real::clone(vector<char*> argv){

	if (argv.size() > 1){
		// Throw error due to in proper amount of
		// values
		reportError("Invalid number of arguments to Real");
		return NULL;
	}

	char* tok = argv[0];
	Real* realValue = new Real();
	realValue->initialize(tok);
	if(error)
		return NULL;
	return realValue;
}

string Real::type(){ return "REAL"; }
string Real::getType(){ return "REAL"; }

string Real::getStrValue(){ return to_string(value); }

Real::~Real(){}
