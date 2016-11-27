#ifndef ERRORBUFFER
#define ERRORBUFFER

#include <string>

using namespace std;

class ErrorBuffer {
private:
    string errorBuffer;
    
public:
    ErrorBuffer();
    
    void reportError(string errorMsg, int lineNumber = -1);

    string getErrorBuffer();
    
    void emptyBuffer();
    
    ~ErrorBuffer();
};

#endif

