#ifndef __THREAD__
#define __THREAD__

#include <cstring>

#include "Functor.hpp"


class Thread {
    public:
        Thread(const Functor& function);
        ~Thread();

        void run();
        void join();

        // Returns true if thread is terminated. Else false.
        bool wait(size_t milliseconds = 0) const;

    private:
        void* createThread() const;

    private:
        Functor mFunction;
        void* mThreadHandle = nullptr;
};

#endif // __THREAD__

