#include <string>
#include "machine.h"
#include <fstream>
#include <iostream>

void splitFileName(string& arg, string &prefix, string &suffix);

int main (int argc, char** argv) {

    string suffix; string prefix;
    string filename = argv[argc - 1];
   	splitFileName(filename, prefix, suffix);
	string programFileName = argv[argc - 1];
	string errorFileName = filename + ".err";
	string outputFileName = filename + ".out";

	ofstream out(outputFileName);
	ofstream err(errorFileName);
	streambuf *coutbuf = cout.rdbuf();
	cout.rdbuf(out.rdbuf());
	streambuf *cerrbuf = cerr.rdbuf();
	cerr.rdbuf(err.rdbuf());

	Machine machine(programFileName, errorFileName, outputFileName);
	machine.run();
    
    cout.rdbuf(coutbuf); //reset to standard output again
    cerr.rdbuf(cerrbuf);
}

// Gets a string name and splits it on the dot.
void splitFileName(string& arg, string &prefix, string &suffix){
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
