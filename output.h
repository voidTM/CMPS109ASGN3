#ifndef _OUPTUT_
#define _OUTPUT_

#include "common.h"

class Output{
  private:
    string outBuffer;
    string errBuffer;
    pthread_mutex_t mutex; // A mutex for managing critical section
    pthread_cond_t consume_cond; // A condition for the consumer to wait when buffer is empty
    pthread_cond_t produce_cond; // A condition for the producer to wiat when buffer is full
    int producer_current; // The index pointer of the producer within the buffer
    int consumer_current; // The index pointer of the consumer within the buffer
    int count; // T

  public:

}
