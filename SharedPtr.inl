template<typename T>
SharedPtr<T>::SharedPtr(T* ptr) {
    assign(ptr);
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& other) {
    assign(other);
}

template<typename T>
SharedPtr<T>::~SharedPtr() {
    destroy();
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other) {
    destroy();
    assign(other);
    return *this;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(T* other) {
    destroy();
    assign(other);
    return *this;
}


template<typename T>
size_t SharedPtr<T>::getReferenceCount() const {
    return mReferenceCount->load();
}


template<typename T>
T* SharedPtr<T>::assign(const SharedPtr<T>& other) {
    mReferenceCount = other.mReferenceCount;
    mReferenceCount->operator++();
    return swapPtr(other.mPtr);
}

template<typename T>
T* SharedPtr<T>::assign(T* other) {
    mReferenceCount = new std::atomic<size_t>(1);
    return swapPtr(other);
}

template<typename T>
void SharedPtr<T>::destroy() {
    mReferenceCount->operator--();
    if(getReferenceCount() == 0) {
        delete mReferenceCount;
        if(mPtr) {
            delete mPtr;
        }
    }
}


template<typename T>
T* SharedPtr<T>::swapPtr(T* ptr) {
    T* oldPtr = ptr;
    mPtr = ptr;
    return oldPtr;
}