#include "parser.h"


Parser::Parser(){
	parseError = false;

	// Create a new object for each subclass of the identifier hierarchy and put them in the map. They will be used for cloning.
	typeSet["NUMERIC"] = new Numeric();
	typeSet["REAL"] = new Real();
	typeSet["CHAR"] = new Character();
	typeSet["STRING"] = new String();

   	// Create a new object for each subclass of the instruction hierarchy and put them in the map. They will be used for cloning.
	/*instSet["ADD"] = new Add(this);
	instSet["SUB"] = new Sub(this);
	instSet["MUL"] = new Mul(this);
	instSet["DIV"] = new Div(this);
	instSet["SET_STR_CHAR"] = new SetStrChar(this);
	instSet["GET_STR_CHAR"] = new GetStrChar(this);
	instSet["ASSIGN"] = new Assign(this);
	instSet["OUT"] = new Out(this);
	instSet["SLEEP"] = new Sleep(this);
	instSet["JMP"] = new Jump(this);
	instSet["JMPZ"] = new ConditionalJump(this, 1);
	instSet["JMPNZ"] = new ConditionalJump(this, 2);
	instSet["JMPGT"] = new ComparativeJump(this, 1);
    instSet["JMPLT"] = new ComparativeJump(this, 2);
    instSet["JMPGTE"] = new ComparativeJump(this, 3);
    instSet["JMPLTE"] = new ComparativeJump(this, 4);*/
}

Parser::~Parser(){}

// replaces all occurrences of a string inside of another string
// Replaces \n \t \r with the appropriate actual escape symbol
string Parser::ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

void Parser::parseFile(ifstream file){
	int lineNumber;
	int instNumber;
	parseError = false;
	string line;
		if(file.is_open())
	{
		string command;
		lineNumber = 1;
		instNumber = 0;
		while(getline(file,line))
		{
         	//cout << line << endl;
			line = ReplaceAll(line, "\\n", "\n");
			line = ReplaceAll(line, "\\t", "\t");
			line = ReplaceAll(line, "\\r", "\r");
         	stringstream iss(line);
         	iss >> command;

         	// check to see if it is a variable, label, or instruction
   			if(!command.compare("LABEL")){
				vector <char*> arguments = parseLine(iss);
   				labels[arguments[0]] = instNumber;
   			} else if(!command.compare("VAR"))
            	parseVar(iss, lineNumber);
         	/*else{
            	//cout << "Instruction: " << command <<endl;
            	parseInst(command, iss, lineNumber);
            	instNumber++; // Ticks for every instruction read
        	}*/

			lineNumber++;
		}
		file.close();
	}
}

// parses line for every token/argument after the initial
vector<char*> Machine::parseLine (stringstream &line) {
   string token;
   vector<char*> tokens;
   char* cstr;

   // tokens are created using . as the delimiter
   while(getline(line, token, ',')){
      trimWhitespace(token);
      //cout << "Token: " << token << endl;
      cstr = strdup(token.c_str()); // convert to c-string
      tokens.push_back(cstr);
   }
   return tokens;
}

// removes whitespace from both ends
void Machine::trimWhitespace(string& str){
    size_t first = str.find_first_not_of(" \t\n");
    size_t last = str.find_last_not_of(" \t\n");
    str = str.substr(first, (last-first+1));
}
