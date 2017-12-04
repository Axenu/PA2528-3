template<typename Return, typename... Params>
Function<Return(Params...)>::Function(Return (*function)(Params...))
: mCaller(callFunction) {
    mFunction.function = function;
}

template<typename Return, typename... Params>
template<typename LambdaT>
Function<Return(Params...)>::Function(const LambdaT& lambda)
: mCaller(callLambda) {
    mFunction.lambda = Lambda<Return(Params...)>::make(lambda);
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
