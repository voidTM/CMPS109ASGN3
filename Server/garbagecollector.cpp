#include "garbagecollector.h"

typename T
GarbageCollector::GarbageCollector(){
  connections = new vector<T>;
}

GarbageCollector::addConnection(Machine* machine){
  connection.push_back(machine);
}


GarbageCollector::cleanup(){

  for(int i = connection.begin(); i < connection.end(); i++){
    if(connection[i] != NULL || !connection[i].isRunning()){
      connection[i]->waitForRunToFinish();
      connection.erase(i);
    }
  }
}

GarbageCollector::terminate(){
  for(int i = connection.begin(); i < connection.end(); i++){
    if(connection[i] != NULL){
      connection[i]->waitForRunToFinish();
      connection.erase(i);
    }
  }
}

GarbageCollector::~GarbageCollector() { terminate(); }
