#ifndef MESSAGE
#define MESSAGE

#include "common.h"

using namespace std;

class Message{
  private:
    static string errorBuffer;
    static string outputBuffer;

    pthread_mutex_t mutex; // A mutex for managing critical section
    pthread_cond_t consume_cond; // A condition for the consumer to wait when buffer is empty
    pthread_cond_t produce_cond; // A condition for the producer to wiat when buffer is full
    int producer_current; // The index pointer of the producer within the buffer
    int consumer_current; // The index pointer of the consumer within the buffer
    int count; // The current number of item in the buffer
	public:
    Message();

    void errorMessage(string);
    void outputMessage(string);

    string getErrorBuffer();
    string getOutputBuffer();

};

#endif
