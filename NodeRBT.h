#ifndef NODERBT_H
#define NODERBT_H

// interface struct do node da arvore rubro negra

// enum para usar como cores na implementacao
enum Color { RED, BLACK };

template <typename Key, typename Value>
struct NodeRBT {
    Key key;
    Value value;
    Color color;
    NodeRBT* left;
    NodeRBT* right;
    NodeRBT* parent;

    NodeRBT(Key k, Value v) 
        : key(k), value(v), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

#endif
