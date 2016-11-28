#ifndef GARBAGE_COLLECTOR
#define GARBAGE_COLLECTOR

#include <vector>
#include "servermachine.h"
using namespace std;

class GarbageCollector
{
  private:

    vector<ServerMachine*> objects;

  public:
    GarbageCollector();// Constructor
    void addConnection(ServerMachine* machine); // Add a connection
    void cleanup(); // Perform a clean up by disposing expired connections.
    void terminate (); // Wait for all thread connections to terminate and cleanup all
    ~GarbageCollector(); // Destructor
};

#endif
