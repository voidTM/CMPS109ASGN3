#ifndef TCPSOCKET_CLIENT
#define TCPSOCKET_CLIENT

#include "TCPSocket.h"

class TCPClient{

  private:
    TCPSocket connection;
  public:
    TCPClient()
    // Sends an entire file to client
    bool writeFileToSocket(filename);

    // Reads an entire file from client
    int readFileFromSocket();
}
