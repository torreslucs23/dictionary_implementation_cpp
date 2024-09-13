#include <bits/stdc++.h>
#include "AVLTree.cpp"
#include "RedBlackTree.cpp"
#include "Dictionary.h"
#include "HashTable.cpp"
using namespace std;


int main(int argc, char const *argv[])
{

    HashTable<string, int> dictionary;
    dictionary.insert("nome", 1);
    cout << dictionary.get("nome") << endl;
    dictionary.update("nome", dictionary.get("nome")+1);
    cout << dictionary.get("nome") << endl;

    return 0;
}
