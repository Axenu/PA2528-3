#ifndef __THREAD__
#define __THREAD__

#include <cstring>

#include "Function.hpp"


class Thread {
    public:
        Thread(const Function<void()>& function);
        ~Thread();

        void run();
        void join();

        // Returns true if thread is terminated. Else false.
        bool wait(size_t milliseconds = 0) const;

    private:
        void* createThread() const;

    private:
        Function<void()> mFunction;
        void* mThreadHandle = nullptr;
};

#endif // __THREAD__

