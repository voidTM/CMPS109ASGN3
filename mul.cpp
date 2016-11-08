#include "mul.h"
#include <string>
#include <iostream>

Mul::Mul (Machine * machine) {this->machine = machine;}

Mul::Mul (Machine * machine, int lineNumber) {
	this->machine = machine;
	this->lineNumber = lineNumber;
}

Mul::~Mul() {}

Instruction * Mul::clone(vector<char*> & argv, int lineNumber) {
	Mul * mul = new Mul(this->machine, lineNumber);
	mul->initialize(argv);
	return mul;
}

void Mul::initialize(vector<char*> & argv) {

	double val1; int val2;
	int argsCount = argv.size();
	if (argsCount < 3 || argsCount > 13)
	{
		reportError("The number of arguments for MUL should be between 3 and 13.", lineNumber); // report error
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

int Mul::execute() {

	auto identifiers = machine->getidentifiers();
	double result = 1;
	for (int i=1; i<args.size(); i++)
	{
		// if the argument is a variable retrieve its value
		if (args[i][0] == '$')
		{
			Identifier * ident = (*identifiers)[args[i]];
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
		else
			result *= atof(args[i].c_str());
	}

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
