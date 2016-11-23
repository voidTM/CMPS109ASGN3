#include "TCPClient.h"


TCPClient::TCPClient(char * address, int port){
  socket = TCPSocket(address, port);
}

bool TCPClient::writeFileToSocket(filename){
  bool success = false;
  ifstream scriptFile(filename);
  if(scriptFile.is_open()){
    /*
    ostringstream oss;
    oss << scriptFile.rdbuf();
    scriptBuffer = oss.str();
    */
    while(getline(scriptFile,buffer))
      scriptBuffer.append(buffer + "\n");

    //printf("File Content: \n %s", scriptBuffer.c_str());
    filesize = scriptBuffer.size();
    string header = to_string(filesize);
    //printf( "file size %d \n", filesize);
    //cout << header << endl;
    // Send header data
    socket.writeToSocket(header.c_str(),100);
    while(filesize > 0){
      filesize -= socket.writeToSocket(scriptBuffer.c_str(), filesize);
    }
    success = true;
  }

  return success;
}

int TCPClient::readFileFromSocket(){
  char headerBuffer[100];
  socket.readFromSocket(headerBuffer, 100);
  //do something with header
  filesize = atoi(headerBuffer);
  //Reading data
  while(filesize > 0){
    // read until theoritical end of file
    filesize -= socket.readFromSocket(writeBuffer, filesize);
    //outfilebuffer.append(writeBuffer);
    cout << writeBuffer;
  }
  
}
