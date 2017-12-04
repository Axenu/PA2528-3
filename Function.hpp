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

        ~Function();

        Function(const Function&) = delete;
        Function& operator=(const Function&) = delete;

        Function(Function&& other) {
            mFunction = other.mFunction;
            mCaller = other.mCaller;
            mDestroyer = other.mDestroyer;
            other.mFunction.function = nullptr;
        }
        Function& operator=(Function&& other) {
            mFunction = other.mFunction;
            mCaller = other.mCaller;
            mDestroyer = other.mDestroyer;
            other.mFunction.function = nullptr;
            return *this;
        }

        Return operator()(Params... args);

    private:
        union FunctionPtr {
            Lambda<Return(Params...)>* lambda;
            Return (*function)(Params...);
        };

    private:
        static Return callLambda(FunctionPtr ptr, Params... args);
        static Return callFunction(FunctionPtr ptr, Params... args);

        static void destroyLambda(FunctionPtr ptr);
        static void destroyFunction(FunctionPtr ptr);

    private:
        FunctionPtr mFunction;
        Return (*mCaller)(FunctionPtr, Params...);
        void (*mDestroyer)(FunctionPtr);
};

#include "Function.inl"

#endif // __FUNCTION_HPP__



