#include "Thread.hpp"


Thread::Thread(const Functor& function) : mFunction(function) {
}

void Thread::run() {
    mThreadHandle = createThread();
}

void Thread::join() {
    if(!mThreadHandle) {
        return;
    }

    // wait...

    // close handle
}

bool Thread::wait(size_t milliseconds) const {
    return true;
}

void* Thread::createThread() const {
    mFunction();
    return nullptr;
}
