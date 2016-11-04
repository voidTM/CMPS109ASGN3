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