template<typename Return>
Future<Return>::Future(Return* (*function)(void*), void* args) : mThread(FuturePrivate::entry) {
    mBlock.args = args;
    mBlock.function = (void* (*)(void*))function;
    mThread.run((void*)&mBlock);
}

template<typename Return>
bool Future<Return>::wait(size_t milliseconds) {
    return mThread.wait(milliseconds);
}

template<typename Return>
Return* Future<Return>::get() {
    mThread.join();
    return (Return*)mBlock.ret;
}
