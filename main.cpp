#include <string>
#include "machine.h"

int main (int argc, char** argv) {
	string programFileName = argv[argc - 1];
	string errorFileName = "output.err";
	string outputFileName = "output.out";
	Machine machine(programFileName, errorFileName, outputFileName);
	machine.run();
}
