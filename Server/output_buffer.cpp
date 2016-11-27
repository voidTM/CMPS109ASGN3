#include "output_buffer.h"

OutputBuffer::OutputBuffer() {
    outputBuffer = "";
}

OutputBuffer::~OutputBuffer() {}

void OutputBuffer::reportOutput(string output) {
    outputBuffer += output;
}

string OutputBuffer::getOutputBuffer() { 
    return outputBuffer;
}

void OutputBuffer::emptyBuffer() {
    outputBuffer = "";
}

