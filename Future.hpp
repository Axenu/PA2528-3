#ifndef __FUTURE__
#define __FUTURE__

#include "Thread.hpp"
#include "Function.hpp"

template<typename T>
class Future {
    public:
        Future(Function<T()>&& function);

        ~Future();


        // Wait forever if 0.
        bool wait(size_t milliseconds = 0) const;
        bool isReady() const;
        T get() const;

    private:
        SharedPtr<Thread> mThread;
        SharedPtr<Function<T()>> mFunction;
        T mPromise;
        volatile bool mIsReady = false;
};

#include "Future.inl"

#endif // __FUTURE__

