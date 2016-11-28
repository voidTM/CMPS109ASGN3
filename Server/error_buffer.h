#ifndef ERRORBUFFER
#define ERRORBUFFER

#include <string>
#include <mutex>
#include <pthread.h>

using namespace std;

class ErrorBuffer {
private:
    string errorBuffer;
    mutex cerr_mutex;
    
public:
    ErrorBuffer();
    
    void reportError(string errorMsg, int lineNumber = -1);

    string getErrorBuffer();
    
    void emptyBuffer();
    
    ~ErrorBuffer();
};

#endif

