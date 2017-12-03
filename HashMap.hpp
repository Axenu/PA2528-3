#ifndef __HASH_MAP__
#define __HASH_MAP__

#include <functional>

#include "utility.hpp"

template<typename Key, typename Value>
class HashMap {
    public:
        HashMap();

        // Return nullptr if not found.
        Value* find(const Key& key);

        void insert(const Key& key, const Value& value);

        void erase(const Key& key);

    private:
        static constexpr size_t hash(const Key& key);

    private:
        struct Entry {
            Key key;
            Value value;
            Entry* next = nullptr;
        };

    private:
        static constexpr size_t TABLE_SIZE = 1024;
        static_assert(isPow2(TABLE_SIZE));
        static const std::hash<Key> HASHER;
        Entry* mTable[TABLE_SIZE];
};

#include "HashMap.inl"

#endif // __HASH_MAP__

