#include "garbagecollector.h"

template <typename T>
GarbageCollector<T>::GarbageCollector(){
  objects = new vector<T>;
}

template <typename T>
void GarbageCollector<T>::addConnection(T machine){
  objects.push_back(machine);
}


template <typename T>
void GarbageCollector<T>::cleanup(){
  for(int i = objects.begin(); i < objects.end(); i++){
    if(objects[i] != NULL || !objects[i].isRunning()){
      objects[i]->waitForRunToFinish();
      objects.erase(i);
    }
  }
}

template <typename T>
void GarbageCollector<T>::terminate(){
  for(int i = objects.begin(); i < objects.end(); i++){
    if(objects[i] != NULL){
      objects[i]->waitForRunToFinish();
      objects.erase(i);
    }
  }
}

template <typename T>
GarbageCollector<T>::~GarbageCollector() { terminate(); }
