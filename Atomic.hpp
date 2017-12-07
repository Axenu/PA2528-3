#ifndef __ATOMIC__
#define __ATOMIC__

#include <cstdint>

class Atomic {
    public:
        Atomic(uint32_t value = 0);

        Atomic& operator++(int);
        Atomic& operator--(int);

        Atomic& operator=(uint32_t value);
        Atomic& operator=(const Atomic& other);

        bool operator==(uint32_t value);
        bool operator==(const Atomic& other);

        uint32_t exchange(uint32_t value);
        bool compareExchange(uint32_t exchange, uint32_t expected);

        uint32_t load();


    private:
        char mData[8];
        volatile uint32_t* mValue;
};

#endif // __ATOMIC__

