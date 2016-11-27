#ifndef ERRORBUFFER
#define ERRORBUFFER

#include <string>
#include <mutex>
#include <pthread.h>

using namespace std;

class ErrorBuffer {
private:
    static thread_local string errorBuffer;
    mutex cerr_mutex;
    
public:
    ErrorBuffer();
    
    static void reportError(string errorMsg, int lineNumber = -1);

    string getErrorBuffer();
    
    void emptyBuffer();
    
    ~ErrorBuffer();
};

#endif

