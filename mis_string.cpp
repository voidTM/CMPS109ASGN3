#include <iostream>

#include "mis_string.h"

// Constructors
String::String(){
	value = new char[256];
	size = 256;
}

String::String(string val){
	value = strdup(val.c_str());
	size = val.size();
	//value = val;
}

String::String(const String &copy){
	value = strdup(copy.value);
	this->size = size;
}

String::String(int size){
	value = new char[size];
	this->size = size;
}
//Methods

void String::initialize(char* token){
	int t;
	int length;
	int charVal;
	string val = token;
	length = strlen(token);
	cout << "token initialize" << val << endl; 
	if(val[0] == '\"' && val[length - 1] == '\"')
	{
		t = 1;
		// copy without first and last value
		// removes double quotes
		val = token;
		val.erase(val.begin());
		val.erase(val.end() -1);
	}

	//cout << value << endl;

	if(t == 1)
		value = strdup(val.c_str());
}

Identifier* String::clone(vector<char*> argv){
	//char* tokSize;
	char* tokVal;
	int tokSize = 256;
	String* chr;
	if (argv.size() > 2){
		// Throw error due to in proper amount of
		// values
		cerr << "Invalid value to Character" << endl;
		exit(1);
	}
	else if(argv.size() == 2){
		// check to see if there are 2 arguments for the 
		// class this would mean first one should be the size
		// of the string
		//*tokSize = argv[0];
		tokVal = argv[1];
		cout << "tokVal" << tokVal << endl;
		sscanf(argv[0], " %d", &tokSize); //get sizes
	}
	else{
		// Assume there is only 1 argument

		tokVal = argv[0];
		cout << "tokVal" << tokVal << endl;

		//*chr = new String();
	}

	chr = new String(tokSize);
	chr->initialize(tokVal);

	return chr;
}

char* String::getValue(){
	return value;
}

void String::setValue(char* val){
	value = val;
}

string String::getStrValue(){ return value; }

string String::type(){ return "STRING"; }
string String::getType(){ return "STRING"; }

// Destructor
String::~String(){}