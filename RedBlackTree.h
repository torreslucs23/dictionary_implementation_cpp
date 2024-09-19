#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "Dictionary.h"
#include "NodeRBT.h"

// implementacao interface da ed arvore rubro negra, que sobreescreve metodos da classe abstrata dictionary

template <typename Key, typename Value>
class RedBlackTree : public Dictionary<Key, Value> {
public:
    RedBlackTree();
    ~RedBlackTree();

    void insert(const Key& key, const Value& value) override;
    void erase(const Key& key) override;
    Value get(const Key& key) const override;
    bool contains(const Key& key) const override;
    int size() const override;
    bool empty() const override;
    void clear() override;
    void traverse() const override;
    void update(const Key& key, const Value& newValue) override; 
    size_t get_comparison_count() const override { return comparison_count; }
    void reset_comparison_count() override { comparison_count = 0; }


private:
    NodeRBT<Key, Value>* root;
    int treeSize;
    mutable size_t comparison_count = 0;

    void fixInsert(NodeRBT<Key, Value>*& node);
    void leftRotate(NodeRBT<Key, Value>*& node);
    void rightRotate(NodeRBT<Key, Value>*& node);
    NodeRBT<Key, Value>* eraseNode(NodeRBT<Key, Value>* node, const Key& key);
    NodeRBT<Key, Value>* findNode(const Key& key) const;
    void clear(NodeRBT<Key, Value>* node);
};

#endif
