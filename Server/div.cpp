#include "div.h"
#include <string>
#include <iostream>

// constructor
Div::Div (Machine * machine) {this->machine = machine;}

// constructor
Div::Div (Machine * machine, int lineNumber) {
	this->machine = machine;
	this->lineNumber = lineNumber;
}

// destructor
Div::~Div() {}

// clone an object of the same type
Instruction * Div::clone(vector<char*> & argv, int lineNumber) {
	Div * div = new Div(this->machine, lineNumber);
	div->initialize(argv);
	return div;
}

// initialize and parse with provided parameters
void Div::initialize(vector<char*> & argv) {

	double val1; int val2;

	// check the number of parameters
	int argsCount = argv.size();
	if (argsCount != 3)
	{
		reportError("The number of arguments for DIV should be 3.", lineNumber); // report error
		return;
	}

	char* token;
	auto identifiers = machine->getidentifiers();
	for(int i=0; i<argsCount; i++)
	{
		token = argv[i];

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
			// the first argument cannot be constant
			if (i == 0)
			{
				reportError(string(token) + " is not a variable.", lineNumber); // report error
			}
			else if ((sscanf(token, "%lf", &val1) != 1) and (sscanf(token, "%d", &val2) != 1)) // check if the constant is of type Numeric or Real
			{
				reportError(string(token) + " is not of type Numeric or Real.", lineNumber); // report error
			}
		}

		// push the argument to a container
		args.push_back(token);
	}
}

int Div::execute() {

	// a pointer to the map of identifiers
	auto identifiers = machine->getidentifiers();
	double result = 1, denom;
	Identifier * ident = (*identifiers)[args[1]];

	// retrieve the value of the second argument and multiply it to result
	if (args[1][0] == '$') // if the second argument is a variable
	{
		if (ident->getType() == Numeric::type())
		{
			Numeric * num = (Numeric*)ident;
			result *= num->getValue();
		}
		else
		{
			Real * real = (Real*)ident;
			result *= real->getValue();
		}
	}
	else // if the second argument is a constant
		result *= atof(args[1].c_str());

	// retrieve the value of the third argument
	if (args[2][0] == '$') // if the third argument is a variable
	{
		Identifier * ident = (*identifiers)[args[2]];
		if (ident->getType() == Numeric::type())
		{
			Numeric * num = (Numeric*)ident;
			denom = num->getValue();
		}
		else
		{
			Real * real = (Real*)ident;
			denom = real->getValue();
		}
	}
	else // if the third argument is a constant
		denom = atof(args[2].c_str());

	// if the third argument is equal to zero, report occurrence of division-by-zero
	if (denom == 0)
	{
		reportError("Division by zero.", lineNumber); //, true);
		exit(1);
	}
	// else divide result by it
	else
		result = result / denom;

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

	// proceed to the execution of the next instruction
	return -1;
}
