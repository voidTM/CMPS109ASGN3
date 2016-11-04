#include <iostream>

#include "real.h"

using namespace std;

// Constructor

Real::Real():Real(0.0){}

Real::Real(double val){
	value = val;
}

double Real::getValue(){
	return value;
}

void Real::initialize (char* token){
	double val;
	int t;
	t = sscanf(token, "%lf", &val);
	if(t == 1)
		value = val;
	//else throw error
}

Identifier* Real::clone(vector<char*> argv){

	if (argv.size() > 1){
		// Throw error due to in proper amount of
		// values
		cerr << "Invalid argument to Real" << endl;
		exit(1);
	}

	char* tok = argv[0];
	Real* realValue = new Real();
	realValue->initialize(tok);

	return realValue;
}

Real::~Real(){}