#ifndef __FUNCTOR__
#define __FUNCTOR__

#include "FunctorHelper.hpp"

class Functor {
    public:
        template<typename Function>
        Functor(Function function);

        ~Functor();

        void operator()();
        void operator()() const;

    private:
        FunctorHelperBase* const mFunction;
};

#include "Functor.inl"

#endif // __FUNCTOR__

