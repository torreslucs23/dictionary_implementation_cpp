#include "OpenHashTable.h"
#include <iostream>

// construtor
template <typename Key, typename Value, typename Hash>
OpenHashTable<Key, Value, Hash>::OpenHashTable(size_t table_size, float load_factor)
    : m_table_size(table_size), m_load_factor(load_factor), m_number_of_elements(0) {
    m_table.resize(m_table_size);
    m_status.resize(m_table_size, EMPTY);
}

// destrutor
template <typename Key, typename Value, typename Hash>
OpenHashTable<Key, Value, Hash>::~OpenHashTable() {
    clear();
}

// inserir uma chave-valor par
// incrementa comps
template <typename Key, typename Value, typename Hash>
void OpenHashTable<Key, Value, Hash>::insert(const Key& key, const Value& value) {
    comparison_count++;
    if (static_cast<float>(m_number_of_elements) / m_table_size > m_load_factor) {
        rehash();
    }

    size_t index = hash_code(key);
    while (m_status[index] == OCCUPIED) {
        comparison_count++;  
        if (m_table[index].first == key) {
            throw std::invalid_argument("chave já existe");
        }
        index = (index + 1) % m_table_size;
    }
    m_table[index] = std::make_pair(key, value);
    m_status[index] = OCCUPIED;
    ++m_number_of_elements;
}


// apaga uma chave
template <typename Key, typename Value, typename Hash>
void OpenHashTable<Key, Value, Hash>::erase(const Key& key) {
    size_t index = hash_code(key);
    while (m_status[index] != EMPTY) {
        comparison_count++;
        if (m_status[index] == OCCUPIED && m_table[index].first == key) {
            m_status[index] = DELETED;
            --m_number_of_elements;
            return;
        }
        index = (index + 1) % m_table_size;
    }
    throw std::out_of_range("Chave não encontrada");
}

// pega o valor associado a chave
// incrementa comps
template <typename Key, typename Value, typename Hash>
Value OpenHashTable<Key, Value, Hash>::get(const Key& key) const {
    size_t index = hash_code(key);
    while (m_status[index] != EMPTY) {
        comparison_count++;  
        if (m_status[index] == OCCUPIED && m_table[index].first == key) {
            return m_table[index].second;
        }
        index = (index + 1) % m_table_size;
    }
    throw std::out_of_range("Chave não encontrada");
}


// Atualiza o valor de uma chave existente
template <typename Key, typename Value, typename Hash>
void OpenHashTable<Key, Value, Hash>::update(const Key& key, const Value& value) {
    size_t index = hash_code(key);
    while (m_status[index] != EMPTY) {
        comparison_count++;
        if (m_status[index] == OCCUPIED && m_table[index].first == key) {
            m_table[index].second = value;
            return;
        }
        index = (index + 1) % m_table_size;
    }
    throw std::out_of_range("Chave não encontrada");
}

// verifica se a table possui a chave
template <typename Key, typename Value, typename Hash>
bool OpenHashTable<Key, Value, Hash>::contains(const Key& key) const {
    size_t index = hash_code(key);
    while (m_status[index] != EMPTY) {
        comparison_count++; 
        if (m_status[index] == OCCUPIED && m_table[index].first == key) {
            return true;
        }
        index = (index + 1) % m_table_size;
    }
    return false;
}


template <typename Key, typename Value, typename Hash>
void OpenHashTable<Key, Value, Hash>::clear() {
    m_table.clear();
    m_status.clear();
    m_table_size = 101;
    m_table.resize(m_table_size);
    m_status.resize(m_table_size, EMPTY);
    m_number_of_elements = 0;
}

// numro de elementos da tabela
template <typename Key, typename Value, typename Hash>
int OpenHashTable<Key, Value, Hash>::size() const {
    return m_number_of_elements;
}

// verifica se tabela e vazia
template <typename Key, typename Value, typename Hash>
bool OpenHashTable<Key, Value, Hash>::empty() const {
    return m_number_of_elements == 0;
}

// percorre imprimindo os valores
template <typename Key, typename Value, typename Hash>
void OpenHashTable<Key, Value, Hash>::traverse() const {
    for (size_t i = 0; i < m_table_size; ++i) {
        comparison_count++;
        if (m_status[i] == OCCUPIED) {
            std::cout << m_table[i].first << ": " << m_table[i].second << std::endl;
        }
    }
}

// gera hash
template <typename Key, typename Value, typename Hash>
size_t OpenHashTable<Key, Value, Hash>::hash_code(const Key& key) const {
    return Hash{}(key) % m_table_size;
}

// rehash a tabela quando a carga excede
template <typename Key, typename Value, typename Hash>
void OpenHashTable<Key, Value, Hash>::rehash() {
    m_table_size *= 2;
    std::vector<std::pair<Key, Value>> new_table(m_table_size);
    std::vector<SlotStatus> new_status(m_table_size, EMPTY);

    for (size_t i = 0; i < m_table.size(); ++i) {
        comparison_count++;
        if (m_status[i] == OCCUPIED) {
            size_t index = hash_code(m_table[i].first);
            while (new_status[index] == OCCUPIED) {
                comparison_count++;
                index = (index + 1) % m_table_size;
            }
            new_table[index] = m_table[i];
            new_status[index] = OCCUPIED;
        }
    }
    m_table.swap(new_table);
    m_status.swap(new_status);
}

template class OpenHashTable<std::string, std::string>;
