#ifndef __FUTURE__
#define __FUTURE__

#include "Thread.hpp"

template<typename T>
class Future {
    public:
        template<typename Function>
        Future(const Function& function);

        ~Future();

        // Wait forever if 0.
        bool wait(size_t milliseconds = 0) const;
        bool isReady() const;
        T get() const;

    private:
        Thread mThread;
        T mPromise;
        volatile bool mIsReady = false;
};

#include "Future.inl"

#endif // __FUTURE__

