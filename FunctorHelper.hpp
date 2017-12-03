#ifndef __FUNCTOR_HELPER__
#define __FUNCTOR_HELPER__

class FunctorHelperBase {
    public:
        virtual ~FunctorHelperBase();
        virtual void operator()() = 0;
};

template<typename Function>
class FunctorHelper : public FunctorHelperBase {
    public:
        FunctorHelper(const Function& function);
        virtual void operator()() override;
    private:
        Function mFunction;
};

#include "FunctorHelper.inl"

#endif // __FUNCTOR_HELPER__

