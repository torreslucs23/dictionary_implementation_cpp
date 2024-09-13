#include "RedBlackTree.h"
#include <iostream>
#include <stdexcept>
#include <functional>

template <typename Key, typename Value>
RedBlackTree<Key, Value>::RedBlackTree() : root(nullptr), treeSize(0) {}

template <typename Key, typename Value>
RedBlackTree<Key, Value>::~RedBlackTree() {
    clear(root);
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::insert(const Key& key, const Value& value) {
    NodeRBT<Key, Value>* node = new NodeRBT<Key, Value>(key, value);
    if (root == nullptr) {
        node->color = BLACK;
        root = node;
    } else {
        NodeRBT<Key, Value>* parent = nullptr;
        NodeRBT<Key, Value>* current = root;

        while (current != nullptr) {
            parent = current;
            if (key < current->key) current = current->left;
            else if (key > current->key) current = current->right;
            else {
                current->value = value;
                delete node;
                return;
            }
        }

        node->parent = parent;
        if (key < parent->key) parent->left = node;
        else parent->right = node;

        fixInsert(node);
    }
    treeSize++;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::fixInsert(NodeRBT<Key, Value>*& node) {
    NodeRBT<Key, Value>* parent = nullptr;
    NodeRBT<Key, Value>* grandparent = nullptr;

    while (node != root && node->color != BLACK && node->parent->color == RED) {
        parent = node->parent;
        grandparent = parent->parent;

        if (parent == grandparent->left) {
            NodeRBT<Key, Value>* uncle = grandparent->right;
            if (uncle && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    leftRotate(parent);
                    node = parent;
                    parent = node->parent;
                }
                rightRotate(grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        } else {
            NodeRBT<Key, Value>* uncle = grandparent->left;
            if (uncle && uncle->color == RED) {
                grandparent->color = RED;


                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    rightRotate(parent);
                    node = parent;
                    parent = node->parent;
                }
                leftRotate(grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        }
    }
    root->color = BLACK;
}









template <typename Key, typename Value>
void RedBlackTree<Key, Value>::leftRotate(NodeRBT<Key, Value>*& node) {
    NodeRBT<Key, Value>* rightChild = node->right;
    node->right = rightChild->left;
    if (node->right != nullptr) node->right->parent = node;
    rightChild->parent = node->parent;

    if (node->parent == nullptr) root = rightChild;
    else if (node == node->parent->left) node->parent->left = rightChild;
    else node->parent->right = rightChild;

    rightChild->left = node;
    node->parent = rightChild;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::rightRotate(NodeRBT<Key, Value>*& node) {
    NodeRBT<Key, Value>* leftChild = node->left;
    node->left = leftChild->right;
    if (node->left != nullptr) node->left->parent = node;
    leftChild->parent = node->parent;

    if (node->parent == nullptr) root = leftChild;
    else if (node == node->parent->left) node->parent->left = leftChild;
    else node->parent->right = leftChild;

    leftChild->right = node;
    node->parent = leftChild;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::erase(const Key& key) {
    if (root == nullptr) return;

    NodeRBT<Key, Value>* node = findNode(key);
    if (node == nullptr) throw std::runtime_error("Key not found");

    root = eraseNode(root, key);
    treeSize--;
}




template <typename Key, typename Value>
NodeRBT<Key, Value>* RedBlackTree<Key, Value>::eraseNode(NodeRBT<Key, Value>* node, const Key& key) {
    if (node == nullptr) return node;

    if (key < node->key) node->left = eraseNode(node->left, key);
    else if (key > node->key) node->right = eraseNode(node->right, key);
    else {
        if (node->left == nullptr || node->right == nullptr) {
            NodeRBT<Key, Value>* temp = node->left ? node->left : node->right;

            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            NodeRBT<Key, Value>* temp = node->right;
            while (temp->left != nullptr) temp = temp->left;

            node->key = temp->key;
            node->value = temp->value;
            node->right = eraseNode(node->right, temp->key);
        }
    }

    if (node == nullptr) return node;

    fixInsert(node);
    return node;
}


template <typename Key, typename Value>
NodeRBT<Key, Value>* RedBlackTree<Key, Value>::findNode(const Key& key) const {
    NodeRBT<Key, Value>* current = root;
    while (current != nullptr) {
        if (key < current->key) current = current->left;
        else if (key > current->key) current = current->right;
        else return current;
    }
    return nullptr;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::update(const Key& key, const Value& newValue) {
    NodeRBT<Key, Value>* node = findNode(key);
    if (node == nullptr) {
        throw std::runtime_error("Key not found");
    }
    node->value = newValue;
}

template <typename Key, typename Value>
Value RedBlackTree<Key, Value>::get(const Key& key) const {
    NodeRBT<Key, Value>* node = findNode(key);
    if (node == nullptr) throw std::runtime_error("Key not found");
    return node->value;
}

template <typename Key, typename Value>
bool RedBlackTree<Key, Value>::contains(const Key& key) const {
    return findNode(key) != nullptr;
}

template <typename Key, typename Value>
int RedBlackTree<Key, Value>::size() const {
    return treeSize;
}

template <typename Key, typename Value>
bool RedBlackTree<Key, Value>::empty() const {
    return root == nullptr;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::clear() {
    clear(root);
    root = nullptr;
    treeSize = 0;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::clear(NodeRBT<Key, Value>* node) {
    if (node == nullptr) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::traverse() const {
    std::function<void(NodeRBT<Key, Value>*)> inOrder = [&](NodeRBT<Key, Value>* node) {
        if (node != nullptr) {
            inOrder(node->left);
            std::cout << node->key << " -> " << node->value << " (Color: " 
                      << (node->color == RED ? "Red" : "Black") << ")\n";
            inOrder(node->right);
        }
    };
    inOrder(root);
}

