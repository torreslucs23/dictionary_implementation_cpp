#ifndef NODEAVL_H
#define NODEAVL_H

template <typename Key, typename Value>
struct NodeAVL {
    Key key;
    Value value;
    NodeAVL *left;
    NodeAVL *right;
    int height;
    NodeAVL(Key k, Value v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
};

#endif
