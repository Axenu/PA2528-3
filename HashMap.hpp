#ifndef __HASH_MAP__
#define __HASH_MAP__

template<typename Key, typename Value>
class HashMap {
    public:
        // Return nullptr if not found.
        Value* find(const Key& key);

        void insert(const Key& key, const Value& value);
};

#include "HashMap.inl"

#endif // __HASH_MAP__

