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
	t = sscanf(token, "%f", &val);
	if(t == 1)
		value = val;
	//else throw error
}

Variable* Real::clone(stringstream &ss){
	string field = "";
	char* value;
	int 
	getline(ss, field, ',');
	value = strdup(field.c_str());

	Real* realValue = new Real();
	realValue->initialize(value);
	return realValue;
}