#include "add.h"
#include <string>
#include <iostream>
#include <typeinfo>

//Add::Add() {}

Add::Add (Machine * machine) {this->machine = machine;}

Add::Add (Machine * machine, int lineNumber) {
	this->machine = machine;
	this->lineNumber = lineNumber;
}

Add::~Add() {}

Instruction * Add::clone(vector<char*> & argv, int lineNumber) {
	Add * add = new Add(this->machine, lineNumber);
	add->initialize(argv);
	return add;
}

void Add::initialize(vector<char*> & argv) {

	//std::regex rr("((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?");
	double val1,val2;

	int argsCount = argv.size();
	if (argsCount < 3 || argsCount > 13)
	{
		reportError("The number of arguments for ADD should be between 3 and 13.", lineNumber); // report error
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
					if (typeid(*((*identifiers)[token])) != typeid(Numeric()) && typeid(*((*identifiers)[token])) != typeid(Real()))
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
					if (typeid(*((*identifiers)[token])) != typeid(Numeric()) && typeid(*((*identifiers)[token])) != typeid(Real()))
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

int Add::execute() {

	auto identifiers = machine->getidentifiers();
	double result = 0;
	for (int i=1; i<args.size(); i++)
	{
		// if the argument is a variable retrieve its value
		if (args[i][0] == '$')
		{
			if (typeid(*((*identifiers)[args[i]])) == typeid(Numeric()))
				result += (dynamic_cast<Numeric*>((*identifiers)[args[i]]))->getValue();
			else
				result += (dynamic_cast<Real*>((*identifiers)[args[i]]))->getValue();
		}
		else
			result += atof(args[i].c_str());
	}

	if (typeid(*((*identifiers)[args[0]])) == typeid(Numeric()))
		(dynamic_cast<Numeric*>((*identifiers)[args[0]]))->setValue(result);
	else
		(dynamic_cast<Real*>((*identifiers)[args[0]]))->setValue(result);

	// ***** for testing
	if (typeid(*((*identifiers)[args[0]])) == typeid(Numeric()))
	{
		cout << (dynamic_cast<Numeric*>((*identifiers)[args[0]]))->getValue();
		cout << ++result;
	}
	else
	{
		cout << (dynamic_cast<Real*>((*identifiers)[args[0]]))->getValue();
		cout << ++result;
	}
    // **** end for testing

	return -1;
}
