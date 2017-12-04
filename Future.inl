#include <cassert>

template<typename T>
Future<T>::Future(Function<T()>&& function)
: mFunction(new Function<T()>(std::move(function)))
, mThread(new Thread([this](){mPromise = mFunction->operator()(); mIsReady = true;})) {
    mThread->run();
}

template<typename T>
Future<T>::~Future() {
    mThread->join();
}

template<typename T>
bool Future<T>::wait(size_t milliseconds) const {
    if(mIsReady) {
        return true;
    }
    return mThread->wait(milliseconds);
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
