#include <iostream>
#include <stdexcept>
#include <functional>
#include "AVLTree.h"

using namespace std;

// implementacoes metodos avltree

// construtor
template <typename Key, typename Value>
AVLTree<Key, Value>::AVLTree() : root(nullptr) {}

// Destrutor
template <typename Key, typename Value>
AVLTree<Key, Value>::~AVLTree() {
    root = clear(root);
}

// limpa todos os nos
template <typename Key, typename Value>
NodeAVL<Key, Value>* AVLTree<Key, Value>::clear(NodeAVL<Key, Value>* node) {
    if (node == nullptr) return nullptr;
    clear(node->left);
    clear(node->right);
    delete node;
    return nullptr;
}

// pega altura de um no
template <typename Key, typename Value>
int AVLTree<Key, Value>::height(NodeAVL<Key, Value>* node) {
    return node ? node->height : 0;
}

// retorna fator de balanceamento de um no
template <typename Key, typename Value>
int AVLTree<Key, Value>::getBalance(NodeAVL<Key, Value>* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Rotacao a direita impl
template <typename Key, typename Value>
NodeAVL<Key, Value>* AVLTree<Key, Value>::rightRotate(NodeAVL<Key, Value>* y) {
    NodeAVL<Key, Value>* x = y->left;
    NodeAVL<Key, Value>* T2 = x->right;
    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Rotacao a esquerda impl
template <typename Key, typename Value>
NodeAVL<Key, Value>* AVLTree<Key, Value>::leftRotate(NodeAVL<Key, Value>* x) {
    NodeAVL<Key, Value>* y = x->right;
    NodeAVL<Key, Value>* T2 = y->left;
    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Insere um nova chave-valor na avl
template <typename Key, typename Value>
NodeAVL<Key, Value>* AVLTree<Key, Value>::insert(NodeAVL<Key, Value>* node, const Key& key, const Value& value) {
    if (node == nullptr) return new NodeAVL<Key, Value>(key, value);

    comparison_count++;  // Incrementa contador de comparações
    if (key < node->key) {
        node->left = insert(node->left, key, value);
    } else if (key > node->key) {
        comparison_count++;  // Incrementa novamente 
        node->right = insert(node->right, key, value);
    } else {
        node->value = value;
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key) return rightRotate(node);
    if (balance < -1 && key > node->right->key) return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}


// 
//

template <typename Key, typename Value>
void AVLTree<Key, Value>::insert(const Key& key, const Value& value) {
    root = insert(root, key, value);
}

// encontra o no com o menor valor
template <typename Key, typename Value>
NodeAVL<Key, Value>* AVLTree<Key, Value>::minValueNode(NodeAVL<Key, Value>* node) {
    NodeAVL<Key, Value>* current = node;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

// encontra o no com omaior valor
template <typename Key, typename Value>
NodeAVL<Key, Value>* AVLTree<Key, Value>::maxValueNode(NodeAVL<Key, Value>* node) {
    NodeAVL<Key, Value>* current = node;
    while (current && current->right != nullptr)
        current = current->right;
    return current;
}

// apaga um no pela chave
template <typename Key, typename Value>
NodeAVL<Key, Value>* AVLTree<Key, Value>::erase(NodeAVL<Key, Value>* root, const Key& key) {
    comparison_count++;
    if (root == nullptr) return root;

    comparison_count++;
    if (key < root->key) root->left = erase(root->left, key);
    else if (key > root->key) root->right = erase(root->right, key);
    else {
        comparison_count++;
        if ((root->left == nullptr) || (root->right == nullptr)) {
            NodeAVL<Key, Value> *temp = root->left ? root->left : root->right;
            comparison_count++;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else *root = *temp;
            delete temp;
        } else {
            NodeAVL<Key, Value>* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = erase(root->right, temp->key);
        }
    }


    

    if (root == nullptr) return root;
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::erase(const Key& key) {
    root = erase(root, key);
}

// retorna no pela chave
// 
template <typename Key, typename Value>
Value AVLTree<Key, Value>::get(NodeAVL<Key, Value>* node, const Key& key) const {
    comparison_count++;
    if (node == nullptr) throw std::runtime_error("Key not found");
    comparison_count++;
    if (key < node->key) return get(node->left, key);
    else if (key > node->key) return get(node->right, key);
    else return node->value;
}

template <typename Key, typename Value>
Value AVLTree<Key, Value>::get(const Key& key) const {
    return get(root, key);
}

// atualiza o valor por um chave existente
template <typename Key, typename Value>
void AVLTree<Key, Value>::update(const Key& key, const Value& value) {
    if (contains(key)) erase(key);
    insert(key, value);
}

// checa se uma chave existe na arvore
template <typename Key, typename Value>
bool AVLTree<Key, Value>::contains(NodeAVL<Key, Value>* node, const Key& key) const {
    if (node == nullptr) return false;
    if (key < node->key) return contains(node->left, key);
    else if (key > node->key) return contains(node->right, key);
    else return true;
}

template <typename Key, typename Value>
bool AVLTree<Key, Value>::contains(const Key& key) const {
    return contains(root, key);
}

// tamanho da arvore
template <typename Key, typename Value>
int AVLTree<Key, Value>::size(NodeAVL<Key, Value>* node) const {
    if (node == nullptr) return 0;
    return 1 + size(node->left) + size(node->right);
}

template <typename Key, typename Value>
int AVLTree<Key, Value>::size() const {
    return size(root);
}

// verifica se arvore e vazia
template <typename Key, typename Value>
bool AVLTree<Key, Value>::empty() const {
    return root == nullptr;
}

// percorre a arvore em pre-order
template <typename Key, typename Value>
void AVLTree<Key, Value>::traverse() const {
    std::function<void(NodeAVL<Key, Value>*)> preOrder = [&](NodeAVL<Key, Value>* node) {
        if (node != nullptr) {
            std::cout << node->key << ": " << node->value << std::endl;
            preOrder(node->left);
            preOrder(node->right);
        }
    };

    preOrder(root);
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::clear() {
    root = clear(root);
}
