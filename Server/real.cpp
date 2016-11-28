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

void Real::initialize (char* token, string& errors){
	double val;
	int t;
	t = sscanf(token, "%lf", &val);
	if(t == 1)
		value = val;
	else{
		error = true;
		errors += "Argument is not a valid Real\n";
	}
	//else throw error*/
}

Identifier* Real::clone(vector<char*> argv, string& errors){

	if (argv.size() > 1){
		// Throw error due to in proper amount of
		// values
		errors += "Invalid number of arguments to Real\n";
		error = true;
		//reportError("Invalid number of arguments to Real");
		return NULL;
	}

	char* tok = argv[0];
	Real* realValue = new Real();
	realValue->initialize(tok, errors);
	if(error)
		return NULL;
	
	return realValue;
}

string Real::type(){ return "REAL"; }
string Real::getType(){ return "REAL"; }

string Real::getStrValue(){ return to_string(value); }

Real::~Real(){}
