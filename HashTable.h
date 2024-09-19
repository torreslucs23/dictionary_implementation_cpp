#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <utility>
#include <cstddef>
#include <functional>
#include "Dictionary.h"

// interface que implementa tabela Hash com tratamento de colisão por encadeamento exterior

// todos os metodos da interface dictionary tem override
template <typename Key, typename Value, typename Hash = std::hash<Key>>
class HashTable : public Dictionary<Key, Value> {
public:
    HashTable(size_t table_size = 101, float load_factor = 0.75);
    ~HashTable();

    void insert(const Key& key, const Value& value) override;
    void erase(const Key& key) override;
    Value get(const Key& key) const override;
    void update(const Key& key, const Value& value) override;
    bool contains(const Key& key) const override;
    void clear() override;
    int size() const override;
    bool empty() const override;
    void traverse() const override;
    size_t get_comparison_count() const override { return comparison_count; }
    void reset_comparison_count() override { comparison_count = 0; }

private:
    size_t hash_code(const Key& key) const;
    void rehash();
    mutable size_t comparison_count = 0;

    std::vector<std::list<std::pair<Key, Value>>> m_table;
    size_t m_table_size;
    size_t m_number_of_elements;
    float m_load_factor;
};

#endif
