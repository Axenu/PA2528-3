#include "Functor.hpp"

void Functor::operator()() {
    mFunction->operator()();
}

void Functor::operator()() const {
    mFunction->operator()();
}
