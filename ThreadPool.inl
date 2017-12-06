template<typename T>
Promise<T> ThreadPool::promise(const Function<T()>& function) {
    SharedPtr<SharedPtr<T>> promise(new SharedPtr<T>((T*)new char[sizeof(T)]));
    SharedPtr<bool> isReady(new bool());
    *isReady = false;
    Semaphore semaphore;

    launch([promise, isReady, semaphore, function]() {
        new(promise->get()) T(function());
        *isReady = true;
        semaphore.signal();
    });

    return Promise<T>(promise, isReady, semaphore);
}
