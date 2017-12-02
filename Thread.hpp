#ifndef __THREAD__
#define __THREAD__

#include <cstring>

class Thread {
    public:
        Thread(void (*function)(void*));

        void run(void* args);
        void join();

        // Returns true if thread is terminated. Else false.
        bool wait(size_t milliseconds = 0);

    private:
        void* createThread(void* args) const;

    private:
        void (*mFunction)(void* args) = nullptr;
        void* mThreadHandle = nullptr;
};

#endif // __THREAD__

