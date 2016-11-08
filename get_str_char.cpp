#include "get_str_char.h"

GetStrChar::GetStrChar (Machine * machine) {this->machine = machine;}

GetStrChar::GetStrChar (Machine * machine, int lineNumber) {
	this->machine = machine;
	this->lineNumber = lineNumber;
}

GetStrChar::~GetStrChar() {}

Instruction * GetStrChar::clone(vector<char*> & argv, int lineNumber) {
	GetStrChar * getStrChar = new GetStrChar(this->machine, lineNumber);
	getStrChar->initialize(argv);
	return getStrChar;
}

void GetStrChar::initialize(vector<char*> & argv) {

	int val1; char val2;

	// check the number of arguments
	int argsCount = argv.size();

	if (argsCount != 3)
	{
		reportError("The number of arguments for GET_STR_CHAR should be 3.", lineNumber); // report error
		return;
	}

	auto identifiers = machine->getidentifiers();

	// check the first argument: it should be a valid String variable
	char* token = argv[0];
	if (token[0] == '$') // check if it is a variable
	{
		if (identifiers->find(token) == identifiers->end()) //check if the variable name is not found in the variable list
		{
			reportError("The variable " + string(token) + " not found.", lineNumber); // report error
		}
		else
		{
			// check if the variable is of type String
			if ((*identifiers)[token]->getType() != String::type())
			{
				reportError("The variable " + string(token) + " should be of type STRING.", lineNumber); // report error
			}
		}
	}
	else
	{
		reportError(string(token) + " is not a variable.", lineNumber); // report error
	}
	args.push_back(token);


	// check the second argument: it should be a valid variable or constant of type Numeric
	token = argv[1];
	if (token[0] == '$') // check if it is a variable
	{
		if (identifiers->find(token) == identifiers->end()) //check if the variable name is not found in the variable list
		{
			reportError("The variable " + string(token) + " not found.", lineNumber); // report error
		}
		else
		{
			// check if the variable is of type Numeric
			if ((*identifiers)[token]->getType() != Numeric::type())
			{
				reportError("The variable " + string(token) + " should be of type Numeric.", lineNumber); // report error
			}
		}
	}
	else // if it is a constant, it should be of type Numeric
	{
		if (sscanf(token, "%d", &val1) != 1)
		{
			reportError(string(token) + " is not of type Numeric.", lineNumber); // report error
		}
	}
	args.push_back(token);


	// check the third argument: it should be a valid variable or constant of type Character
	token = argv[2];
	if (token[0] == '$') // check if it is a variable
	{
		if (identifiers->find(token) == identifiers->end()) //check if the variable name is not found in the variable list
		{
			reportError("The variable " + string(token) + " not found.", lineNumber); // report error
		}
		else
		{
			// check if the variable is of type Character
			if ((*identifiers)[token]->getType() != Character::type())
			{
				reportError("The variable " + string(token) + " should be of type Character.", lineNumber); // report error
			}
		}
	}
	else // if it is a constant, it should be of type Character
	{
		reportError(string(token) + " is not a variable." , lineNumber);

	}
	args.push_back(token);
}

int GetStrChar::execute() {

	auto identifiers = machine->getidentifiers();
	Identifier * ident = (*identifiers)[args[0]];
	String * sVar = (String*) ident;

	// retrieve the value of the second parameter
	int idx;
	if (args[1][0] == '$')
	{
		ident = (*identifiers)[args[1]];
		Numeric * nVar = (Numeric*) ident;
		idx = nVar->getValue();
	}
	else
	{
		idx = stoi (args[1]);
	}

	// check index is inside the valid range
	if (idx < 0 || idx >= strlen(sVar->getValue()))
	{
		reportError("Index out of range.", lineNumber, true);
	}

	// retrieve the variable object of the third parameter
	ident = (*identifiers)[args[2]];
	Character * cVar = (Character*) ident;

	// update the character variable with the character at the specified index of the specified string
	char* s = sVar->getValue();
	cVar->setValue(s[idx]);

	return -1;
}
