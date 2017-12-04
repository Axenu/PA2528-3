template<typename Return, typename... Params>
Function<Return(Params...)>::Function(Return (*function)(Params...))
: mCaller(callFunction)
, mDestroyer(destroyFunction) {
    mFunction.function = function;
}

template<typename Return, typename... Params>
template<typename LambdaT>
Function<Return(Params...)>::Function(const LambdaT& lambda)
: mCaller(callLambda)
, mDestroyer(destroyLambda) {
    mFunction.lambda = Lambda<Return(Params...)>::make(lambda);
}

template<typename Return, typename... Params>
Function<Return(Params...)>::~Function() {
    mDestroyer(mFunction);
}

template<typename Return, typename... Params>
Return Function<Return(Params...)>::operator()(Params... args) {
    return mCaller(mFunction, args...);
}

template<typename Return, typename... Params>
Return Function<Return(Params...)>::callLambda(FunctionPtr ptr, Params... args) {
    return ptr.lambda->operator()(args...);
}

template<typename Return, typename... Params>
Return Function<Return(Params...)>::callFunction(FunctionPtr ptr, Params... args) {
    return ptr.function(args...);
}

template<typename Return, typename... Params>
void Function<Return(Params...)>::destroyLambda(FunctionPtr ptr) {
    delete ptr.lambda;
}

template<typename Return, typename... Params>
void Function<Return(Params...)>::destroyFunction(FunctionPtr ptr) {
}
