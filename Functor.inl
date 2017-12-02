template<typename Function>
Functor::Functor(Function function) : mFunction(new FunctorHelper<Function>(function)) {
}
