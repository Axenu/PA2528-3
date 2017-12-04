#ifndef __FUNCTION_HPP__
#define __FUNCTION_HPP__

#include "Lambda.hpp"
#include "SharedPtr.hpp"

template<typename T> class Function {
};

template<typename Return, typename... Params>
class Function<Return(Params...)> {
    public:
        Function(Return (*function)(Params...));

        template<typename LambdaT>
        Function(const LambdaT& lambda);

        Return operator()(Params... args);
    private:
        Return callLambda(Params... args);
        Return callFunction(Params... args);

    private:
        SharedPtr<Lambda<Return(Params...)>> mLambda;
        Return (*mFunction)(Params...);

        Return (Function::*mCaller)(Params...);
};

#include "Function.inl"

#endif // __FUNCTION_HPP__



