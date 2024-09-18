#ifndef OPENHASHTABLE_H
#define OPENHASHTABLE_H

#include <vector>
#include <utility>
#include <functional>
#include <stdexcept>
#include "Dictionary.h"

// HashTable with open addressing (linear probing) for collision handling
template <typename Key, typename Value, typename Hash = std::hash<Key>>
class OpenHashTable : public Dictionary<Key, Value> {
public:
    OpenHashTable(size_t table_size = 101, float load_factor = 0.75);
    ~OpenHashTable();

    void insert(const Key& key, const Value& value) override;
    void erase(const Key& key) override;
    Value get(const Key& key) const override;
    void update(const Key& key, const Value& value) override;
    bool contains(const Key& key) const override;
    void clear() override;
    int size() const override;
    bool empty() const override;
    void traverse() const override;

private:
    size_t hash_code(const Key& key) const;
    void rehash();

    enum SlotStatus { EMPTY, OCCUPIED, DELETED };
    
    std::vector<std::pair<Key, Value>> m_table;
    std::vector<SlotStatus> m_status;  // Keeps track of the status of each slot
    size_t m_table_size;
    size_t m_number_of_elements;
    float m_load_factor;
};

#endif
