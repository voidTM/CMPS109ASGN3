#include "output_buffer.h"

string OutputBuffer::outputBuffer = "";

void OutputBuffer::reportOutput(string output) {
    outputBuffer += output;
}

string OutputBuffer::getOutputBuffer() { 
    return outputBuffer;
}

void OutputBuffer::emptyBuffer() {
    outputBuffer = "";
}

