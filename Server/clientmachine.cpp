#include "clientmachine.h"

//ClientMachine::ClientMachine(){}

ClientMachine::ClientMachine(string programFileName) : Machine(){
	this->programFileName = programFileName;
}

// Read file content into the string buffer
void ClientMachine::readFile(){

	int lineNumber;
	int instNumber;
	parseError = false;
	ifstream file(programFileName);
	string line;

	if(file.is_open())
	{
		string command;
		lineNumber = 1;
		instNumber = 0;
		while(getline(file,line))
		{
         	//cout << line << endl;
         	inputBuffer += line + "\n";
		}
		file.close();
	}

}

bool ClientMachine::checkError(){
	readFile();
	parseFile();
	return parseError;
}

void ClientMachine::executeInstructions(int startInstIdx){}


bool ClientMachine::getErrorStatus(){ return parseError; }

ClientMachine::~ClientMachine(){}
