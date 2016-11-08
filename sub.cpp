#include "sub.h"
#include <string>
#include <iostream>

Sub::Sub (Machine * machine) {this->machine = machine;}

Sub::Sub (Machine * machine, int lineNumber) {
	this->machine = machine;
	this->lineNumber = lineNumber;
}

Sub::~Sub() {}

Instruction * Sub::clone(vector<char*> & argv, int lineNumber) {
	Sub * sub = new Sub(this->machine, lineNumber);
	sub->initialize(argv);
	return sub;
}

void Sub::initialize(vector<char*> & argv) {

	double val1; int val2;
	int argsCount = argv.size();
	if (argsCount != 3)
	{
		reportError("The number of arguments for SUB should be 3.", lineNumber); // report error
	}

	for(int i=0; i<argsCount; i++)
	{
		auto identifiers = machine->getidentifiers();
		char* token = argv[i];

		// check the first argument: it should be a valid variable and of type Numeric or Real
		if (i == 0)
		{
			// check if it is a variable
			if (token[0] == '$')
			{
				if (identifiers->find(token) == identifiers->end()) //check if the variable name is not found in the variable list
				{
					reportError("The variable " + string(token) + " not found.", lineNumber); // report error
				}
				else
				{
					// check if the variable is of type Numeric or Real
					if ((*identifiers)[token]->getType() != Real::type() && (*identifiers)[token]->getType() != Numeric::type())
					{
						reportError("The variable " + string(token) + " should be of type Numeric or Real.", lineNumber); // report error
					}
				}
			}
			else
			{
				reportError(string(token) + " is not a variable.", lineNumber); // report error
			}
		}
		else
		{
			// check if it is a variable
			if (token[0] == '$')
			{
				if (identifiers->find(token) == identifiers->end()) //check if the variable name is not found in the variable list
				{
					reportError("The variable " + string(token) + " not found.", lineNumber); // report error
				}
				else
				{
					// check if the variable is of type Numeric or Real
					if ((*identifiers)[token]->getType() != Real::type() && (*identifiers)[token]->getType() != Numeric::type())
					{
						reportError("The variable " + string(token) + " should be of type Numeric or Real.", lineNumber); // report error
					}
				}
			}
			// check if the constant (literal) is of type Numeric or Real
			else if ((sscanf(token, "%lf", &val1) != 1) and (sscanf(token, "%d", &val2) != 1))
			{
				reportError(string(token) + " is not of type Numeric or Real.", lineNumber); // report error
			}
		}

		args.push_back(token);
	}
}

int Sub::execute() {

	auto identifiers = machine->getidentifiers();
	double result = 0;

	// retrieve the value of the second argument and add it to the result
	if (args[1][0] == '$') // if the second argument is a variable
	{
		Identifier * ident = (*identifiers)[args[1]];
		if (ident->getType() == Numeric::type())
		{
			Numeric * num = (Numeric*)ident;
			result += num->getValue();
		}
		else
		{
			Real * real = (Real*)ident;
			result += real->getValue();
		}
	}
	else // if the second argument is a constant
		result += atof(args[1].c_str());

	// retrieve the value of the third argument and deduct it from the result
	if (args[2][0] == '$') // if the third argument is a variable
	{
		Identifier * ident = (*identifiers)[args[2]];
		if (ident->getType() == Numeric::type())
		{
			Numeric * num = (Numeric*)ident;
			result -= num->getValue();
		}
		else
		{
			Real * real = (Real*)ident;
			result -= real->getValue();
		}
	}
	else // if the third argument is a constant
		result -= atof(args[2].c_str());

	// save the results in the first variable
	Identifier * ident0 = (*identifiers)[args[0]];
	if (ident0->getType() == Numeric::type())
	{
		Numeric * num = (Numeric*)ident0;
		num->setValue(result);
	}
	else
	{
		Real * real = (Real*)ident0;
		real->setValue(result);
	}

	return -1;
}
