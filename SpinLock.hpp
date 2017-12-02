#ifndef __SPIN_LOCK__
#define __SPIN_LOCK__

#include <atomic>

class SpinLock {
    public:
        SpinLock();

        void lock();
        void unlock();

    private:
        std::atomic<bool> mIsLocked;
};

#endif // __SPIN_LOCK__

