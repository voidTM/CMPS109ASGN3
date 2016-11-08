#include "machine.h"
#include "add.h"
#include <string>
//#include "stdlib.h"

Machine::Machine() {}

Machine::Machine(string programFileName, string errorFileName, string outputFileName) :
		programFileName(programFileName) , errorFileName(errorFileName) , outputFileName(outputFileName) {

	parseError = false;
	typeSet["NUMERIC"] = new Numeric();
	typeSet["REAL"] = new Real();
	typeSet["CHAR"] = new Character();
	typeSet["STRING"] = new String();

	instSet["ADD"] = new Add(this);

	/*instSet["SUB"]
	   instSet["MUL"]
	   instSet["DIV"]
	   instSet["ASSIGN"]
	   instSet["OUT"]
	   instSet["SET_STR_CHAR"]
	   instSet["GET_STR_CHAR"]
	   instSet["LABEL"]? <-not instruction class
	   instSet["JMP"]
	   instSet["JMPZ"]
	   instSet["JMPNZ"]
	   instSet["JMPGT"]
	   instSet["JMPLT"]
	   instSet["JMPGTE"]
	   instSet["JMPLTE"]
	   instSet["SLEEP"]
	 */
}

Machine::~Machine() {
}

void Machine::parseFile(){
	int lineNumber;
	parseError = false;
	cout << programFileName << endl;
	ifstream file(programFileName);
	string line;
	if(file.is_open())
	{
		string command;
		lineNumber = 1;
		while(getline(file,line))
		{
         	cout << line << endl;
         	stringstream iss(line);
         	iss >> command;
         	// check to see if it is a variable
         	if(!command.compare("VAR"))
            	parseVar(iss, lineNumber);
         	else{
            	cout << "Instruction: " << command <<endl;
            	parseInst(command, iss, lineNumber);
        	}

			//should parse and split input into variable
			// and instructions
			// does not act upon it.

			lineNumber++;
		}
		file.close();
	}

}

void Machine::parseInst(string command, stringstream &argv, int lineNumber){
	try
	{
		string token;
		vector<char*> arguments;
		char* cstr;


	   	while(getline(argv, token, ',')){
    		trimWhitespace(token);
      		cout << "Token: " << token << endl;
      		cstr = strdup(token.c_str());
      		arguments.push_back(cstr);
   		}

		Instruction* obj = instSet[command];
		if(obj != NULL){
			obj = obj->clone(arguments, lineNumber);

			instructions.push_back(obj);
		}
	}

	catch (int e)
	{
		reportError("An error was generated while parsing the line.", lineNumber);
	}
}

void Machine::parseVar(stringstream &line, int lineNumber){
	try
	{
		string token;
		vector<char*> arguments;
		char* cstr;

		//use , as delimiter for now?
	   	while(getline(line, token, ',')){
    		trimWhitespace(token);
      		cout << "Token: " << token << endl;
      		cstr = strdup(token.c_str());
      		arguments.push_back(cstr);
   		}

		// get the name and type of variable
		// after parsing
	   	string varName = arguments[0];
   		string varType = arguments[1];
   		// remove name and type from argument vector
   		arguments.erase(arguments.begin());
   		arguments.erase(arguments.begin());
   		cout << "arguments length: " << arguments.size() << endl;
   		//call appropriate type object
   		Identifier* obj = typeSet[varType];
   		if(obj != NULL){
    	  //create clone
    	  obj = obj->clone(arguments);
    	  //store into variable map
    	  identifiers[varName] = obj;
    	  //return obj;
	   }
	   else
	      cerr << "class not found" << endl;
	}

	catch (int e)
	{
		reportError("An error was generated while parsing the line.", lineNumber);
	}
}

// parses line for every token/argument after the initial
// one
vector<char*> Machine::parseLine (stringstream &line) {
   string token;
   vector<char*> tokens;
   char* cstr;

   //use , as delimiter for now?
   while(getline(line, token, ',')){
      trimWhitespace(token);
      cout << "Token: " << token << endl;
      cstr = strdup(token.c_str());
      tokens.push_back(cstr);
   }
   return tokens;
}

// removes from both ends
void Machine::trimWhitespace(string& str){
    size_t first = str.find_first_not_of(" \t\n");
    size_t last = str.find_last_not_of(" \t\n");
    str = str.substr(first, (last-first+1));
}

void Machine::run()
{
	// if there is an error in parsing the program file, terminate the execution
	parseFile();
	if (parseError) return;
	cout << "Running \n";
	// try to execute the program line by line (instruction by instruction)
	int retval, currentInstIdx = 0;
	try
	{
		while (currentInstIdx < instructions.size())
		{
			cout << "At: " << currentInstIdx << endl;
			retval = instructions[currentInstIdx]->execute();

			if (retval == -1)
				currentInstIdx++; // if it was a non-jump instructions, then go to the next instruction
			else
				currentInstIdx = retval; // if it was a jump instruction, then jump to that specified point
		}
	}

	catch (int e)
	{
		int lineNumber = instructions[currentInstIdx]->getLineNumber();
		reportError("An error was generated while executing the line. Execution of the program terminated." , lineNumber, true);
	}
}

void Machine::reportError(string errMsg , int lineNumber /*= -1*/ , bool terminate /*= false*/) {

	ofstream file(errorFileName);
	if(file.is_open())
	{
		string output = errMsg + "\n";
		if (lineNumber > -1)
			output = "Error in line " + to_string(lineNumber) + ": " + output;
		file << output;
		file.close();
	}

	if (terminate)
		exit(1);
}

void Machine::setParseError(bool val) {
	parseError = val;
}

map<string,Identifier*> * Machine::getidentifiers() {
	return & identifiers;
}

map<string,Identifier*> * Machine::getTypes(){
	return & typeSet;
}