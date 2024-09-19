#ifndef AVLTREE_H
#define AVLTREE_H

#include "NodeAVL.h"
#include "Dictionary.h"

// implementação de interface da AVLTree, que sobreescreve métodos do dictionary
template <typename Key, typename Value>
class AVLTree : public Dictionary<Key, Value> {
private:
    NodeAVL<Key, Value>* root;
    mutable size_t comparison_count = 0; 

    NodeAVL<Key, Value>* insert(NodeAVL<Key, Value>* node, const Key& key, const Value& value);
    NodeAVL<Key, Value>* erase(NodeAVL<Key, Value>* node, const Key& key);
    NodeAVL<Key, Value>* minValueNode(NodeAVL<Key, Value>* node);
    NodeAVL<Key, Value>* maxValueNode(NodeAVL<Key, Value>* node);
    int height(NodeAVL<Key, Value>* node);
    int getBalance(NodeAVL<Key, Value>* node);
    NodeAVL<Key, Value>* rightRotate(NodeAVL<Key, Value>* y);
    NodeAVL<Key, Value>* leftRotate(NodeAVL<Key, Value>* x);
    bool contains(NodeAVL<Key, Value>* node, const Key& key) const;
    NodeAVL<Key, Value>* clear(NodeAVL<Key, Value>* node);
    Value get(NodeAVL<Key, Value>* node, const Key& key) const;
    int size(NodeAVL<Key, Value>* node) const;

public:
    AVLTree();
    ~AVLTree();
    
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
};

#endif
