#include <iostream>

#include "character.h"

// Constructors
Character::Character(){
	value = ' ';
	error = false;
}

Character::Character(char val){
	value = val;
}

Character::Character(const Character &copy){
	value = copy.value;
}

//Methods

void Character::initialize(char* token){
	int val;
	int t;
	// check for single quotes at end of quotation
	//cout << "token = " << token << endl;
	string init = token;
	//init->
	//if(val[0] == '\'' && val[length - 1] == '\'')
	t = sscanf(token, " \'%d\'", &val);

	//cout << "val = " << val << endl;
	if(t == 1)
		value = val;
	/*else
		reportError("Argument is not a valid Character");
	*/
}

Identifier* Character::clone(vector<char*> argv){
	if (argv.size() > 1){
		// Throw error due to in proper amount of
		// values
		reportError("Invalid number of arguments to Character");
		return NULL;
	}

	char* tok = argv[0];

	Character* chr = new Character();
	chr->initialize(tok);
	if(error)
		return NULL;

	return chr;
}

char Character::getValue(){
	return value;
}

string Character::getStrValue(){
	string s;
	s.push_back(value);
	return s;
}


void Character::setValue(char val){
	value = val;
}

string Character::type(){ return "CHAR"; }
string Character::getType(){ return "CHAR"; }

// Destructor
Character::~Character(){}
