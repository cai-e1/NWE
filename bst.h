
#ifndef BST_H
#define BST_H
#include <iostream>

using namespace std;

template <typename D, typename K>
class BST{
private: 
    struct Node{
        D data;
        K key;
        Node* p;
        Node* left;
        Node* right;

        Node() : data(D()), key (K()) {};
        Node(D d, K k) {
            data = d;
            key = k;
            p = nullptr;
            left = nullptr;
            right = nullptr;
        };
    };
    Node* root;

public:

    BST();
    ~BST();
    BST (const BST<D,K> & rbst);

    bool empty ();
    void insert (D data, K key);
    D get (K key);
    void remove (K key);
    D max_data();
    K max_key();
    D min_data();
    K min_key();
    K successor(K key);
    string in_order();
    void trim (K low, K high);
    void clear(Node* node);
    string print_strings(Node* node);

    string to_string ();
};





#endif