#ifndef OUTPUTBUFFER
#define OUTPUTBUFFER

#include <string>

using namespace std;

class OutputBuffer {
private:
    string outputBuffer;
    
public:
    OutputBuffer();
    
    void reportOutput(string output);

    string getOutputBuffer();
    
    void emptyBuffer();
    
    ~OutputBuffer();
};

#endif

