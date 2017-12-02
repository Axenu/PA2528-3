#include <cassert>

template<typename T>
template<typename Function>
Future<T>::Future(const Function& function)
: mThread([this, function](){mPromise = function(); mIsReady = true;}) {
}

template<typename T>
Future<T>::~Future() {
    mThread.join();
}

template<typename T>
bool Future<T>::wait(size_t milliseconds) const {
    if(mIsReady) {
        return true;
    }
    return mThread.wait(milliseconds);
}

template<typename T>
bool Future<T>::isReady() const {
    return mIsReady;
}

template<typename T>
T Future<T>::get() const {
    if(mIsReady) {
        return mPromise;
    }
    while(!wait(1000));
    assert(mIsReady);
    return mPromise;
}
