#include "parser.h"

using namespace std;

//Constructor
Parser::Parser(){
   //create maps
   typeSet["NUMERIC"] = new Numeric();
   typeSet["REAL"] = new Real();
   typeSet["CHAR"] = new Character();
   typeSet["STRING"] = new String();

   // for instructions
   /*
   instSet["ADD"]
   instSet["SUB"]
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

void Parser::parseFile(string filename){
   ifstream file(filename);
   string line;
   if(file.is_open())
   {
      string command;
      while(getline(file,line))
      {
         cout << line << endl;
         //fileinput.push_back(line);
         stringstream iss(line);
         // gets first with whitespace delimiter
         //int i = line.find_first_of(" \t\n");
         //get(iss, command, i);
         iss >> command;
         // check to see if it is a variable
         if(!command.compare("VAR"))
            parseVar(iss);
         else{
            //cout << "found instruction" << endl;
            parseInst(command, iss);
         }

         //should parse and split input into variable
         // and instructions
         // does not act upon it.

      }
      file.close();
   }

}

void Parser::parseVar(stringstream &line){
   string token;
   vector<char*> arguments;
   char* cstr;

   //line.flags(skipws);

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
      varMap[varName] = obj;
   }
   else
      cerr << "class not found" << endl;
}

void Parser::parseInst(string command, stringstream &argv){
   string token;
   vector<char*> arguments;
   char* cstr;

   //use , as delimiter for now?
   while(getline(argv, token, ',')){
      cstr = strdup(token.c_str());
      arguments.push_back(cstr);
   }
   /*
   Instruction* inst = instSet[command];
   if(obj != NULL){
      obj = obj->clone(arguments);

      instructions.push_back(obj);
   }*/
}

// Run cpp against the lines of the file.
vector<string> Parser::parseLine (string line) {
   char* buffer; char* bufptr;
   char* savepos = NULL;
   vector<string> strtoken;

   buffer = strdup(line.c_str());
   bufptr = buffer;

   // parse linebuffer
   for (int tokenct = 1;; ++tokenct) {
      char* token = strtok_r (bufptr, " \t\n", &savepos);
      bufptr = NULL;
      if (token == NULL) break;
      //sprintf(temp,"token %d.%d: [%s]",
      strtoken.push_back(token);
      //store this
      //cout << strtoken.back();
      }
   return strtoken;
}

// removes from both ends
void Parser::trimWhitespace(string& str)
{
    size_t first = str.find_first_not_of(" \t\n");
    size_t last = str.find_last_not_of(" \t\n");
    str = str.substr(first, (last-first+1));
}

Parser::~Parser(){}