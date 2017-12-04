#ifndef __FUNCTION_HPP__
#define __FUNCTION_HPP__

#include "Lambda.hpp"


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
        union FunctionPtr {
            Lambda<Return(Params...)>* lambda;
            Return (*function)(Params...);
        };

    private:
        static Return callLambda(FunctionPtr ptr, Params... args);
        static Return callFunction(FunctionPtr ptr, Params... args);

    private:
        FunctionPtr mFunction;
        Return (*mCaller)(FunctionPtr ptr, Params...);
};

#include "Function.inl"

#endif // __FUNCTION_HPP__



