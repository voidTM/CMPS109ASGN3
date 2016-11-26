#include <string>
#include "server.h"
#include <fstream>
#include <iostream>

int main (int argc, char** argv) {

/*
	string programFileName = argv[argc - 1];
	string errorFileName = programFileName + ".err";
	string outputFileName = programFileName + ".out";

	ofstream out(outputFileName);
	ofstream err(errorFileName);
	// Redirect output to filess
	streambuf *coutbuf = cout.rdbuf();
	cout.rdbuf(out.rdbuf());
	streambuf *cerrbuf = cerr.rdbuf();
	cerr.rdbuf(err.rdbuf());

	Machine machine(programFileName);
	machine.run();

    cout.rdbuf(coutbuf); //reset to standard output again
    cerr.rdbuf(cerrbuf);
*/

	Server server("127.0.0.1", 1000);
	server.run();

}
