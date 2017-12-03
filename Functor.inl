template<typename Function>
Functor::Functor(const Function& function) : mFunction(new FunctorHelper<Function>(function)) {
}
