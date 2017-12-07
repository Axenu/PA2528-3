#include "Atomic.hpp"


#include <windows.h>


Atomic::Atomic(uint32_t value) {
    mValue = (volatile uint32_t*)(size_t(mData) + (sizeof(uint32_t) - size_t(mData) % sizeof(uint32_t)) % sizeof(uint32_t));
    *mValue = value;
}

Atomic& Atomic::operator++(int) {
    InterlockedIncrement(mValue);
    return *this;
}

Atomic& Atomic::operator--(int) {
    InterlockedDecrement(mValue);
    return *this;
}

Atomic& Atomic::operator=(uint32_t value)  {
    *mValue = value;
    return *this;
}

Atomic& Atomic::operator=(const Atomic& other) {
    *mValue = *other.mValue;
    return *this;
}

bool Atomic::operator==(uint32_t value) {
    return *mValue == value;
}
bool Atomic::operator==(const Atomic& other) {
    return *mValue == *other.mValue;
}

uint32_t Atomic::load() {
    return *mValue;
}

uint32_t Atomic::exchange(uint32_t value) {
    return InterlockedExchange(mValue, value);
}

bool Atomic::compareExchange(uint32_t exchange, uint32_t expected) {
    return InterlockedCompareExchange(mValue, exchange, expected) == expected;
}
