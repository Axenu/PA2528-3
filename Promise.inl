#include <cassert>

template<typename T>
Promise<T>::Promise(SharedPtr<SharedPtr<T>> promise, SharedPtr<bool> isReady, Semaphore semaphore)
: mPromise(promise)
, mIsReady(isReady)
, mSemaphore(semaphore) {
}

template<typename T>
bool Promise<T>::wait(size_t milliseconds) const {
    return mSemaphore.wait(milliseconds);
}


template<typename T>
void Promise<T>::wait() const {
    mSemaphore.wait();
}


template<typename T>
bool Promise<T>::isReady() const {
    return *mIsReady;
}


template<typename T>
T Promise<T>::get() const {
    mSemaphore.wait();
    assert(*mIsReady);
    return **mPromise;
}

