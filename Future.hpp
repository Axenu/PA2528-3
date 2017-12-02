#ifndef __FUTURE__
#define __FUTURE__

#include "Thread.hpp"

namespace FuturePrivate {
    struct Block {
        void* ret = nullptr;
        void* args = nullptr;
        void* (*function)(void*) = nullptr;
    };
    void entry(void* block);
}

template<typename Return>
class Future {
    public:
        Future(Return* (*function)(void*), void* args);

        // Returns true if future is ready. Else false.
        bool wait(size_t milliseconds = 0);
        Return* get();

    private:
        FuturePrivate::Block mBlock;
        Thread mThread;
};

#include "Future.inl"

#endif // __FUTURE__

