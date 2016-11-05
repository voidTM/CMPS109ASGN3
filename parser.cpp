#include "parser.h"

using namespace std;

//Constructor
Parser::parser(){
   //create maps
   varSet["NUMERIC"] = new Numeric();
   varSet["REAL"] = new Real();
   varSet["CHARACTER"] = new Character();
   varSet["STRING"] = new String();

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

Parser::parseFile(string filename){
   ifstream file(filename);

   if(file.is_open())
   {
      int found;
      string command;
      while(getline(file,line))
      {
         cout << line << endl;
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

Parser::parseVar(stringstream &line){
   string token;
   vector<char*> arguments;
   char* cstr;
   
   //use , as delimiter for now?
   while(getline(line, token, ",")){
      strdup(cstr, token.c_str());
      arguments.push_back(cstr);
   }
}