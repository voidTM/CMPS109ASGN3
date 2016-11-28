#ifndef THREAD_MANAGER
#define THREAD_MANAGER

#include "Thread.h"

class ThreadManager
{
  private:
    vector <Thread *> threads; // Vector of Thread pointers
  public:
    ThreadManager(); // Constructor
    void addThread (Thread * p_thread); // Add a thread
    void startAll();// Start all threads
    void start(int);
    void barrier(); // Wait for all threads to finish
    ~ThreadManager(); // Destructor
};


#endif
