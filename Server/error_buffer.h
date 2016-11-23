#ifndef ERRORBUFFER
#define ERRORBUFFER

#include <string>

using namespace std;

class ErrorBuffer {
private:
    static string errorBuffer;
    
public:
    static void reportError(string errorMsg, int lineNumber = -1);

    static string getErrorBuffer();
};

#endif

