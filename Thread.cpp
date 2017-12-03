#include "Thread.hpp"

#include <windows.h>
#include <cassert>

Thread::Thread(const Functor& function) : mFunction(function) {
}

Thread::~Thread() {
    join();
}

void Thread::run() {
    mThreadHandle = createThread();
    assert(mThreadHandle != nullptr);
}

void Thread::join() {
    if(!mThreadHandle) {
        return;
    }

    while(!wait(1000));

    CloseHandle(mThreadHandle);
}

bool Thread::wait(size_t milliseconds) const {
    if(!mThreadHandle) {
        return true;
    }
    return WaitForSingleObject(mThreadHandle, milliseconds) == WAIT_OBJECT_0;
}

namespace ThreadPrivate {
    DWORD WINAPI entry(void* args) {
        ((Functor*)args)->operator()();
        return 0;
    }
}

void* Thread::createThread() const {

    void* h = CreateThread(NULL, 0, ThreadPrivate::entry, (void*)&mFunction, 0, NULL);
    if(h == NULL) {
        return nullptr;
    }
    return h;
}
