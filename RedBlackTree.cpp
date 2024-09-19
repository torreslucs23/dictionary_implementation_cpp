#include "RedBlackTree.h"
#include <iostream>
#include <stdexcept>
#include <functional>


//construtor
template <typename Key, typename Value>
RedBlackTree<Key, Value>::RedBlackTree() : root(nullptr), treeSize(0) {}


//destrutor
template <typename Key, typename Value>
RedBlackTree<Key, Value>::~RedBlackTree() {
    clear(root);
}

//insere uma uma chave-valor na arvore
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::insert(const Key& key, const Value& value) {
    NodeRBT<Key, Value>* node = new NodeRBT<Key, Value>(key, value);
    comparison_count++;
    if (root == nullptr) {
        node->color = BLACK;
        root = node;
    } else {
        NodeRBT<Key, Value>* parent = nullptr;
        NodeRBT<Key, Value>* current = root;

        while (current != nullptr) {
            parent = current;
            comparison_count++;
            if (key < current->key) current = current->left;
            else if (key > current->key) current = current->right;
            else {
                comparison_count++;
                current->value = value;
                delete node;
                return;
            }
        }

        node->parent = parent;
        comparison_count++;
        if (key < parent->key) parent->left = node;
        else parent->right = node;

        fixInsert(node);
    }
    treeSize++;
}

//faz o balanceamento da insercao
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::fixInsert(NodeRBT<Key, Value>*& node) {
    NodeRBT<Key, Value>* parent = nullptr;
    NodeRBT<Key, Value>* grandparent = nullptr;

    while (node != root && node->color != BLACK && node->parent->color == RED) {
        parent = node->parent;
        grandparent = parent->parent;
        comparison_count++;

        if (parent == grandparent->left) {
            NodeRBT<Key, Value>* uncle = grandparent->right;
            comparison_count++;
            if (uncle && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                comparison_count++;
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
            comparison_count++;
            if (uncle && uncle->color == RED) {
                grandparent->color = RED;


                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                comparison_count++;
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








// rotacao a esquerda
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::leftRotate(NodeRBT<Key, Value>*& node) {
    NodeRBT<Key, Value>* rightChild = node->right;
    node->right = rightChild->left;
    comparison_count++;
    if (node->right != nullptr) node->right->parent = node;
    rightChild->parent = node->parent;

    comparison_count++;
    if (node->parent == nullptr) root = rightChild;
    else if (node == node->parent->left) node->parent->left = rightChild;
    else node->parent->right = rightChild;

    rightChild->left = node;
    node->parent = rightChild;
}


// rotacao a direita
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::rightRotate(NodeRBT<Key, Value>*& node) {
    NodeRBT<Key, Value>* leftChild = node->left;
    node->left = leftChild->right;
    comparison_count++;
    if (node->left != nullptr) node->left->parent = node;
    leftChild->parent = node->parent;

    comparison_count++;
    if (node->parent == nullptr) root = leftChild;
    else if (node == node->parent->left) node->parent->left = leftChild;
    else node->parent->right = leftChild;

    leftChild->right = node;
    node->parent = leftChild;
}

// apaga node pela chave
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::erase(const Key& key) {
    comparison_count++;
    if (root == nullptr) return;

    comparison_count++;
    NodeRBT<Key, Value>* node = findNode(key);
    if (node == nullptr) throw std::runtime_error("chave não encontrada");

    root = eraseNode(root, key);
    treeSize--;
}



//metodo aux para apagar node
template <typename Key, typename Value>
NodeRBT<Key, Value>* RedBlackTree<Key, Value>::eraseNode(NodeRBT<Key, Value>* node, const Key& key) {
    comparison_count++;
    if (node == nullptr) return node;

    comparison_count++;
    if (key < node->key) node->left = eraseNode(node->left, key);
    else if (key > node->key) node->right = eraseNode(node->right, key);
    else {
        comparison_count++;
        if (node->left == nullptr || node->right == nullptr) {
            NodeRBT<Key, Value>* temp = node->left ? node->left : node->right;
            comparison_count++;

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

    comparison_count++;
    if (node == nullptr) return node;

    fixInsert(node);
    return node;
}


// metodo que encontra no na arvore
template <typename Key, typename Value>
NodeRBT<Key, Value>* RedBlackTree<Key, Value>::findNode(const Key& key) const {
    NodeRBT<Key, Value>* current = root;
    while (current != nullptr) {
        comparison_count++;
        if (key < current->key) current = current->left;
        else if (key > current->key) current = current->right;
        else return current;
    }
    return nullptr;
}


// atualiza valor na arvore
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::update(const Key& key, const Value& newValue) {
    NodeRBT<Key, Value>* node = findNode(key);
    comparison_count++;
    if (node == nullptr) {
        throw std::runtime_error("chave não encontrada");
    }
    node->value = newValue;
}

// retorna um no pela chave

template <typename Key, typename Value>
Value RedBlackTree<Key, Value>::get(const Key& key) const {
    NodeRBT<Key, Value>* node = findNode(key);
    comparison_count++;
    if (node == nullptr) throw std::runtime_error("chave não encontrada");
    return node->value;
}

// verifica se no esta contido na arvore
template <typename Key, typename Value>
bool RedBlackTree<Key, Value>::contains(const Key& key) const {
    return findNode(key) != nullptr;
}

//calcula tamanho da arvore
template <typename Key, typename Value>
int RedBlackTree<Key, Value>::size() const {
    return treeSize;
}


// verifica se arvore e vazia
template <typename Key, typename Value>
bool RedBlackTree<Key, Value>::empty() const {
    return root == nullptr;
}


// limpa arvore
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::clear() {
    clear(root);
    root = nullptr;
    treeSize = 0;
}


// limpa com passagem de no
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::clear(NodeRBT<Key, Value>* node) {
    if (node == nullptr) return;
    clear(node->left);
    clear(node->right);
    delete node;
}


// metodo que percorre arvore inorder
template <typename Key, typename Value>
void RedBlackTree<Key, Value>::traverse() const {
    std::function<void(NodeRBT<Key, Value>*)> inOrder = [&](NodeRBT<Key, Value>* node) {
        if (node != nullptr) {
            inOrder(node->left);
            std::cout << node->key << ": " << node->value <<  "\n";
            inOrder(node->right);
        }
    };
    inOrder(root);
}

