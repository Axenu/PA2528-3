#include "Thread.hpp"


Thread::Thread(void (*function)(void* args)) : mFunction(function){

}

void Thread::run(void* args) {
    mThreadHandle = createThread(args);
}

void Thread::join() {
    if(!mThreadHandle) {
        return;
    }

    // wait...

    // close handle
}

bool Thread::wait(size_t milliseconds) {
    return true;
}

void* Thread::createThread(void* args) const {
    return nullptr;
}
