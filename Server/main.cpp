#include <string>
#include "server.h"
#include <fstream>
#include <iostream>

using namespace std;

int main (int argc, char** argv) {

	if(argc != 2 && argc != 3 ) {
		cout << "server_misvm <server port>" << endl;
		cout << "or" << endl;
		cout << "server_misvm <<server IPaddress> server port>" << endl;
		exit(1);
	}

    int port;
    char* serverAddress;
    if (argc == 2)
    {
    	serverAddress = NULL;
	    port = atoi(argv[1]);
    }
    if (argc == 3)
    {
    	serverAddress = argv[1];
	    port = atoi(argv[2]);
    }

	Server server(serverAddress, port);
	server.run();
}

