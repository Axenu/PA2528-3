template<typename Return, typename... Params>
Function<Return(Params...)>::Function(Return (*function)(Params...))
: mCaller(callFunction) {
    mFunction = function;
}

template<typename Return, typename... Params>
template<typename LambdaT>
Function<Return(Params...)>::Function(const LambdaT& lambda)
: mCaller(callLambda) {
    mLambda = Lambda<Return(Params...)>::make(lambda);
}


template<typename Return, typename... Params>
Return Function<Return(Params...)>::operator()(Params... args) {
    return (this->*mCaller)(args...);
}

template<typename Return, typename... Params>
Return Function<Return(Params...)>::callLambda(Params... args) {
    return mLambda->operator()(args...);
}

template<typename Return, typename... Params>
Return Function<Return(Params...)>::callFunction(Params... args) {
    return mFunction(args...);
}
