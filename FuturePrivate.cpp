#ifndef __FUTURE__
#define __FUTURE__

#include "Thread.hpp"

template<typename Return>
class Future {
    public:
        Future(Return (*function)(void* args));

        // Returns true if future is ready. Else false.
        bool wait(size_t milliseconds = 0);
        Return get();

    private:
        Thread mThread;
};

#include "Future.inl"

#endif // __FUTURE__

