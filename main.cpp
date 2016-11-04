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

using namespace std;

constexpr size_t LINESIZE = 1024;

void splitFileName(char* filename, string &prefix, string &suffix);

int main (int argc, char** argv) {
   const char* execname = basename (argv[0]);
   int exit_status = EXIT_SUCCESS;
   string suffix, prefix;
   string line;
   vector<string> fileinput;
   vector<string> instInput;
   vector<string> varInput;

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

   ifstream file(filename);

   if(file.is_open())
   {
      int found;
      while(getline(file,line))
      {
         cout << line << endl;
         fileinput.push_back(line);

         //should parse and split input into variable
         // and instructions
         // does not act upon it.
         if(!line.find("VAR"))
            varInput.push_back(line);
         else
            instInput.push_back(line);
      }
      file.close();
   }

   cout <<endl << "Variables" << endl;
   for(string out: varInput)
      cout << out << endl;

   cout << endl << "Instructions" << endl;
   for(string out: instInput)
      cout << out << endl;

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