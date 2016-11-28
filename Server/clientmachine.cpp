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
		while(getline(file,line) && !file.eof())
		{
			//printf("")
        	//printf("%s \n", line.c_str());
         	inputBuffer += line + "\n";
		}
		file.close();
	}
	else{
		parseError = true;
		reportError("Can't find file\n");
		return;
		//exit(1);
	}

}

bool ClientMachine::checkError(){
	readFile();
	if(parseError == true){
		//printf("File not found \n");
		return parseError;
	}
	parseFile();
	return parseError;
}

string ClientMachine::getOutputMsg(){ return outputBuffer.getOutputBuffer(); }

string ClientMachine::getErrorMsg(){ return errorBuffer.getErrorBuffer(); }



void ClientMachine::executeInstructions(int startInstIdx){}


bool ClientMachine::getErrorStatus(){ return parseError; }

ClientMachine::~ClientMachine(){}
