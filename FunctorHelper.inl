template<typename Function>
FunctorHelper<Function>::FunctorHelper(Function function) : mFunction(function) {
}

template<typename Function>
void FunctorHelper<Function>::operator()() {
    mFunction();
}
