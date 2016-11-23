#ifndef GARBAGE_COLLECTOR
#define GARBAGE_COLLECTOR

#include "machine.h"

template <typename T>
class GarbageCollector
{
  private:

    vector<T> objects;

  public:
    GarbageCollector();// Constructor
    void addConnection(T machine); // Add a connection
    void cleanup(); // Perform a clean up by disposing expired connections.
    void terminate (); // Wait for all thread connections to terminate and cleanup all
    ~GarbageCollector(); // Destructor
};

#endif
