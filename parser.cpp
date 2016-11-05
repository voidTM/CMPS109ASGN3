#include "parser.h"

using namespace std;

//Constructor
Parser::Parser(){
   //create maps
   typeSet["NUMERIC"] = new Numeric();
   typeSet["REAL"] = new Real();
   typeSet["CHARACTER"] = new Character();
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
         //scout << line << endl;
         //fileinput.push_back(line);
         stringstream iss(line);
         // gets first with whitespace delimiter
         getline(iss, command, ' ');

         // check to see if it is a variable
         if(!command.compare("VAR"))
            parseVar(iss);
         else
            parseInst(command, iss);

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

   //use , as delimiter for now?
   while(getline(line, token, ',')){
      strcpy(cstr, token.c_str());
      arguments.push_back(cstr);
   }

   // get the name and type of variable
   // after parsing
   string varName = arguments[0];
   string varType = arguments[1];
   // remove name and type from argument vector
   arguments.erase(arguments.begin(), arguments.begin()+1);

   //call appropriate type object
   Identifier* obj = typeSet[varType];
   if(obj != NULL){
      //create clone
      obj = obj->clone(arguments);
      //store into variable map
      varMap[varName] = obj;
   }
}

void Parser::parseInst(string command, stringstream &argv){
   string token;
   vector<char*> arguments;
   char* cstr;

   //use , as delimiter for now?
   while(getline(argv, token, ',')){
      strcpy(cstr, token.c_str());
      arguments.push_back(cstr);
   }
   /*
   Instruction* inst = instSet[command];
   if(obj != NULL){
      obj = obj->clone(arguments);

      instructions.push_back(obj);
   }*/
}
