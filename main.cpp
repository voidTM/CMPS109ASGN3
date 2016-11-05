#include <string>
#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <ctype.h>
#include <wait.h>
#include <vector>

#include "identifier.h"
#include "real.h"
#include "numeric.h"
#include "character.h"
#include "mis_string.h"
#include "parser.h"

using namespace std;


void splitFileName(char* filename, string &prefix, string &suffix);

// testing/debugging functions for class
void testNumeric();
void testReal();
void testCharacter();
void testString();

int main (int argc, char** argv) {
   int exit_status = EXIT_SUCCESS;
   string suffix, prefix;
   string line;
   Parser parser;

   // Assumes last argument is file name
   char* filename = argv[argc - 1];
   //printf ("command=\"%s\"\n", command.c_str());
   //Check to see if it filename has .oc suffix.
   splitFileName(filename, prefix, suffix);

   if (suffix != ".mis")
   {
      fprintf (stderr, "File not of file type .mis\n");
      return EXIT_FAILURE;
   }

   parser.parseFile(filename);

   return exit_status;
}



// Gets a string name and splits it on the dot.
void splitFileName(char* arg, string &prefix, string &suffix){
   string filename = arg;
   size_t dotpos = filename.find_last_of(".");
   if (dotpos == string::npos)
   { 
      cerr << "not a file " << endl;
   }
   else {
      prefix = filename.substr (0, dotpos);
      suffix = filename.substr (dotpos);
   }
}

void testNumeric(){
   cout << "Testing Numeric" << endl;
}
void testReal();
void testCharacter();
void testString();
