// Constructor
ThreadManager::ThreadManager() {}
// Add a thread
void ThreadManager::addThread (Thread * p_thread) {
  threads.push_back(p_thread); // Push back thread pointer to threads vector
}
// Start all threads
void ThreadManager::startAll() {
// Loop on all vector threads and start them
  for ( int i = 0 ; i < threads.size();i++)
    threads[i]->start();
}

// Start an individual thread.
void ThreadManager::start(int i) {
    threads[i]->start();
}

// Wait on barrier on all threads
void ThreadManager::barrier() {
// Loop on all vector thread and block until terminated
 for ( int i = 0 ; i < threads.size();i++)
  threads[i]->waitForRunToFinish();
}


// Destructor
ThreadManager::~ThreadManager() {
// Loop on threads vector and delete all threads
  for ( int i = 0 ; i < threads.size();i++)
    delete (threads[i]);
}
