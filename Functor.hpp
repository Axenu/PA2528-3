#ifndef __FUNCTOR__
#define __FUNCTOR__

#include "FunctorHelper.hpp"
#include "SharedPtr.hpp"

class Functor {
    public:
        template<typename Function>
        Functor(const Function& function);

        void operator()();
        void operator()() const;

    private:
        SharedPtr<FunctorHelperBase> mFunction;
};

#include "Functor.inl"

#endif // __FUNCTOR__

