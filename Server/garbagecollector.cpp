#include "garbagecollector.h"

GarbageCollector::GarbageCollector(){
}

void GarbageCollector::addConnection(Machine* machine){
  objects.push_back(machine);
}


void GarbageCollector::cleanup(){
  auto i = objects.begin();

  while (i != objects.end()) {
      // do some stuff
      if (*i != nullptr ||!(*i)->isRunning()){
        (*i)->waitForRunToFinish();
        i = objects.erase(i);
      }
      else
          ++i;
  }
}

void GarbageCollector::terminate(){
  auto i = objects.begin();

  while (i != objects.end()) {
      // do some stuff
      if (*i != nullptr)
          i = objects.erase(i);
      else
          ++i;
  }
}

GarbageCollector::~GarbageCollector() { terminate(); }
