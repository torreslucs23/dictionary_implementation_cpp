#include "HashTable.h"
#include <stdexcept>
#include <iostream>

// arquivo que implementa metodos do hash table com enderecamento aberto



template <typename Key, typename Value, typename Hash>
HashTable<Key, Value, Hash>::HashTable(size_t table_size, float load_factor)
    : m_table_size(table_size), m_load_factor(load_factor), m_number_of_elements(0) {
    m_table.resize(m_table_size);
}

template <typename Key, typename Value, typename Hash>
HashTable<Key, Value, Hash>::~HashTable() {
    clear();
}

template <typename Key, typename Value, typename Hash>
void HashTable<Key, Value, Hash>::insert(const Key& key, const Value& value) {
    if (static_cast<float>(m_number_of_elements) / m_table_size > m_load_factor) {
        rehash();
    }

    size_t index = hash_code(key);
    for (auto& kvp : m_table[index]) {
        if (kvp.first == key) {
            throw std::invalid_argument("Key already exists");
        }
    }
    m_table[index].emplace_back(key, value);
    ++m_number_of_elements;
}

template <typename Key, typename Value, typename Hash>
void HashTable<Key, Value, Hash>::erase(const Key& key) {
    size_t index = hash_code(key);
    for (auto it = m_table[index].begin(); it != m_table[index].end(); ++it) {
        if (it->first == key) {
            m_table[index].erase(it);
            --m_number_of_elements;
            return;
        }
    }
    throw std::out_of_range("Key not found");
}

template <typename Key, typename Value, typename Hash>
Value HashTable<Key, Value, Hash>::get(const Key& key) const {
    size_t index = hash_code(key);
    for (const auto& kvp : m_table[index]) {
        if (kvp.first == key) {
            return kvp.second;
        }
    }
    throw std::out_of_range("Key not found");
}

template <typename Key, typename Value, typename Hash>
void HashTable<Key, Value, Hash>::update(const Key& key, const Value& value) {
    size_t index = hash_code(key);
    for (auto& kvp : m_table[index]) {
        if (kvp.first == key) {
            kvp.second = value;
            return;
        }
    }
    throw std::out_of_range("Key not found");
}

template <typename Key, typename Value, typename Hash>
bool HashTable<Key, Value, Hash>::contains(const Key& key) const {
    size_t index = hash_code(key);
    for (const auto& kvp : m_table[index]) {
        if (kvp.first == key) {
            return true;
        }
    }
    return false;
}

template <typename Key, typename Value, typename Hash>
void HashTable<Key, Value, Hash>::clear() {
    for (auto& bucket : m_table) {
        bucket.clear();
    }
    m_number_of_elements = 0;
}

template <typename Key, typename Value, typename Hash>
int HashTable<Key, Value, Hash>::size() const {
    return m_number_of_elements;
}

template <typename Key, typename Value, typename Hash>
bool HashTable<Key, Value, Hash>::empty() const {
    return m_number_of_elements == 0;
}

template <typename Key, typename Value, typename Hash>
void HashTable<Key, Value, Hash>::traverse() const {
    for (const auto& bucket : m_table) {
        for (const auto& kvp : bucket) {
            std::cout << kvp.first << ": " << kvp.second << std::endl;
        }
    }
}

template <typename Key, typename Value, typename Hash>
size_t HashTable<Key, Value, Hash>::hash_code(const Key& key) const {
    return Hash{}(key) % m_table_size;
}

template <typename Key, typename Value, typename Hash>
void HashTable<Key, Value, Hash>::rehash() {
    m_table_size *= 2;
    std::vector<std::list<std::pair<Key, Value>>> new_table(m_table_size);

    for (const auto& bucket : m_table) {
        for (const auto& kvp : bucket) {
            size_t index = hash_code(kvp.first);
            new_table[index].emplace_back(kvp);
        }
    }
    m_table.swap(new_table);
}

template class HashTable<std::string, std::string>;
