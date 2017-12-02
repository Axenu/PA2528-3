#include "Functor.hpp"

Functor::~Functor() {
    delete mFunction;
}

void Functor::operator()() {
    mFunction->operator()();
}

void Functor::operator()() const {
    mFunction->operator()();
}
