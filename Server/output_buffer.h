#ifndef OUTPUTBUFFER
#define OUTPUTBUFFER

#include <string>

using namespace std;

class OutputBuffer {
private:
    static string outputBuffer;
    
public:
    static void reportOutput(string output);

    static string getOutputBuffer();
};

#endif

