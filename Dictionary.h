#include <cstddef>

#ifndef DICTIONARY_H
#define DICTIONARY_H

// Classe genérica abstrata do dictionary
template <typename Key, typename Value>
class Dictionary {
public:
    virtual ~Dictionary() {}

    virtual void insert(const Key& key, const Value& value) = 0;
    virtual void erase(const Key& key) = 0;
    virtual Value get(const Key& key) const = 0;
    virtual void update(const Key& key, const Value& value) = 0;
    virtual bool contains(const Key& key) const = 0;
    virtual void clear() = 0;
    virtual int size() const = 0;
    virtual bool empty() const = 0;
    virtual void traverse() const = 0;

    virtual size_t get_comparison_count() const = 0;  
    virtual void reset_comparison_count() = 0;        
};

#endif
