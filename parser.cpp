#include "parser.h"

using namespace std;

//Constructor
Parser::parser(){
   //create maps
   varSet["NUMERIC"] = new Numeric();
   varSet["REAL"] = new Real();
   varSet["CHARACTER"] = new Character();
   varSet["STRING"] = new String();
}