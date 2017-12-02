#include "SpinLock.hpp"

SpinLock::SpinLock() : mIsLocked(false) {
}

void SpinLock::lock() {
    bool expected = false;
    while(!mIsLocked.compare_exchange_weak(expected, true));
}

void SpinLock::unlock() {
    mIsLocked = false;
}
