#ifndef TCPSOCKET_CLIENT
#define TCPSOCKET_CLIENT

#include <iostream>
#include <fstream>
#include <string>
#include "stdio.h"
#include <sstream>

#include "TCPSocket.h"

class TCPClient{

  private:
    TCPSocket socket;
  public:
    TCPClient(char * address, int port);
    // Sends an entire file to client
    bool writeFileToSocket(string filename);

    // Reads an entire file from client
    int readFileFromSocket();
}
