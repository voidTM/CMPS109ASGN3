#include "mul.h"
#include <string>
#include <iostream>

// constructor
Mul::Mul (ErrorChecker* parser) {this->parser = parser;}
// constructor
Mul::Mul (ErrorChecker* parser, int lineNumber) {
	this->parser = parser;
	this->lineNumber = lineNumber;
}
// destructor
Mul::~Mul() {}

// clone an object of the same type
Instruction * Mul::clone(vector<char*> & argv, int lineNumber) {
	Mul * mul = new Mul(this->parser, lineNumber);
	mul->initialize(argv);
	return mul;
}

// initialize and parse the instruction with the provided parameters
void Mul::initialize(vector<char*> & argv) {

	double val1; int val2;

	// check the number of parameters
	int argsCount = argv.size();
	if (argsCount < 3 || argsCount > 13)
	{
		reportError("The number of arguments for MUL should be between 3 and 13.", lineNumber); // report error
	}

	char* token;
	auto identifiers = parser->getidentifiers();
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

// execute the instruction
int Mul::execute() {

	auto identifiers = parser->getidentifiers();

	// calculate the multiplication result
	double result = 1;
	for (int i=1; i<args.size(); i++)
	{
		// if the argument is a variable
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
		else  // if the argument is a constant
			result *= atof(args[i].c_str());
	}

	// store the result in the first argument
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
